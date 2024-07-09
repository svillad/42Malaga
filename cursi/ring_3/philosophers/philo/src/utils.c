/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 14:44:54 by svilla-d          #+#    #+#             */
/*   Updated: 2024/07/09 09:51:24 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error_philo(t_table *table, const char *message)
{
	printf("❌ Error ❌\n");
	if (message != NULL && ft_strlen(message) != 0)
		printf("► %s\n", message);
	if (table)
		free_table(table);
	exit(EXIT_FAILURE);
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

long long int	time_milliseconds(void)
{
	struct timeval	tv;
	long long int	milliseconds;

	gettimeofday(&tv, NULL);
	milliseconds = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
	return (milliseconds);
}

void	print_time(t_philo *philo, t_msg_ids msg_id, t_table *table)
{
	const char	*messages[] = {TAKE, EAT, SLEEP, THINK, DIED, DROP};

	if (pthread_mutex_lock(table->mutex->print) != 0)
		ft_error_philo(table, "failed to lock print");
	if (!table->dead && msg_id >= 0 && msg_id < 6)
	{
		printf("%llu %d %s (%d)\n", time_milliseconds(), philo->id,
			messages[msg_id], philo->num_meals);
	}
	if (pthread_mutex_unlock(table->mutex->print) != 0)
		ft_error_philo(table, "failed to unlock print");
}
