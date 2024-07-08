/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:02:22 by svilla-d          #+#    #+#             */
/*   Updated: 2024/07/08 22:35:50 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_finished(t_table *table)
{
	int	i;
	int	all_finish;

	i = 0;
	all_finish = 1;
	while (i < table->seats)
	{
		if (table->philosophers[i]->finished != TRUE)
			all_finish = 0;
		i++;
	}
	return (all_finish);
}

void	*dying_routine(void *arg)
{
	t_args	*args;
	t_table	*table;
	t_philo	*philo;
	int		current_meal;

	args = (t_args *)arg;
	table = args->table;
	philo = args->philo;
	current_meal = philo->meals;
	usleep(table->time_to_die * 1000);
	if (philo->meals == current_meal)
	{
		if (pthread_mutex_lock(&table->mutex->die[philo->id - 1]) != 0)
			ft_error_philo(table, "failed to lock die");
		print_time(philo, DYING, table);
		table->dead = TRUE;
		if (pthread_mutex_unlock(&table->mutex->die[philo->id - 1]) != 0)
			ft_error_philo(table, "failed to unlock die");
	}
	return (NULL);
}

void	pausing_philo(t_table *table, long long int sleep)
{
	long long int	wake_up;

	wake_up = time_milliseconds() + sleep;
	while (time_milliseconds() < wake_up)
	{
		if (table->dead == TRUE)
			break ;
		usleep(10);
	}
}

void	eating(t_philo *philo, t_table *table)
{
	pthread_t	t_died;
	t_args		args;

	if (pthread_mutex_lock(&table->mutex->die[philo->id - 1]) != 0)
		ft_error_philo(table, "failed to lock die");
	philo->meals++;
	print_time(philo, EATING, table);
	philo->last_meal = time_milliseconds();
	if (pthread_mutex_unlock(&table->mutex->die[philo->id - 1]) != 0)
		ft_error_philo(table, "failed to unlock die");
	if (philo->num_meals != 0)
	{
		args.philo = philo;
		args.table = table;
		if (pthread_create(&t_died, NULL, &dying_routine, &args) != 0)
			ft_error_philo(table, "failed to create thread dying");
		if (pthread_detach(t_died) != 0)
			ft_error_philo(table, "failed to detach thread dying");
	}
	if (philo->num_meals != -1)
		philo->num_meals--;
	if (philo->num_meals == 0)
		philo->finished = 1;
	pausing_philo(table, table->time_to_eat);
}
