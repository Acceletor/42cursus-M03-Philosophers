/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuebtha <ksuebtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:20:17 by ksuebtha          #+#    #+#             */
/*   Updated: 2025/05/20 17:54:02 by ksuebtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*  Goal of the philo_routine 
Each philosopher thread simulate the following action:
1. Thinking
2. Take forks (two mutexes)
3. Eating (update time and track how many time)
4. Sleeping
5. Repeat until simulation stop (someone dies or all are full)
*/

//-----------------------------------------------------------------------------
// 1) Always pick forks in a fixed order to break the circular wait.
//    Here we compare the pointer addresses.
//-----------------------------------------------------------------------------

void	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	first = philo->left_fork;
	second = philo->right_fork;
	if (first > second)
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	pthread_mutex_lock(first);
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(second);
	print_action(philo, "has taken a fork");
}


void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->sim_stop_lock);
	philo->lastmeal = get_time_in_ms();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->table->sim_stop_lock);

	print_action(philo, "is eating");
	usleep(philo->table->time_to_eat * 1000);

}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	philo_sleep(t_philo *philo)
{
	print_action(philo, "is sleeping");
	usleep(philo->table->time_to_sleep * 1000);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	print_action(philo, "is thinking");
	while (!has_sim_stopped(philo->table))
	{
		take_forks(philo);
		eat(philo);
		drop_forks(philo);
		philo_sleep(philo);
		print_action(philo, "is thinking");
	}
	return (NULL);
}









