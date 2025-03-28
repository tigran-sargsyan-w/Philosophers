/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:21:13 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/28 12:22:48 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
