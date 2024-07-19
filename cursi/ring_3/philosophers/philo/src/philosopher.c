/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:42:57 by svilla-d          #+#    #+#             */
/*   Updated: 2024/07/19 10:03:21 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	print_time(p, THINKING);
	if (pthread_create(&p->table->monitor[p->id - 1], NULL, &dying_routine,
			p) != 0)
		ft_error_philo(p, "failed to create thread monitor");
	while (!p->table->dead)
	{
		if (p->finished == FALSE)
			picking_forks(p);
		if (p->finished == FALSE && p->table->dead == FALSE)
		{
			print_time(p, SLEEPING);
			pausing_philo(p, p->table->time_to_sleep);
		}
		if (p->finished == FALSE && p->table->dead == FALSE)
		{
			print_time(p, THINKING);
			pausing_philo(p, time_to_think(p));
		}
		else
			break ;
	}
	return (NULL);
}

int	all_philosophers_finished(t_philo *philos)
{
	int	i;
	int	finished;

	finished = TRUE;
	i = -1;
	while (++i < philos->table->seats)
		if (philos[i].finished != TRUE)
			finished = FALSE;
	return (finished);
}

static void	load_philo_info(int i, t_philo *p)
{
	p->id = i + 1;
	p->fork_left = i;
	p->fork_right = i;
	if (p->table->seats != 1)
		p->fork_right = (i + 1) % p->table->seats;
	p->meals = 0;
	p->finished = FALSE;
	p->num_meals = p->table->num_meals;
	p->last_meal = 0;
}

void	init_philosophers(t_philo *philos, t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->seats)
	{
		philos[i].table = table;
		load_philo_info(i, &philos[i]);
	}
	i = -1;
	while (++i < philos->table->seats)
		if (pthread_create(&philos[i].threads, NULL, &routine, &philos[i]) != 0)
			ft_error_philo(philos, "Failed to create thread philosopher");
	i = -1;
	while (++i < philos->table->seats)
		if (pthread_join(philos[i].threads, NULL) != 0)
			ft_error_philo(philos, "Failed to join thread philosopher");
	i = -1;
	while (++i < philos->table->seats)
		if (pthread_join(philos->table->monitor[i], NULL) != 0)
			ft_error_philo(philos, "failed to join thread monitor");
}
