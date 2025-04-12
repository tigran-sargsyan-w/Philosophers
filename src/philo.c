/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:44:08 by tsargsya          #+#    #+#             */
/*   Updated: 2025/04/12 20:56:38 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	try_take_forks(t_philo *philo)
{
	if (is_simulation_ended(philo->vars))
		return (ERROR);
	pthread_mutex_lock(philo->left_fork);
	if (is_simulation_ended(philo->vars))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (ERROR);
	}
	log_action(philo, "has taken a fork");
	if (!philo->right_fork)
	{
		smart_sleep(philo->vars->rules.time_to_die, philo->vars);
		pthread_mutex_unlock(philo->left_fork);
		return (ERROR);
	}
	pthread_mutex_lock(philo->right_fork);
	if (is_simulation_ended(philo->vars))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (ERROR);
	}
	log_action(philo, "has taken a fork");
	return (SUCCESS);
}

int	try_eat(t_philo *philo)
{
	if (is_simulation_ended(philo->vars))
		return (ERROR);
	log_action(philo, "is eating");
	philo->last_meal = get_time_in_ms();
	philo->meals_eaten++;
	smart_sleep(philo->vars->rules.time_to_eat, philo->vars);
	if (is_simulation_ended(philo->vars))
		return (ERROR);
	return (SUCCESS);
}

void	drop_forks(t_philo *philo)
{
	if (philo->left_fork)
		pthread_mutex_unlock(philo->left_fork);
	if (philo->right_fork)
		pthread_mutex_unlock(philo->right_fork);
}

int	try_sleep_think(t_philo *philo)
{
	if (is_simulation_ended(philo->vars))
		return (ERROR);
	log_action(philo, "is sleeping");
	smart_sleep(philo->vars->rules.time_to_sleep, philo->vars);
	if (is_simulation_ended(philo->vars))
		return (ERROR);
	log_action(philo, "is thinking");
	return (SUCCESS);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		smart_sleep(philo->vars->rules.time_to_eat / 10, philo->vars);
	while (!is_simulation_ended(philo->vars))
	{
		if (try_take_forks(philo) == ERROR)
			break ;
		if (try_eat(philo) == ERROR)
		{
			drop_forks(philo);
			break ;
		}
		drop_forks(philo);
		if (try_sleep_think(philo) == ERROR)
			break ;
	}
	return (NULL);
}
