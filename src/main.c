/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:31:48 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/27 18:03:05 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	printf("seconds : %ld\nmicro seconds : %ld",
		current_time.tv_sec,
		current_time.tv_usec);
	return (0);
}
