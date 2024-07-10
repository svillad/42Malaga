/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 08:14:48 by svilla-d          #+#    #+#             */
/*   Updated: 2024/07/10 14:00:51 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	picking_forks(t_philo *p)
{
	if (sem_wait(p->table->sem->forks) == -1)
		ft_error_philo(p, "failed to lock a fork");
	print_time(p, TAKING_FORK);
	if (p->table->seats == 1)
	{
		while (p->table->dead == FALSE)
			usleep(100);
	}
	else
	{
		if (sem_wait(p->table->sem->forks) == -1)
			ft_error_philo(p, "failed to lock a fork");
		print_time(p, TAKING_FORK);
	}
	if (p->table->dead == FALSE)
	{
		eating(p);
		if (sem_post(p->table->sem->forks) == -1)
			ft_error_philo(p, "failed to unlock a fork");
		if (p->table->seats != 1)
			if (sem_post(p->table->sem->forks) == -1)
				ft_error_philo(p, "failed to unlock a fork");
	}
}
