/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:31:48 by tsargsya          #+#    #+#             */
/*   Updated: 2025/04/09 12:44:13 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_action(t_philo *philo, const char *msg)
{
	t_vars	*vars;

	vars = philo->vars;
	pthread_mutex_lock(&vars->print_lock);
	printf("%ld %d %s\n", get_time_in_ms() - vars->start_time, philo->id, msg);
	pthread_mutex_unlock(&vars->print_lock);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	init_all(&vars, argc, argv);
	start_simulation(&vars);
	cleanup_and_exit(&vars);
	return (0);
}
