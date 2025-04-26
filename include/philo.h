/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:33:00 by tsargsya          #+#    #+#             */
/*   Updated: 2025/04/26 23:52:04 by tsargsya         ###   ########.fr       */
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
# include "structures.h"

# define SUCCESS 0
# define ERROR 1

void					cleanup_and_exit(t_vars *vars);
void					cleanup_and_error_exit(t_vars *vars, char *msg);
void					init_all(t_vars *vars, int argc, char **argv);
void					*monitor_routine(void *arg);
void					sort_forks(pthread_mutex_t **first,
							pthread_mutex_t **second);
int						lock_first_fork(t_philo *philo,
							pthread_mutex_t **first,
							pthread_mutex_t **second);
int						lock_second_fork(t_philo *philo,
							pthread_mutex_t *first,
							pthread_mutex_t *second);
void					*philo_routine(void *arg);
long					get_time_in_ms(void);
void					smart_sleep(long duration, t_vars *vars);
void					log_action(t_philo *philo, const char *msg);
void					set_simulation_end(t_vars *vars);
int						is_simulation_ended(t_vars *vars);
void					start_simulation(t_vars *vars);
int						try_parse_int(const char *str, int *out);

#endif