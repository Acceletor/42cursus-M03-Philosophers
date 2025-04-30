# ifndef PHILO_H
#  define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <limits.h>
#include <sys/time.h>
#include <stdbool.h>

/******************************************************************************
*                                     Macros                                  *
******************************************************************************/

# define MAX_PHILO 250
# define STR_MAX_PHILO "250"

# define NC		"\e[0m"
# define RED	"\e[31m"
# define GREEN	"\e[32m"
# define PURPLE	"\e[35m"
# define CYAN	"\e[36m"

# define STR_PROG_NAME	"(philo)"
# define STR_USAGE	"%s Usage: ./philo <number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_must_eat]\n"
# define STR_ERR_INPUT_DIGIT	"%s Invalid input: \
a valid unsigned integer is between 0 and 2147483647.\n"
# define STR_ERR_INPUT_POFLOW	"%s Invalid input: \
there must be between 1 and %s philosophers.\n"
# define STR_ERR_THREAD	"%s Error: Could not create thread.\n"
# define STR_ERR_MALLOC	"%s Error: Could not allocate memory.\n"
# define STR_ERR_MUTEX	"%s Error: Could not create mutex.\n"




# endif 

