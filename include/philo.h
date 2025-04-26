/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:33:00 by tsargsya          #+#    #+#             */
/*   Updated: 2025/04/26 22:44:48 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define SUCCESS 0
# define ERROR 1

typedef struct s_philo	t_philo;
typedef struct s_vars	t_vars;
typedef struct s_rules	t_rules;

typedef struct s_rules
{
	int					philo_count;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					must_eat_count;
}						t_rules;

typedef struct s_vars
{
	long				start_time;
	int					simulation_end;

	pthread_t			monitor;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_lock;
	pthread_mutex_t		simulation_lock;

	t_rules				rules;
	t_philo				*philos;
}						t_vars;

typedef struct s_philo
{
	int					id;
	int					meals_eaten;
	long				last_meal;
	pthread_t			thread;

	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;

	t_vars				*vars;
}						t_philo;

// exit_utils.c
void					cleanup_and_exit(t_vars *vars);
void					cleanup_and_error_exit(t_vars *vars, char *msg);

// init.c
void					init_all(t_vars *vars, int argc, char **argv);

// monitoring.c
void					*monitor_routine(void *arg);

// philo_utils.c
void					sort_forks(pthread_mutex_t **first,
							pthread_mutex_t **second);
int						lock_first_fork(t_philo *philo,
							pthread_mutex_t **first,
							pthread_mutex_t **second);
int						lock_second_fork(t_philo *philo,
							pthread_mutex_t *first,
							pthread_mutex_t *second);

// philo.c
void					*philo_routine(void *arg);
long					get_time_in_ms(void);
void					smart_sleep(long duration, t_vars *vars);
void					log_action(t_philo *philo, const char *msg);

// simulation.c
void					set_simulation_end(t_vars *vars);
int						is_simulation_ended(t_vars *vars);
void					start_simulation(t_vars *vars);

// utils.c
int						try_parse_int(const char *str, int *out);

#endif