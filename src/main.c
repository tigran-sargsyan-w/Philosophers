/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:31:48 by tsargsya          #+#    #+#             */
/*   Updated: 2025/04/06 18:56:15 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_action(t_philo *philo, const char *msg)
{
	t_vars	*vars;

	vars = philo->vars;
	pthread_mutex_lock(&vars->print_lock);
	printf("%ld %d %s\n", get_time_in_ms() - vars->start_time, philo->id, msg);
	pthread_mutex_unlock(&vars->print_lock);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		smart_sleep(philo->vars->rules.time_to_eat / 10, philo->vars);
	while (!is_simulation_ended(philo->vars))
	{
		// 1. TAKE FORKS
		if (is_simulation_ended(philo->vars))
			break ;
		pthread_mutex_lock(philo->left_fork);
		if (is_simulation_ended(philo->vars))
		{
			pthread_mutex_unlock(philo->left_fork);
			break ;
		}
		log_action(philo, "has taken a fork");
		if (is_simulation_ended(philo->vars))
		{
			pthread_mutex_unlock(philo->left_fork);
			break ;
		}
		if (!philo->right_fork)
		{
			smart_sleep(philo->vars->rules.time_to_die, philo->vars);
			pthread_mutex_unlock(philo->left_fork);
			return (NULL);
		}
		pthread_mutex_lock(philo->right_fork);
		if (is_simulation_ended(philo->vars))
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			break ;
		}
		log_action(philo, "has taken a fork");
		// 2. EAT
		if (is_simulation_ended(philo->vars))
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			break ;
		}
		log_action(philo, "is eating");
		philo->last_meal = get_time_in_ms();
		philo->meals_eaten++;
		smart_sleep(philo->vars->rules.time_to_eat, philo->vars);
		// 3. DROP FORKS
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		// 4. SLEEP
		if (is_simulation_ended(philo->vars))
			break ;
		log_action(philo, "is sleeping");
		smart_sleep(philo->vars->rules.time_to_sleep, philo->vars);
		// 5. THINK
		if (is_simulation_ended(philo->vars))
			break ;
		log_action(philo, "is thinking");
	}
	return (NULL);
}

void	start_simulation(t_vars *vars)
{
	pthread_t	monitor;
	int			i;

	vars->start_time = get_time_in_ms();
	i = 0;
	while (i < vars->rules.philo_count)
	{
		vars->philos[i].last_meal = vars->start_time;
		if (pthread_create(&vars->philos[i].thread, NULL, &philo_routine,
				&vars->philos[i]) != 0)
			cleanup_and_error_exit(vars, "pthread_create");
		i++;
	}
	if (pthread_create(&monitor, NULL, &monitor_routine, vars) != 0)
		cleanup_and_error_exit(vars, "pthread_create (monitor)");
	if (pthread_join(monitor, NULL) != 0)
		cleanup_and_error_exit(vars, "pthread_join (monitor)");
	i = 0;
	while (i < vars->rules.philo_count)
	{
		if (pthread_join(vars->philos[i].thread, NULL) != 0)
			cleanup_and_error_exit(vars, "pthread_join");
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	init_all(&vars, argc, argv);
	start_simulation(&vars);
	cleanup_and_exit(&vars);
	return (0);
}
