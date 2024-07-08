/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:29:48 by svilla-d          #+#    #+#             */
/*   Updated: 2024/07/08 22:29:28 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	*table;

	if (argc < 5 || argc > 6)
		ft_error_philo(NULL, "Incorrect number of arguments");
	validate_arguments(argc, argv);
	table = init_table(argv);
	while (all_finished(table) == 0)
	{
		if (table->dead)
			break ;
	}
	pthread_mutex_unlock(table->mutex->print);
	// destroy_mutex(p, inf);
	free(table->philosophers);
	return (0);
}
