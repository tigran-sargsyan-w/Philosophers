/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:07:01 by tsargsya          #+#    #+#             */
/*   Updated: 2025/04/03 16:07:04 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_rules(int argc, char **argv, t_vars *vars)
{
	t_rules	*rules;

	rules = &vars->rules;
	if (argc != 5 && argc != 6)
		cleanup_and_error_exit(vars, "invalid argument count");
	if (try_parse_int(argv[1], &rules->philo_count) != SUCCESS)
		cleanup_and_error_exit(vars, "invalid value: number_of_philosophers");
	if (rules->philo_count == 0 || rules->philo_count > 200)
		cleanup_and_error_exit(vars, "invalid range of philosophers (1-200)");
	if (try_parse_int(argv[2], &rules->time_to_die) != SUCCESS)
		cleanup_and_error_exit(vars, "invalid value: time_to_die");
	if (try_parse_int(argv[3], &rules->time_to_eat) != SUCCESS)
		cleanup_and_error_exit(vars, "invalid value: time_to_eat");
	if (rules->time_to_eat == 0)
		cleanup_and_error_exit(vars, "invalid range: time_to_eat must be > 0");
	if (try_parse_int(argv[4], &rules->time_to_sleep) != SUCCESS)
		cleanup_and_error_exit(vars, "invalid value: time_to_sleep");
	rules->must_eat_count = -1;
	if (argc == 6)
	{
		if (try_parse_int(argv[5], &rules->must_eat_count) != SUCCESS)
			cleanup_and_error_exit(vars,
				"invalid value: number_of_times_each_philosopher_must_eat");
	}
}

void	init_mutexes(t_vars *vars)
{
	int	i;

	vars->forks = malloc(sizeof(pthread_mutex_t) * vars->rules.philo_count);
	if (!vars->forks)
		cleanup_and_error_exit(vars, "malloc: forks");
	i = 0;
	while (i < vars->rules.philo_count)
	{
		if (pthread_mutex_init(&vars->forks[i], NULL) != 0)
			cleanup_and_error_exit(vars, "pthread_mutex_init: fork");
		i++;
	}
	if (pthread_mutex_init(&vars->print_lock, NULL) != 0)
		cleanup_and_error_exit(vars, "pthread_mutex_init: print_lock");
	if (pthread_mutex_init(&vars->simulation_lock, NULL) != 0)
		cleanup_and_error_exit(vars, "pthread_mutex_init: simulation_lock");
}

void	init_philosophers(t_vars *vars)
{
	int	i;

	vars->philos = malloc(sizeof(t_philo) * vars->rules.philo_count);
	if (!vars->philos)
		cleanup_and_error_exit(vars, "malloc: philosophers");
	i = 0;
	while (i < vars->rules.philo_count)
	{
		vars->philos[i].id = i + 1;
		vars->philos[i].meals_eaten = 0;
		vars->philos[i].last_meal = 0;
		vars->philos[i].thread = 0;
		vars->philos[i].left_fork = &vars->forks[i];
		vars->philos[i].right_fork = &vars->forks[(i + 1)
			% vars->rules.philo_count];
		vars->philos[i].vars = vars;
		i++;
	}
}

void	init_all(t_vars *vars, int argc, char **argv)
{
	vars->forks = NULL;
	vars->philos = NULL;
	vars->simulation_end = 0;
	vars->start_time = 0;
	init_rules(argc, argv, vars);
	init_mutexes(vars);
	init_philosophers(vars);
}
