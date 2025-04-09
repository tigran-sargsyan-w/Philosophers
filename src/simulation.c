/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:41:48 by tsargsya          #+#    #+#             */
/*   Updated: 2025/04/09 12:48:05 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_simulation_end(t_vars *vars)
{
	pthread_mutex_lock(&vars->simulation_lock);
	vars->simulation_end = 1;
	pthread_mutex_unlock(&vars->simulation_lock);
}

int	is_simulation_ended(t_vars *vars)
{
	int	end;

	pthread_mutex_lock(&vars->simulation_lock);
	end = vars->simulation_end;
	pthread_mutex_unlock(&vars->simulation_lock);
	return (end);
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
