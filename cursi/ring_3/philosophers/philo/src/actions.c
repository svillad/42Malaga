/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:02:22 by svilla-d          #+#    #+#             */
/*   Updated: 2024/07/09 11:50:57 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_philosophers_finished(t_table *table)
{
	int	i;
	int	finished;

	i = 0;
	finished = TRUE;
	while (i < table->seats)
	{
		if (table->philosophers[i]->finished != TRUE)
			finished = FALSE;
		i++;
	}
	return (finished);
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
		if (pthread_mutex_lock(&table->mutex->eat[philo->id - 1]) != 0)
			ft_error_philo(table, "failed to lock eat");
		if (pthread_mutex_lock(table->mutex->die) != 0)
			ft_error_philo(table, "failed to lock die");
		print_time(philo, DYING, table);
		table->dead = TRUE;
		if (pthread_mutex_unlock(table->mutex->die) != 0)
			ft_error_philo(table, "failed to unlock die");
		if (pthread_mutex_unlock(&table->mutex->eat[philo->id - 1]) != 0)
			ft_error_philo(table, "failed to unlock eat");
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
	t_args		*args;

	if (pthread_mutex_lock(&table->mutex->eat[philo->id - 1]) != 0)
		ft_error_philo(table, "failed to lock eat");
	philo->meals++;
	print_time(philo, EATING, table);
	philo->last_meal = time_milliseconds();
	if (pthread_mutex_unlock(&table->mutex->eat[philo->id - 1]) != 0)
		ft_error_philo(table, "failed to unlock eat");
	if (philo->num_meals != 0)
	{
		args = (t_args *)malloc(sizeof(t_args));
		if (!args)
			ft_error_philo(table, "failed to allocate memory for arguments");
		args->philo = philo;
		args->table = table;
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
