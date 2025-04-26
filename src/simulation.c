/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:41:48 by tsargsya          #+#    #+#             */
/*   Updated: 2025/04/27 00:19:45 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Sets the simulation end flag to 1.
 * @param vars The variables structure.
 */
void	set_simulation_end(t_vars *vars)
{
	pthread_mutex_lock(&vars->simulation_lock);
	vars->simulation_end = 1;
	pthread_mutex_unlock(&vars->simulation_lock);
}

/**
 * @brief Checks if the simulation has ended.
 * @param vars The variables structure.
 * @return 1 if the simulation has ended, 0 otherwise.
 */
int	is_simulation_ended(t_vars *vars)
{
	int	end;

	pthread_mutex_lock(&vars->simulation_lock);
	end = vars->simulation_end;
	pthread_mutex_unlock(&vars->simulation_lock);
	return (end);
}

/**
 * @brief Starts the simulation.
 * @param vars The variables structure.
 */
void	start_simulation(t_vars *vars)
{
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
	if (pthread_create(&vars->monitor, NULL, &monitor_routine, vars) != 0)
		cleanup_and_error_exit(vars, "pthread_create (monitor)");
	if (pthread_join(vars->monitor, NULL) != 0)
		cleanup_and_error_exit(vars, "pthread_join (monitor)");
	i = 0;
	while (i < vars->rules.philo_count)
	{
		if (pthread_join(vars->philos[i].thread, NULL) != 0)
			cleanup_and_error_exit(vars, "pthread_join");
		i++;
	}
}
