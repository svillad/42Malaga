/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:29:48 by svilla-d          #+#    #+#             */
/*   Updated: 2024/07/12 17:26:10 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo	*philosophers;
	t_table	*table;

	if (argc < 5 || argc > 6)
		ft_error_philo(NULL, "Incorrect number of arguments");
	validate_arguments(argc, argv);
	table = init_table(argv);
	philosophers = (t_philo *)malloc(ft_atoi(argv[1]) * sizeof(t_philo));
	if (!philosophers)
		ft_error_table(table, "failed to allocate memory");
	init_philosophers(philosophers, table);
	while (!all_philosophers_finished(philosophers))
	{
		if (table->dead)
		{
			if (pthread_mutex_lock(table->mutex->print) != 0)
				ft_error_philo(philosophers, "failed to lock print");
			break ;
		}
	}
	if (pthread_mutex_unlock(table->mutex->print) != 0)
		ft_error_philo(philosophers, "failed to unlock print");
	free_philo(philosophers);
	return (0);
}
