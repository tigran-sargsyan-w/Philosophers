/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:44:08 by tsargsya          #+#    #+#             */
/*   Updated: 2025/04/09 12:49:31 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


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
