/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuebtha <ksuebtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:22:32 by ksuebtha          #+#    #+#             */
/*   Updated: 2025/05/28 16:23:29 by ksuebtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

time_t	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_action(t_philo *philo, char *msg)
{
	bool	stopped;

	pthread_mutex_lock(&philo->table->sim_stop_lock);
	stopped = philo->table->sim_stop;
	pthread_mutex_unlock(&philo->table->sim_stop_lock);
	if (!stopped)
	{
		pthread_mutex_lock(&philo->table->print_lock);
		printf("%lu %d %s\n", get_time_in_ms() - philo->table->start_time,
			philo->id + 1, msg);
		pthread_mutex_unlock(&philo->table->print_lock);
	}
}

bool	has_sim_stopped(t_table *table)
{
	bool	result;

	pthread_mutex_lock(&table->sim_stop_lock);
	result = table->sim_stop;
	pthread_mutex_unlock(&table->sim_stop_lock);
	return (result);
}

void	precise_sleep_until(time_t deadline_ms, t_table *table)
{
	time_t	now;

	while (!has_sim_stopped(table))
	{
		now = get_time_in_ms();
		if (now >= deadline_ms)
			break ;
		usleep(100);
	}
}

void	assign_forks(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		table->philos[i]->left_fork = &table->forks[i];
		table->philos[i]->right_fork = &table->forks[(i + 1) % table->nb_philo];
		i++;
	}
}
