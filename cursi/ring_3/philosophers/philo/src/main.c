/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:29:48 by svilla-d          #+#    #+#             */
/*   Updated: 2024/07/09 12:43:59 by svilla-d         ###   ########.fr       */
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
	while (!all_philosophers_finished(table))
	{
		if (table->dead)
		{
			if (pthread_mutex_lock(table->mutex->print) != 0)
				ft_error_philo(table, "failed to lock print");
			break ;
		}
	}
	if (pthread_mutex_unlock(table->mutex->print) != 0)
		ft_error_philo(table, "failed to unlock print");
	delete_mutex(table);
	free_table(table);
	return (0);
}
