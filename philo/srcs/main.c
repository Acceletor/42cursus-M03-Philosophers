#include "../include/philo.h"

time_t get_time_in_ms(void)
{
    struct timeval tv;
    
    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void *routine (void *arg)
{
    t_philo *philo = (t_philo *)arg;
    printf("%d\n", philo->id);

    return (NULL);
}


bool start_simulation(t_table *table)
{
    unsigned int i;

    table->start_time = get_time_in_ms();
    printf("Start time: %lu\n", table->start_time);
    i = 0;
    while(i < table->nb_philo)
    {
        if (pthread_create(&table->philos[i]->philo, NULL, routine, table->philos[i]) != 0)
        {
            while (i-- > 0)
                pthread_join(table->philos[i]->philo, NULL);
            return (false);
        }
        i++;
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
        free_table(table);
        dis_msg(STR_ERR_THREAD, NULL, EXIT_FAILURE);
    }
    stop_simulation(table);


    return (EXIT_SUCCESS);
}
