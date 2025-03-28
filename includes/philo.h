/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:33:00 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/28 15:31:33 by tsargsya         ###   ########.fr       */
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

int						try_parse_int(const char *str, int *out);
void					cleanup_and_exit(t_vars *vars);
void					cleanup_and_error_exit(t_vars *vars, char *msg);

#endif