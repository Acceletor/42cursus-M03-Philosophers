#include "../include/philo.h"

time_t get_time_in_ms(void)
{
    struct timeval tv;
    
    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void print_action(t_philo *philo, char *msg)
{
    pthread_mutex_lock(&philo->table->print_lock);
    if (!philo->table->sim_stop)
        printf("%lu %d %s\n", get_time_in_ms() - philo->table->start_time, philo->id + 1, msg);
    pthread_mutex_unlock(&philo->table->print_lock);
}

bool has_sim_stopped(t_table *table)
{
    bool result;

    pthread_mutex_lock(&table->sim_stop_lock);
    result = table->sim_stop;
    pthread_mutex_unlock(&table->sim_stop_lock);
    return (result);
}
