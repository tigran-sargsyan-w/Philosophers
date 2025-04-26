/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 22:04:25 by tsargsya          #+#    #+#             */
/*   Updated: 2025/04/27 00:22:03 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Tries to parse an integer from a string.
 * @param str The string to parse.
 * @param out Pointer to store the parsed integer.
 * @return SUCCESS if parsing was successful, ERROR otherwise.
 */
int	try_parse_int(const char *str, int *out)
{
	long	num;
	int		i;

	num = 0;
	i = 0;
	if (!str || !str[0])
		return (ERROR);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (ERROR);
		num = num * 10 + (str[i] - '0');
		if (num > INT_MAX)
			return (ERROR);
		i++;
	}
	*out = (int)num;
	return (SUCCESS);
}

/**
 * @brief Gets the current time in milliseconds.
 * @return The current time in milliseconds.
 */
long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/**
 * @brief Sleeps for a specified duration,
 * checking if the simulation has ended.
 * @param duration The duration to sleep in milliseconds.
 * @param vars The variables structure.
 */
void	smart_sleep(long duration, t_vars *vars)
{
	long	start;

	start = get_time_in_ms();
	while (!is_simulation_ended(vars))
	{
		if (get_time_in_ms() - start >= duration)
			break ;
		usleep(500);
	}
}

/**
 * @brief Logs an action with a timestamp.
 * @param philo The philosopher structure.
 * @param msg The message to log.
 */
void	log_action(t_philo *philo, const char *msg)
{
	t_vars	*vars;

	vars = philo->vars;
	pthread_mutex_lock(&vars->print_lock);
	printf("%ld %d %s\n", get_time_in_ms() - vars->start_time, philo->id, msg);
	pthread_mutex_unlock(&vars->print_lock);
}
