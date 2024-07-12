/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 14:44:54 by svilla-d          #+#    #+#             */
/*   Updated: 2024/07/12 19:01:20 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	free_philo(t_philo *philos)
{
	if (philos)
		philos = philos - philos->id + 1;
	if (philos)
	{
		if (philos->table)
		{
			if (philos->table->sem)
			{
				close_semaphores(philos);
				free(philos->table->sem);
			}
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

void	ft_itoa(int num, char *str)
{
	int	i;
	int	length;
	int	digit;

	if (num == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return ;
	}
	length = 0;
	i = num;
	while (i != 0)
	{
		i /= 10;
		length++;
	}
	i = 0;
	while (num != 0)
	{
		digit = num % 10;
		str[length - i++ - 1] = digit + '0';
		num /= 10;
	}
	str[length] = '\0';
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
	if (sem_wait(table->sem->print) == -1)
		ft_error_philo(p, "failed to lock print");
	if (!table->dead && msg_id >= 0 && msg_id < 6)
	{
		printf("%llu %d %s (%d)\n", time_milliseconds(), p->id,
			messages[msg_id], p->num_meals);
	}
	if (sem_post(table->sem->print) == -1)
		ft_error_philo(p, "failed to unlock print");
}
