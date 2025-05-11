/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuebtha <ksuebtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:49:23 by ksuebtha          #+#    #+#             */
/*   Updated: 2025/05/07 12:36:27 by ksuebtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"


bool start_simulation(t_table *table)
{
    unsigned int i;

    table->start_time = get_time_in_ms();
    i = 0;
    while(i < table->nb_philo)
    {
        table->philos[i]->lastmeal = table->start_time;
        if (pthread_create(&table->philos[i]->philo, NULL, &philo_routine, table->philos[i]) != 0)
        {
            while (i-- > 0)
                pthread_join(table->philos[i]->philo, NULL);
            return (false);
        }
        i++;
    }
    if (pthread_create(&table->monitor_thread, NULL,&monitor_routine, table) != 0)
    {
        table->sim_stop = true;
        return (false);
    }
    return (true);
}


int main(int argc, char **argv)
{
    int vars[5];
    t_table *table;
    if (argc - 1 < 4 || argc - 1 > 5)
        dis_msg(STR_USAGE, NULL, EXIT_FAILURE);
    if (!is_valid_input(argc, argv, vars))
        return (EXIT_FAILURE);
    table = init_table(vars);
    if (!table)
        return (EXIT_FAILURE);
    if (!start_simulation(table))
    {
        if (table->sim_stop)
            stop_simulation(table);
        else
            free_table(table);
        dis_msg(STR_ERR_THREAD, NULL, EXIT_FAILURE);
    }
    stop_simulation(table);

    return (EXIT_SUCCESS);
}
