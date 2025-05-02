#include "../include/philo.h"

// bool start_simulation(t_table *table)
// {
//     // You must implement or remove this declaration if unused.
//     return (true);
// }


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
    // start_simulation(table);
    free_table(table);


    return (EXIT_SUCCESS);
}
