/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 22:28:17 by tsargsya          #+#    #+#             */
/*   Updated: 2025/04/26 22:36:46 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
