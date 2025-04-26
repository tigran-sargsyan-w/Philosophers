/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:31:48 by tsargsya          #+#    #+#             */
/*   Updated: 2025/04/27 00:11:04 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Entrypoint of the program.
 * @param argc The number of command line arguments.
 * @param argv The command line arguments.
 */
int	main(int argc, char **argv)
{
	t_vars	vars;

	init_all(&vars, argc, argv);
	start_simulation(&vars);
	cleanup_and_exit(&vars);
	return (0);
}
