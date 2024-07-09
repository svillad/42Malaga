/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 08:14:48 by svilla-d          #+#    #+#             */
/*   Updated: 2024/07/09 18:37:47 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	lock_fork(t_philo *p, int fork_id)
{
	t_table	*table;

	table = p->table;
	if (pthread_mutex_lock(&table->mutex->forks[fork_id]) != 0)
		ft_error_philo(p, "failed to lock fork");
	table->forks[fork_id] = LOCK;
	print_time(p, TAKING_FORK);
}

static void	unlock_fork(t_philo *p, int fork_id)
{
	t_table	*table;

	table = p->table;
	if (pthread_mutex_unlock(&table->mutex->forks[fork_id]) != 0)
		ft_error_philo(p, "failed to unlock fork");
	table->forks[fork_id] = UNLOCK;
	print_time(p, NOPRINT);
}

static int	try_to_lock_forks(t_philo *p)
{
	if (p->table->forks[p->fork_left] == UNLOCK
		&& p->table->forks[p->fork_right] == UNLOCK)
	{
		lock_fork(p, p->fork_left);
		if (p->table->forks[p->fork_right] == UNLOCK)
		{
			lock_fork(p, p->fork_right);
			return (TRUE);
		}
		else if (p->table->seats == 1)
		{
			while (p->table->dead == 0)
				usleep(100);
			return (TRUE);
		}
		else
		{
			unlock_fork(p, p->fork_left);
			print_time(p, THINKING);
			pausing_philo(p, time_to_think(p));
		}
	}
	return (FALSE);
}

void	picking_forks(t_philo *p)
{
	while (!try_to_lock_forks(p))
		;
	eating(p);
	unlock_fork(p, p->fork_left);
	if (p->table->seats != 1)
		unlock_fork(p, p->fork_right);
}
