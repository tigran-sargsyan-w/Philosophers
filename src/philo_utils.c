/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 22:28:17 by tsargsya          #+#    #+#             */
/*   Updated: 2025/04/27 00:16:08 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Sorts the forks to ensure a consistent order.
 * @param first The first fork.
 * @param second The second fork.
 */
void	sort_forks(pthread_mutex_t **first, pthread_mutex_t **second)
{
	pthread_mutex_t	*tmp;

	if (*second && *first > *second)
	{
		tmp = *first;
		*first = *second;
		*second = tmp;
	}
}

/**
 * @brief Locks the first fork and checks for simulation end.
 * @param philo The philosopher structure.
 * @param first The first fork.
 * @param second The second fork.
 * @return SUCCESS or ERROR.
 */
int	lock_first_fork(t_philo *philo,
							pthread_mutex_t **first,
							pthread_mutex_t **second)
{
	sort_forks(first, second);
	if (is_simulation_ended(philo->vars))
		return (ERROR);
	pthread_mutex_lock(*first);
	if (is_simulation_ended(philo->vars))
	{
		pthread_mutex_unlock(*first);
		return (ERROR);
	}
	log_action(philo, "has taken a fork");
	if (!*second)
	{
		smart_sleep(philo->vars->rules.time_to_die,
			philo->vars);
		pthread_mutex_unlock(*first);
		return (ERROR);
	}
	return (SUCCESS);
}

/**
 * @brief Locks the second fork and checks for simulation end.
 * @param philo The philosopher structure.
 * @param first The first fork.
 * @param second The second fork.
 * @return SUCCESS or ERROR.
 */
int	lock_second_fork(t_philo *philo,
							pthread_mutex_t *first,
							pthread_mutex_t *second)
{
	pthread_mutex_lock(second);
	if (is_simulation_ended(philo->vars))
	{
		pthread_mutex_unlock(second);
		pthread_mutex_unlock(first);
		return (ERROR);
	}
	log_action(philo, "has taken a fork");
	return (SUCCESS);
}
