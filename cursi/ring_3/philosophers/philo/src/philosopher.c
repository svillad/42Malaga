/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:42:57 by svilla-d          #+#    #+#             */
/*   Updated: 2024/07/08 23:34:10 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long int	time_to_think(t_philo *philo, t_table *table)
{
	long long int	time_to_think;

	time_to_think = (table->time_to_die - (time_milliseconds()
				- philo->last_meal) - table->time_to_eat) / table->seats;
	if (time_to_think < 0)
		time_to_think = 0;
	return (time_to_think);
}

void	start_routine(t_args *args)
{
	pthread_t	t_died;

	if (pthread_create(&t_died, NULL, &dying_routine, args) != 0)
		ft_error_philo(args->table, "failed to create thread dying");
	if (pthread_detach(t_died) != 0)
		ft_error_philo(args->table, "failed to detach thread dying");
}

void	*routine(void *arg)
{
	t_args		*args;

	args = (t_args *)arg;
	start_routine(args);
	while (!args->table->dead)
	{
		if (args->philo->finished == FALSE)
			picking_forks(args->philo, args->table);
		if (args->philo->finished == FALSE && args->table->dead == FALSE)
		{
			print_time(args->philo, SLEEPING, args->table);
			pausing_philo(args->table, args->table->time_to_sleep);
		}
		if (args->philo->finished == FALSE && args->table->dead == FALSE)
		{
			print_time(args->philo, THINKING, args->table);
			pausing_philo(args->table, time_to_think(args->philo, args->table));
		}
		else
			break ;
	}
	return (NULL);
}

t_philo	*create_philosopher(int i, t_table *table)
{
	t_philo	*philosopher;
	t_args	*args;

	philosopher = (t_philo *)malloc(sizeof(t_philo));
	philosopher->id = i + 1;
	philosopher->fork_left = i;
	philosopher->fork_right = i;
	if (table->seats != 1)
		philosopher->fork_right = (i + 1) % table->seats;
	philosopher->meals = 0;
	philosopher->finished = FALSE;
	philosopher->num_meals = table->num_meals;
	philosopher->last_meal = 0;
	args = (t_args *)malloc(sizeof(t_args));
	if (!args)
		ft_error_philo(table,
			"failed to allocate memory for routine arguments");
	args->philo = philosopher;
	args->table = table;
	if (pthread_create(&philosopher->threads, NULL, &routine, args) != 0)
		ft_error_philo(table, "failed to create thread philosopher");
	return (philosopher);
}

t_philo	**init_philosophers(t_table *table)
{
	int		i;
	t_philo	**philosophers;

	philosophers = (t_philo **)malloc(table->seats * sizeof(t_philo *));
	if (!philosophers)
		ft_error_philo(table, "failed to allocate memory");
	i = -1;
	while (++i < table->seats)
		philosophers[i] = NULL;
	i = -1;
	while (++i < table->seats)
		philosophers[i] = create_philosopher(i, table);
	i = -1;
	while (++i < table->seats)
		if (pthread_join(philosophers[i]->threads, NULL) != 0)
			ft_error_philo(table, "failed to join thread philosopher");
	return (philosophers);
}
