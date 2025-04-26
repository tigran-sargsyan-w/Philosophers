/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:31:48 by tsargsya          #+#    #+#             */
/*   Updated: 2025/04/26 22:10:29 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_vars	vars;

	init_all(&vars, argc, argv);
	start_simulation(&vars);
	cleanup_and_exit(&vars);
	return (0);
}
