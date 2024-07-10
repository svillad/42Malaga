/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:29:48 by svilla-d          #+#    #+#             */
/*   Updated: 2024/07/10 14:45:22 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	int		i;
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
	i = 0;
	while (i < table->seats)
	{
		philosophers[i].pid = fork();
		if (philosophers[i].pid < 0)
			ft_error_philo(philosophers, "failed creating process");
		else if (philosophers[i].pid == 0)
			routine(&philosophers[i]);
		i++;
	}
	end_processes(philosophers);
	free_philo(philosophers);
	return (0);
}
