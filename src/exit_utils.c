/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:31:19 by tsargsya          #+#    #+#             */
/*   Updated: 2025/04/27 00:06:41 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Prints an error message to stderr.
 * @param msg The error message to print.
 */
static void	print_error(const char *msg)
{
	if (!msg)
		return ;
	write(2, "Error: ", 7);
	while (*msg)
		write(2, msg++, 1);
	write(2, "\n", 1);
}

/**
 * @brief Destroys all mutexes used in the simulation.
 * @param vars The simulation variables structure.
 */
static void	destroy_mutexes(t_vars *vars)
{
	int	i;

	if (!vars)
		return ;
	pthread_mutex_destroy(&vars->print_lock);
	pthread_mutex_destroy(&vars->simulation_lock);
	if (vars->forks)
	{
		i = 0;
		while (i < vars->rules.philo_count)
		{
			pthread_mutex_destroy(&vars->forks[i]);
			i++;
		}
	}
}

/**
 * @brief Frees all allocated resources in the simulation.
 * @param vars The simulation variables structure.
 */
static void	free_all_resources(t_vars *vars)
{
	if (!vars)
		return ;
	if (vars->forks)
		free(vars->forks);
	if (vars->philos)
		free(vars->philos);
}

/**
 * @brief Cleans up resources and exits the program with an error message.
 * @param vars The simulation variables structure.
 * @param msg The error message to print.
 */
void	cleanup_and_error_exit(t_vars *vars, char *msg)
{
	destroy_mutexes(vars);
	free_all_resources(vars);
	print_error(msg);
	exit(EXIT_FAILURE);
}

/**
 * @brief Cleans up resources and exits the program successfully.
 * @param vars The simulation variables structure.
 */
void	cleanup_and_exit(t_vars *vars)
{
	destroy_mutexes(vars);
	free_all_resources(vars);
	exit(EXIT_SUCCESS);
}
