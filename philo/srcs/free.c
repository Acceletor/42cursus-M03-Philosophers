/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuebtha <ksuebtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:24:04 by ksuebtha          #+#    #+#             */
/*   Updated: 2025/05/20 15:25:53 by ksuebtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_philos(t_table *table, unsigned int j)
{
	unsigned int	i;
	t_philo			**philos;

	if (!table || !table->philos)
		return ;
	i = 0;
	philos = table->philos;
	while (i < j)
		free(philos[i++]);
	free(philos);
	table->philos = NULL;
	return ;
}

void	destroy_forks(t_table *table, unsigned int j)
{
	unsigned int	i;

	if (!table || !table->forks)
		return ;
	i = 0;
	while (i < j)
		pthread_mutex_destroy(&table->forks[i++]);
	free(table->forks);
	table->forks = NULL;
	return ;
}

void	free_table(t_table *table)
{
	if (!table)
		return ;
	if (table->forks)
		destroy_forks(table, table->nb_philo);
	if (table->print_lock_init)
		pthread_mutex_destroy(&table->print_lock);
	if (table->sim_stop_lock_init)
		pthread_mutex_destroy(&table->sim_stop_lock);
	if (table->philos)
		free_philos(table, table->nb_philo);
	free(table);
	return ;
}

void	stop_simulation(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		pthread_join(table->philos[i]->philo, NULL);
		i++;
	}
	free_table(table);
}
