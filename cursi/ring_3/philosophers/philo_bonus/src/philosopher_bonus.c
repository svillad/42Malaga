/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:42:57 by svilla-d          #+#    #+#             */
/*   Updated: 2024/07/10 14:45:31 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	end_processes(t_philo *philos)
{
	int	i;
	int	j;
	int	res;

	i = -1;
	while (++i < philos->table->seats)
	{
		waitpid(-1, &res, 0);
		if (res != 0)
		{
			j = -1;
			while (++j < philos->table->seats)
				kill(philos[j].pid, 15);
			break ;
		}
	}
}

static void	start_routine(t_philo *p)
{
	pthread_t	t_died;

	print_time(p, THINKING);
	if (pthread_create(&t_died, NULL, &dying_routine, p) != 0)
		ft_error_philo(p, "failed to create thread dying");
	if (pthread_detach(t_died) != 0)
		ft_error_philo(p, "failed to detach thread dying");
}

void	routine(t_philo	*p)
{
	start_routine(p);
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
	if (p->table->dead)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

static void	load_philo_info(int i, t_philo *p)
{
	char	str[2];

	p->id = i + 1;
	p->meals = 0;
	p->finished = FALSE;
	p->num_meals = p->table->num_meals;
	p->last_meal = 0;
	str[0] = (char)i;
	str[1] = '\0';
	sem_unlink(str);
	p->sem_eat = sem_open(str, O_CREAT, 0644, 1);
	if (p->sem_eat == SEM_FAILED)
		ft_error_philo(p, "failed to create semaphore: sem_eat");
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
}
