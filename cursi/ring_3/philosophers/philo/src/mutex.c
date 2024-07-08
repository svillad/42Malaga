/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:49:06 by svilla-d          #+#    #+#             */
/*   Updated: 2024/07/08 22:22:58 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_to_zero(t_mutex *mutex)
{
	mutex->die = NULL;
	mutex->forks = NULL;
	mutex->print = NULL;
}

t_mutex	*init_mutex(t_table *table)
{
	int			i;
	t_mutex		*mutex;
	const int	size = table->seats;

	mutex = (t_mutex *)malloc(sizeof(t_mutex));
	if (!mutex)
		ft_error_philo(table, "failed to allocate memory: mutex");
	init_to_zero(mutex);
	mutex->forks = (pthread_mutex_t *)malloc(size * sizeof(pthread_mutex_t));
	if (!mutex->forks)
		ft_error_philo(table, "failed to allocate memory: forks");
	mutex->die = (pthread_mutex_t *)malloc(size * sizeof(pthread_mutex_t));
	if (!mutex->die)
		ft_error_philo(table, "failed to allocate memory: die");
	mutex->print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!mutex->print)
		ft_error_philo(table, "failed to allocate memory: print");
	pthread_mutex_init(mutex->print, NULL);
	i = -1;
	while (++i < size)
	{
		pthread_mutex_init(&mutex->forks[i], NULL);
		pthread_mutex_init(&mutex->die[i], NULL);
	}
	return (mutex);
}
