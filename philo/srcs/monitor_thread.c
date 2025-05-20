/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuebtha <ksuebtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:31:14 by ksuebtha          #+#    #+#             */
/*   Updated: 2025/05/20 15:34:39 by ksuebtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*monitor_routine(void *arg)
{
	t_table			*table;
	time_t			now;
	unsigned int	i;
	unsigned int	full_count;

	table = (t_table *)arg;
	while (true)
	{
		i = 0;
		full_count = 0;
		while (i < table->nb_philo)
		{
			pthread_mutex_lock(&table->sim_stop_lock);
			if (table->sim_stop)
			{
				pthread_mutex_unlock(&table->sim_stop_lock);
				return (NULL);
			}
			now = get_time_in_ms();
			if (now - table->philos[i]->lastmeal > table->time_to_die)
			{
				print_action(table->philos[i], "died" );
				table->sim_stop = true;
				pthread_mutex_unlock(&table->sim_stop_lock);
				return (NULL);
			}
			if (table->must_eat_count != -1
				&& table->philos[i]->eat_count >= table->must_eat_count)
				full_count++;
			pthread_mutex_unlock(&table->sim_stop_lock);
			i++;
		}

		if (table->must_eat_count != -1 && full_count == table->nb_philo)
		{
			pthread_mutex_lock(&table->sim_stop_lock);
			table->sim_stop = true;
			pthread_mutex_unlock(&table->sim_stop_lock);
			return (NULL);
		}
		usleep(1000);
	}
}


