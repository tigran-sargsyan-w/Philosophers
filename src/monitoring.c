/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 19:18:40 by tsargsya          #+#    #+#             */
/*   Updated: 2025/04/27 00:14:39 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Handles the case when all philosophers have eaten 
 * the required number of meals.
 * @param vars The simulation variables structure.
 */
static void	handle_all_philos_satisfied(t_vars *vars)
{
	pthread_mutex_lock(&vars->print_lock);
	printf("Each philosopher ate %d time(s)\n", vars->rules.must_eat_count);
	pthread_mutex_unlock(&vars->print_lock);
	set_simulation_end(vars);
}

/**
 * @brief Checks if any philosopher has died.
 * @param vars The simulation variables structure.
 * @return 1 if a philosopher has died, 0 otherwise.
 */
static int	check_if_any_philo_died(t_vars *vars)
{
	int		i;
	t_philo	*philo;
	long	time_since_last_meal;

	i = 0;
	while (i < vars->rules.philo_count)
	{
		philo = &vars->philos[i];
		pthread_mutex_lock(&philo->vars->simulation_lock);
		time_since_last_meal = get_time_in_ms() - philo->last_meal;
		pthread_mutex_unlock(&philo->vars->simulation_lock);
		if (time_since_last_meal > vars->rules.time_to_die)
		{
			set_simulation_end(vars);
			log_action(philo, "died");
			return (1);
		}
		i++;
	}
	return (0);
}

/**
 * @brief Checks if all philosophers have eaten the required number of meals.
 * @param vars The simulation variables structure.
 * @return 1 if all philosophers have eaten enough, 0 otherwise.
 */
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
		pthread_mutex_lock(&philo->vars->simulation_lock);
		if (philo->meals_eaten >= vars->rules.must_eat_count)
			count++;
		pthread_mutex_unlock(&philo->vars->simulation_lock);
		i++;
	}
	if (count == vars->rules.philo_count)
	{
		handle_all_philos_satisfied(vars);
		return (1);
	}
	return (0);
}

/**
 * @brief Monitors the simulation and checks for conditions to end it.
 * @param arg The simulation variables structure.
 * @return NULL.
 */
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
	return (NULL);
}
