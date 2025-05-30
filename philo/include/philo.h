/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuebtha <ksuebtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:49:40 by ksuebtha          #+#    #+#             */
/*   Updated: 2025/05/28 16:22:34 by ksuebtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>
# include <stdbool.h>

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

typedef struct s_philo	t_philo;

typedef struct s_table
{
	time_t			start_time;
	unsigned int	nb_philo;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				must_eat_count;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	sim_stop_lock;
	bool			print_lock_init;
	bool			sim_stop_lock_init;
	pthread_t		monitor_thread;
	bool			sim_stop;
	t_philo			**philos;
}					t_table;

typedef struct s_philo
{
	pthread_t		philo;
	unsigned int	id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	time_t			lastmeal;
	int				eat_count;
	t_table			*table;

}					t_philo;

// parsing.c
bool			is_valid_input(int argc, char**argv, int *vars);
int				unsigned_atoi(char *str);
int				dis_msg(char *str, char *detail, int exit_no);

// init.c 
t_philo			**init_philos(t_table *table);
pthread_mutex_t	*init_fork(unsigned int nb_philo, t_table *table);
bool			create_global_mutex(t_table *table);
t_table			*init_table(int vars[]);

// free.c
void			free_philos(t_table *table, unsigned int j);
void			destroy_forks(t_table *table, unsigned int j);
void			free_table(t_table *table);
void			stop_simulation(t_table *table);

//philosopher.c
void			take_forks(t_philo *philo);
void			eat(t_philo *philo);
void			drop_forks(t_philo *philo);
void			philo_sleep(t_philo *philo);
void			*philo_routine(void *arg);

//monitor_thread.c
void			*monitor_routine(void *arg);

//utils.c
time_t			get_time_in_ms(void);
void			print_action(t_philo *philo, char *msg);
bool			has_sim_stopped(t_table *table);
void			precise_sleep_until(time_t deadline_ms, t_table *table);
void			assign_forks(t_table *table);

//main.c
time_t			get_time_in_ms(void);
void			print_action(t_philo *philo, char *msg);
bool			has_sim_stopped(t_table *table);
bool			start_simulation(t_table *table);

#endif

