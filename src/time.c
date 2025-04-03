/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 18:27:33 by tsargsya          #+#    #+#             */
/*   Updated: 2025/04/03 15:55:11 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

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
