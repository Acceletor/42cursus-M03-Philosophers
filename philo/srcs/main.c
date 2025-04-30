#include "../include/philo.h"

int dis_msg(char *str, char *detail, int exit_no)
{
    if (!detail)
        printf(str, STR_PROG_NAME);
    else
        printf(str, STR_PROG_NAME, detail);

    exit(exit_no);
}


int unsigned_atoi(char *str)
{
    unsigned long long int nb;
    int i;

    i = 0;
    nb = 0;
    while (str[i] && (str[i] >= '0' && str[i] <= '9'))
    {
        nb *= 10;
        nb += str[i] - '0';
        i++;
    }
    if (str[i] || nb > INT_MAX || nb == 0)
        dis_msg(STR_ERR_INPUT_DIGIT, NULL, EXIT_FAILURE);
    return ((int)nb);
}


bool is_valid_input(int argc, char**argv, int *vars)
{
    int i;
    int temp;

    i = 1;
    if (argc - 1 == 4)
        vars[4] = -1;
    while (i < argc)
    {
        temp = unsigned_atoi(argv[i]);
        if (i == 1 && !(temp < MAX_PHILO && temp > 0))
            dis_msg(STR_ERR_INPUT_POFLOW, STR_MAX_PHILO, EXIT_FAILURE); 
        vars[i-1] = temp;
        i++;
    }
    return (true);
}

t_philo **init_philos(t_table *table)
{
    t_philo **philos;
    unsigned int i;
    
    philos = malloc(sizeof(t_philo *) * table->nb_philo);
    if (!philos)
        dis_msg(STR_ERR_MALLOC, NULL, EXIT_FAILURE);
    i = 0;
    while (i < table->nb_philo)
    {
        philos[i] = malloc(sizeof(t_philo));
        if (!philos[i])
            dis_msg(STR_ERR_MALLOC, NULL, EXIT_FAILURE);
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
    table->phios = init_philos(table);
    create_global_mutex(table);
    return (table);
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

    return (EXIT_SUCCESS);
}
