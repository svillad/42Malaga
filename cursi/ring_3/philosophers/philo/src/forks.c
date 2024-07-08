/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 08:14:48 by svilla-d          #+#    #+#             */
/*   Updated: 2024/07/09 08:31:38 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_fork(t_philo *philo, int fork, t_table *table)
{
	if (pthread_mutex_lock(&table->mutex->forks[fork]) != 0)
		ft_error_philo(table, "failed to lock fork");
	table->forks_locked[fork] = LOCK;
	print_time(philo, TAKING_FORK, table);
}

void	unlock_fork(t_philo *philo, int fork, t_table *table)
{
	if (pthread_mutex_unlock(&table->mutex->forks[fork]) != 0)
		ft_error_philo(table, "failed to unlock fork");
	table->forks_locked[fork] = UNLOCK;
	print_time(philo, NOPRINT, table);
}

int	try_to_lock_forks(t_philo *philo, t_table *table)
{
	if (table->forks_locked[philo->fork_left] == UNLOCK
		&& table->forks_locked[philo->fork_right] == UNLOCK)
	{
		lock_fork(philo, philo->fork_left, table);
		if (table->forks_locked[philo->fork_right] == UNLOCK)
		{
			lock_fork(philo, philo->fork_right, table);
			return (TRUE);
		}
		else if (table->seats == 1)
		{
			while (table->dead == 0)
				usleep(100);
			return (TRUE);
		}
		else
		{
			unlock_fork(philo, philo->fork_left, table);
			print_time(philo, THINKING, table);
			pausing_philo(table, time_to_think(philo, table));
		}
	}
	return (FALSE);
}

void	picking_forks(t_philo *philo, t_table *table)
{
	while (!try_to_lock_forks(philo, table))
		;
	eating(philo, table);
	unlock_fork(philo, philo->fork_left, table);
	if (table->seats != 1)
		unlock_fork(philo, philo->fork_right, table);
}
