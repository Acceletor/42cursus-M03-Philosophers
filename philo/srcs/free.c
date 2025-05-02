#include "../include/philo.h"

void free_philos(t_table *table, unsigned int j)
{
    unsigned int i;
    t_philo **philos;
    
    i = 0;
    philos = table->philos;
    while (i < j)
        free(philos[i++]);
    free(philos);
    table->philos = NULL;
    return ;
}

void	destroy_mutexes(t_table *table)
{
	unsigned int	i;

	if (!table || !table->forks)
		return ;
	i = 0;
	while (i < table->nb_philo)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->print_lock);
}

void free_table(t_table *table)
{
    if (!table)
        return;
    if (table->forks)
    {
        destroy_mutexes(table);
        free(table->forks);
    }
    if (table->philos)
        free_philos(table, table->nb_philo);
    free(table);
    return ;
}