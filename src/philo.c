/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:44:08 by tsargsya          #+#    #+#             */
/*   Updated: 2025/04/27 00:17:59 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Tries to take forks for the philosopher.
 * @param philo The philosopher structure.
 * @return SUCCESS or ERROR.
 */
static int	try_take_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	first = philo->left_fork;
	second = philo->right_fork;
	if (lock_first_fork(philo, &first, &second) == ERROR)
		return (ERROR);
	return (lock_second_fork(philo, first, second));
}

/**
 * @brief Tries to eat for the philosopher.
 * @param philo The philosopher structure.
 * @return SUCCESS or ERROR.
 */
static int	try_eat(t_philo *philo)
{
	if (is_simulation_ended(philo->vars))
		return (ERROR);
	log_action(philo, "is eating");
	pthread_mutex_lock(&philo->vars->simulation_lock);
	philo->last_meal = get_time_in_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->vars->simulation_lock);
	smart_sleep(philo->vars->rules.time_to_eat, philo->vars);
	if (is_simulation_ended(philo->vars))
		return (ERROR);
	return (SUCCESS);
}

/**
 * @brief Drops the forks held by the philosopher.
 * @param philo The philosopher structure.
 */
static void	drop_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	first = philo->left_fork;
	second = philo->right_fork;
	sort_forks(&first, &second);
	if (second)
		pthread_mutex_unlock(second);
	if (first)
		pthread_mutex_unlock(first);
}

/**
 * @brief Tries to sleep and think for the philosopher.
 * @param philo The philosopher structure.
 * @return SUCCESS or ERROR.
 */
static int	try_sleep_think(t_philo *philo)
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

/**
 * @brief The main routine for each philosopher thread.
 * @param arg The philosopher structure.
 * @return NULL.
 */
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
