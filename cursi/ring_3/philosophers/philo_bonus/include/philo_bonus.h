/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:12:35 by svilla-d          #+#    #+#             */
/*   Updated: 2024/07/19 09:53:46 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/errno.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>

# define NUM_PHILO "number of philosopher"
# define TIME_DIE "time to die"
# define TIME_EAT "time to eat"
# define TIME_SLEEP "time to sleep"
# define NUM_EAT "number of times each philosopher must eat"
# define TAKE "has \e[33mtaken\e[0m a fork"
# define DROP "has \e[36mdropped\e[0m a fork"
# define EAT "is \e[32meating\e[0m"
# define SLEEP "is \e[34msleeping\e[0m"
# define THINK "is \e[35mthinking\e[0m"
# define DIED "\e[31mdied\e[0m"
# define TRUE 1
# define FALSE 0
# define UNSET -1
# define LOCK 1
# define UNLOCK 0

typedef enum msg_ids
{
	TAKING_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DYING,
	DROPPING,
	NOPRINT
}					t_msg_ids;

typedef struct s_semaphore
{
	sem_t	*die;
	sem_t	*forks;
	sem_t	*print;
}					t_semaphore;

typedef struct s_table
{
	int				seats;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_meals;
	int				dead;
	t_semaphore		*sem;
	pthread_t		*monitor;
}					t_table;

typedef struct s_philo
{
	int				id;
	int				num_meals;
	int				meals;
	int				finished;
	long long int	last_meal;
	sem_t			*sem_eat;
	pid_t			pid;
	t_table			*table;
}					t_philo;

// actions
long long int		time_to_think(t_philo *p);
void				*dying_routine(void *arg);
void				pausing_philo(t_philo *p, long long int sleep);
void				eating(t_philo *p);

// forks
void				picking_forks(t_philo *p);

// semaphore
void				close_semaphores(t_philo *philos);
t_semaphore			*init_semaphore(t_table *table);

// philosopher
void				end_processes(t_philo *philos);
void				free_philo(t_philo *philos);
void				routine(t_philo	*p);
void				init_philosophers(t_philo *philos, t_table *table);

// table
void				ft_error_table(t_table *table, const char *message);
void				ft_error_philo(t_philo *philos, const char *message);
t_table				*init_table(char **argv);

// utils
int					ft_atoi(const char *str);
void				ft_itoa(int num, char *str);
size_t				ft_strlen(const char *str);
long long int		time_milliseconds(void);
void				print_time(t_philo *p, t_msg_ids msg_id);

// validations
void				validate_arguments(int argc, char **argv);

#endif
