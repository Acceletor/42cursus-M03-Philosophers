/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuebtha <ksuebtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:31:14 by ksuebtha          #+#    #+#             */
/*   Updated: 2025/10/14 15:13:01 by ksuebtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	sim_should_stop(t_table *table)
{
	pthread_mutex_lock(&table->sim_stop_lock);
	if (table->sim_stop)
	{
		pthread_mutex_unlock(&table->sim_stop_lock);
		return (1);
	}
	pthread_mutex_unlock(&table->sim_stop_lock);
	return (0);
}

static int	philo_died(t_table *table, t_philo *ph)
{
	time_t			now;
	time_t			last;

	pthread_mutex_lock(&table->sim_stop_lock);
	now = get_time_in_ms();
	last = ph->lastmeal;
	pthread_mutex_unlock(&table->sim_stop_lock);
	if (now - last > table->time_to_die)
	{
		print_action(ph, "died");
		pthread_mutex_lock(&table->sim_stop_lock);
		table->sim_stop = true;
		pthread_mutex_unlock(&table->sim_stop_lock);
		return (1);
	}
	return (0);
}

static void	count_full(t_table *table, t_philo *ph, unsigned int *full_count)
{
	pthread_mutex_lock(&table->sim_stop_lock);
	if (table->must_eat_count != -1
		&& ph->eat_count >= table->must_eat_count)
		(*full_count)++;
	pthread_mutex_unlock(&table->sim_stop_lock);
}

static int	stop_if_all_full(t_table *table, unsigned int full_count)
{
	if (table->must_eat_count != -1 && full_count == table->nb_philo)
	{
		pthread_mutex_lock(&table->sim_stop_lock);
		table->sim_stop = true;
		pthread_mutex_unlock(&table->sim_stop_lock);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_table			*table;
	unsigned int	i;
	unsigned int	full_count;

	table = (t_table *)arg;
	while (true)
	{
		i = 0;
		full_count = 0;
		while (i < table->nb_philo)
		{
			if (sim_should_stop(table))
				return (NULL);
			if (philo_died(table, table->philos[i]))
				return (NULL);
			count_full(table, table->philos[i], &full_count);
			i++;
		}
		if (stop_if_all_full(table, full_count))
			return (NULL);
		usleep(1000);
	}
}
