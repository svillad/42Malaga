/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 14:44:54 by svilla-d          #+#    #+#             */
/*   Updated: 2024/07/18 20:19:28 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error_philo(t_philo *philos, const char *message)
{
	printf("❌ Error ❌\n");
	if (message != NULL && ft_strlen(message) != 0)
		printf("► %s\n", message);
	if (philos)
		free_philo(philos);
	exit(EXIT_FAILURE);
}

void	free_philo(t_philo *philos)
{
	if (philos)
		philos = philos - philos->id + 1;
	if (philos)
	{
		if (philos->table)
		{
			if (philos->table->forks)
				free(philos->table->forks);
			if (philos->table->mutex)
				delete_mutex(philos->table);
			if (philos->table->monitor)
				free(philos->table->monitor);
			free(philos->table);
		}
		free(philos);
	}
}

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\r' || str[i] == '\f'
		|| str[i] == '\t' || str[i] == '\v')
	{
		i++;
	}
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (sign * result);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	print_time(t_philo *p, t_msg_ids msg_id)
{
	const char	*messages[] = {TAKE, EAT, SLEEP, THINK, DIED, DROP};
	t_table		*table;

	table = p->table;
	if (pthread_mutex_lock(table->mutex->print) != 0)
		ft_error_philo(p, "failed to lock print");
	if (!table->dead && msg_id >= 0 && msg_id < 6)
	{
		printf("%llu %d %s (%d)\n", time_milliseconds(), p->id,
			messages[msg_id], p->num_meals);
	}
	if (pthread_mutex_unlock(table->mutex->print) != 0)
		ft_error_philo(p, "failed to unlock print");
}
