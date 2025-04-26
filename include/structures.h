/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 23:37:53 by tsargsya          #+#    #+#             */
/*   Updated: 2025/04/26 23:53:02 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <pthread.h>

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

#endif