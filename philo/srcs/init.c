#include "../include/philo.h"

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
        philos[i] = malloc(sizeof(t_philo));
        if (!philos[i])
        {
            free_philos(table, i);
            dis_msg(STR_ERR_MALLOC, NULL, EXIT_FAILURE);
        }
        philos[i]->philo = NULL;
        philos[i]->id = i;
        philos[i]->left_fork = NULL;
        philos[i]->right_fork = NULL;
        philos[i]->eat_count = 0;
        philos[i]->table = table;
        i++;
    }
    return (philos);
}

pthread_mutex_t *init_fork(unsigned int nb_philo)
{
    pthread_mutex_t *forks;
    unsigned int i;
    
    forks = malloc(sizeof(pthread_mutex_t) * nb_philo);
    if (!forks)
        dis_msg(STR_ERR_MALLOC, NULL, EXIT_FAILURE);
    i = 0;
    while(i < nb_philo)
    {
        if (pthread_mutex_init(&forks[i], NULL) != 0)
            dis_msg(STR_ERR_MUTEX, NULL, EXIT_FAILURE);
        i++;
    }
    return (forks);
}

bool create_global_mutex(t_table *table)
{
    table->forks = init_fork(table->nb_philo);
    if (pthread_mutex_init(&table->print_lock, NULL) != 0)
        dis_msg(STR_ERR_MUTEX, NULL, EXIT_FAILURE);
    return (true);
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
    table->philos = init_philos(table);
    create_global_mutex(table);
    return (table);
}
