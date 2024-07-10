/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:49:06 by svilla-d          #+#    #+#             */
/*   Updated: 2024/07/10 12:56:45 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	close_semaphores(t_philo *philos)
{
	int		i;
	char	str[2];

	if (sem_close(philos->table->sem->die) == -1)
		ft_error_philo(philos, "failed to create semaphore: die");
	sem_unlink("/die");
	if (sem_close(philos->table->sem->forks) == -1)
		ft_error_philo(philos, "failed to create semaphore: die");
	sem_unlink("/forks");
	if (sem_close(philos->table->sem->print) == -1)
		ft_error_philo(philos, "failed to create semaphore: die");
	sem_unlink("/print");
	i = -1;
	while (++i < philos->table->seats)
	{
		str[0] = (char)i;
		str[1] = '\0';
		if (sem_close(philos[i].sem_eat) == -1)
			ft_error_philo(philos, "failed to create semaphore: die");
		sem_unlink(str);
	}
}

static void	create_semaphores(t_semaphore *semaphore, t_table *table)
{
	semaphore->die = NULL;
	semaphore->forks = NULL;
	semaphore->print = NULL;
	sem_unlink("/die");
	semaphore->die = sem_open("/die", O_CREAT, 0644, 1);
	if (semaphore->die == SEM_FAILED)
		ft_error_table(table, "failed to create semaphore: die");
	sem_unlink("/forks");
	semaphore->forks = sem_open("/forks", O_CREAT, 0644, table->seats);
	if (semaphore->forks == SEM_FAILED)
		ft_error_table(table, "failed to create semaphore: forks");
	sem_unlink("/print");
	semaphore->print = sem_open("/print", O_CREAT, 0644, 1);
	if (semaphore->print == SEM_FAILED)
		ft_error_table(table, "failed to create semaphore: print");
}

t_semaphore	*init_semaphore(t_table *table)
{
	t_semaphore	*semaphore;

	semaphore = (t_semaphore *)malloc(sizeof(t_semaphore));
	if (!semaphore)
		ft_error_table(table, "failed to allocate memory: semaphore");
	create_semaphores(semaphore, table);
	return (semaphore);
}
