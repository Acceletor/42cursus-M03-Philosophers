/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuebtha <ksuebtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:49:26 by ksuebtha          #+#    #+#             */
/*   Updated: 2025/05/07 12:44:44 by ksuebtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"


static t_philo  *alloc_one_philo(t_table *table, unsigned int i)
{
    t_philo *philo;

    philo = malloc(sizeof(t_philo));
    if (!philo)
    {
        return (NULL);
    }
    // philo->philo = 0;
    philo->id = i;
    philo->left_fork = NULL;
    philo->right_fork = NULL;
    philo->eat_count = 0;
    philo->table = table;
    return (philo);
}


t_philo **init_philos(t_table *table)
{
    t_philo **philos;
    unsigned int i;
    
    philos = malloc(sizeof(t_philo *) * table->nb_philo);
    if (!philos)
    {
        free_table(table);
        dis_msg(STR_ERR_MALLOC, NULL, EXIT_FAILURE);
    } 
    i = 0;
    while (i < table->nb_philo)
    {
        philos[i] = alloc_one_philo(table, i);
        if (!philos[i])
        {
            free_philos(table, i);
            dis_msg(STR_ERR_MALLOC, NULL, EXIT_FAILURE);
        }
        i++;
    }
    return (philos);
}

pthread_mutex_t *init_fork(unsigned int nb_philo, t_table *table)
{
    pthread_mutex_t *forks;
    unsigned int i;
    
    forks = malloc(sizeof(pthread_mutex_t) * nb_philo);
    if (!forks)
    {
        free_table(table);
        dis_msg(STR_ERR_MALLOC, NULL, EXIT_FAILURE); 
    }
        
    i = 0;
    while(i < nb_philo)
    {
        if (pthread_mutex_init(&forks[i], NULL) != 0)
        {
            destroy_forks(table, i);
            free_table(table);
            dis_msg(STR_ERR_MUTEX, NULL, EXIT_FAILURE);
        } 
        i++;
    }
    return (forks);
}

bool create_global_mutex(t_table *table)
{
    table->forks = init_fork(table->nb_philo, table);
    if (pthread_mutex_init(&table->print_lock, NULL) != 0)
    {
        free_table(table);
        dis_msg(STR_ERR_MUTEX, NULL, EXIT_FAILURE);
    }
    table->print_lock_init = true;
    if (pthread_mutex_init(&table->sim_stop_lock, NULL) != 0)
    {
        free_table(table);
        dis_msg(STR_ERR_MUTEX, NULL, EXIT_FAILURE);
    }
    table->sim_stop_lock_init = true;
    return (true);
}
void assign_forks(t_table *table)
{
    unsigned int i;

    i = 0;
    while (i < table->nb_philo)
    {
        table->philos[i]->left_fork = &table->forks[i];
        table->philos[i]->right_fork = &table->forks[(i + 1)% table->nb_philo];
        i++;
    }
}

t_table *init_table(int vars[])
{
    t_table *table;

    table = malloc(sizeof(t_table));
    if (!table)
        dis_msg(STR_ERR_MALLOC, NULL, EXIT_FAILURE);
    table->nb_philo = vars[0];
    table->time_to_die = vars[1];
    table->time_to_eat = vars[2];
    table->time_to_sleep = vars[3];
    table->must_eat_count = vars[4];
    table->sim_stop = false;
    table->print_lock_init = false;
    table->sim_stop_lock_init = false;
    table->philos = init_philos(table);
    create_global_mutex(table);
    assign_forks(table);
    return (table);
}
