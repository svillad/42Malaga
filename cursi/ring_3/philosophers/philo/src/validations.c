/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:40:53 by svilla-d          #+#    #+#             */
/*   Updated: 2024/07/08 22:25:08 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	validate_arguments(int argc, char **argv)
{
	int			error;
	int			i;
	const char	*msg[] = {NUM_PHILO, TIME_DIE, TIME_EAT, TIME_SLEEP, NUM_EAT};

	error = FALSE;
	i = -1;
	while (++i < argc - 1)
	{
		if (ft_atoi(argv[i + 1]) < 0)
		{
			if (!error)
				printf("❌ Error ❌\n");
			printf(" ► %s should be positive integer.\n", msg[i]);
			error = TRUE;
		}
	}
	if (error)
		exit(EXIT_FAILURE);
}
