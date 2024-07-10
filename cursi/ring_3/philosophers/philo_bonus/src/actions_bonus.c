/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:02:22 by svilla-d          #+#    #+#             */
/*   Updated: 2024/07/10 14:11:15 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long int	time_milliseconds(void)
{
	struct timeval	tv;
	long long int	milliseconds;

	gettimeofday(&tv, NULL);
	milliseconds = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
	return (milliseconds);
}

long long int	time_to_think(t_philo *p)
{
	long long int	time_to_think;
	t_table			*table;

	table = p->table;
	time_to_think = (table->time_to_die - (time_milliseconds() - p->last_meal)
			- table->time_to_eat) / table->seats;
	if (time_to_think < 0)
		time_to_think = 0;
	return (time_to_think);
}

void	*dying_routine(void *arg)
{
	t_philo	*p;
	int		current_meal;

	p = (t_philo *)arg;
	current_meal = p->meals;
	usleep(p->table->time_to_die * 1000);
	if (p->meals == current_meal)
	{
		if (sem_wait(p->sem_eat) == -1)
			ft_error_philo(p, "failed to lock eat");
		if (sem_wait(p->table->sem->die) == -1)
			ft_error_philo(p, "failed to lock die");
		print_time(p, DYING);
		p->table->dead = TRUE;
		if (sem_post(p->table->sem->die) == -1)
			ft_error_philo(p, "failed to unlock die");
		if (sem_post(p->sem_eat) == -1)
			ft_error_philo(p, "failed to unlock eat");
		if (sem_wait(p->table->sem->print) == -1)
			ft_error_philo(p, "failed to lock eat");
		exit(EXIT_FAILURE);
	}
	return (NULL);
}

void	pausing_philo(t_philo *p, long long int sleep)
{
	long long int	wake_up;

	wake_up = time_milliseconds() + sleep;
	while (time_milliseconds() < wake_up)
	{
		if (p->table->dead == TRUE)
			break ;
		usleep(10);
	}
}

void	eating(t_philo *p)
{
	pthread_t	t_died;

	if (sem_wait(p->sem_eat) == -1)
		ft_error_philo(p, "failed to lock eat");
	p->meals++;
	print_time(p, EATING);
	p->last_meal = time_milliseconds();
	if (sem_post(p->sem_eat) == -1)
		ft_error_philo(p, "failed to unlock eat");
	if (p->num_meals != 0)
	{
		if (pthread_create(&t_died, NULL, &dying_routine, p) != 0)
			ft_error_philo(p, "failed to create thread dying");
		if (pthread_detach(t_died) != 0)
			ft_error_philo(p, "failed to detach thread dying");
	}
	if (p->num_meals != -1)
		p->num_meals--;
	if (p->num_meals == 0)
		p->finished = 1;
	pausing_philo(p, p->table->time_to_eat);
}
