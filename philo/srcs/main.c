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

    // *vars = malloc(sizeof(int)* 5);
    // if (!*vars)
    //     dis_msg(STR_ERR_MALLOC, NULL, EXIT_FAILURE);
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


int main(int argc, char **argv)
{
    int vars[5];
    if (argc - 1 < 4 || argc - 1 > 5)
        dis_msg(STR_USAGE, NULL, EXIT_FAILURE);
    if (!is_valid_input(argc, argv, vars))
        return (EXIT_FAILURE);
    for(int i = 0; i < 5; i++)
        printf("%d: %d\n", i, vars[i]);

    return (EXIT_SUCCESS);
}