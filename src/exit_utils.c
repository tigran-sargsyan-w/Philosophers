/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:31:19 by tsargsya          #+#    #+#             */
/*   Updated: 2025/04/24 21:57:07 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_error(const char *msg)
{
	if (!msg)
		return ;
	write(2, "Error: ", 7);
	while (*msg)
		write(2, msg++, 1);
	write(2, "\n", 1);
}

void	free_all_resources(t_vars *vars)
{
	int	i;

	if (!vars)
		return ;
	i = 0;
	pthread_mutex_destroy(&vars->print_lock);
	pthread_mutex_destroy(&vars->simulation_lock);
	if (vars->forks)
	{
		while (i < vars->rules.philo_count)
		{
			if (&vars->forks[i])
				pthread_mutex_destroy(&vars->forks[i]);
			i++;
		}
	}
	if (vars->forks)
		free(vars->forks);
	if (vars->philos)
		free(vars->philos);
}

void	cleanup_and_error_exit(t_vars *vars, char *msg)
{
	free_all_resources(vars);
	print_error(msg);
	exit(EXIT_FAILURE);
}

void	cleanup_and_exit(t_vars *vars)
{
	free_all_resources(vars);
	exit(EXIT_SUCCESS);
}
