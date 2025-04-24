/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 19:18:40 by tsargsya          #+#    #+#             */
/*   Updated: 2025/04/24 17:36:02 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	handle_all_philos_satisfied(t_vars *vars)
{
	pthread_mutex_lock(&vars->print_lock);
	printf("Each philosopher ate %d time(s)\n", vars->rules.must_eat_count);
	pthread_mutex_unlock(&vars->print_lock);
	set_simulation_end(vars);
	cleanup_and_exit(vars);
}

static int	check_if_any_philo_died(t_vars *vars)
{
	int		i;
	t_philo	*philo;
	long	time_since_last_meal;

	i = 0;
	while (i < vars->rules.philo_count)
	{
		philo = &vars->philos[i];
		time_since_last_meal = get_time_in_ms() - philo->last_meal;
		if (time_since_last_meal > vars->rules.time_to_die)
		{
			set_simulation_end(vars);
			log_action(philo, "died");
			cleanup_and_exit(vars);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	check_if_all_philos_ate_enough(t_vars *vars)
{
	int		i;
	int		count;
	t_philo	*philo;

	if (vars->rules.must_eat_count <= 0)
		return (0);
	i = 0;
	count = 0;
	while (i < vars->rules.philo_count)
	{
		philo = &vars->philos[i];
		if (philo->meals_eaten >= vars->rules.must_eat_count)
			count++;
		i++;
	}
	if (count == vars->rules.philo_count)
	{
		handle_all_philos_satisfied(vars);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_vars	*vars;

	vars = (t_vars *)arg;
	while (!is_simulation_ended(vars))
	{
		if (check_if_any_philo_died(vars))
			break ;
		if (check_if_all_philos_ate_enough(vars))
			break ;
		usleep(500);
	}
	cleanup_and_exit(vars);
	return (NULL);
}
