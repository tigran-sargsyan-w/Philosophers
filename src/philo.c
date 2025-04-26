/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:44:08 by tsargsya          #+#    #+#             */
/*   Updated: 2025/04/26 18:02:39 by tsargsya         ###   ########.fr       */
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

static int	lock_first_fork(t_philo *philo,
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

static int	lock_second_fork(t_philo *philo,
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

int	try_take_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	first = philo->left_fork;
	second = philo->right_fork;
	if (lock_first_fork(philo, &first, &second) == ERROR)
		return (ERROR);
	return (lock_second_fork(philo, first, second));
}

int	try_eat(t_philo *philo)
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

void	drop_forks(t_philo *philo)
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
