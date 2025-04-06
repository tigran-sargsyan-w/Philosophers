/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 19:18:40 by tsargsya          #+#    #+#             */
/*   Updated: 2025/04/06 15:43:21 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_simulation_ended(t_vars *vars)
{
	int	end;

	pthread_mutex_lock(&vars->simulation_lock);
	end = vars->simulation_end;
	pthread_mutex_unlock(&vars->simulation_lock);
	return (end);
}

void	set_simulation_end(t_vars *vars)
{
	pthread_mutex_lock(&vars->simulation_lock);
	vars->simulation_end = 1;
	pthread_mutex_unlock(&vars->simulation_lock);
}

void	*monitor_routine(void *arg)
{
	t_vars	*vars;
	t_philo	*philo;
	long	time_since_last_meal;
	int		i;
	int		full_count;

	vars = (t_vars *)arg;
	while (!is_simulation_ended(vars))
	{
		i = 0;
		full_count = 0;
		while (i < vars->rules.philo_count)
		{
			philo = &vars->philos[i];
			time_since_last_meal = get_time_in_ms() - philo->last_meal;
			if (time_since_last_meal > vars->rules.time_to_die)
			{
				set_simulation_end(vars);
				log_action(philo, "died");
				return (NULL);
			}
			if (vars->rules.must_eat_count > 0
				&& philo->meals_eaten >= vars->rules.must_eat_count)
				full_count++;
			i++;
		}
		if (vars->rules.must_eat_count > 0
			&& full_count == vars->rules.philo_count)
		{
			pthread_mutex_lock(&vars->print_lock);
			printf("Each philosopher ate %d time(s)\n",
				vars->rules.must_eat_count);
			pthread_mutex_unlock(&vars->print_lock);
			set_simulation_end(vars);
			return (NULL);
		}
		usleep(500);
	}
	return (NULL);
}
