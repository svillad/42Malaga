/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:12:35 by svilla-d          #+#    #+#             */
/*   Updated: 2024/07/18 20:13:03 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/errno.h>
# include <sys/time.h>
# include <unistd.h>

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

typedef struct s_mutex
{
	pthread_mutex_t	*die;
	pthread_mutex_t	*eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print;
}					t_mutex;

typedef struct s_table
{
	int				seats;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_meals;
	int				dead;
	int				*forks;
	t_mutex			*mutex;
	pthread_t		*monitor;
}					t_table;

typedef struct s_philo
{
	int				id;
	int				num_meals;
	int				fork_left;
	int				fork_right;
	int				meals;
	int				finished;
	long long int	last_meal;
	pthread_t		threads;
	t_table			*table;
}					t_philo;

// actions
long long int		time_to_think(t_philo *p);
void				*dying_routine(void *arg);
void				pausing_philo(t_philo *p, long long int sleep);
void				eating(t_philo *p);

// forks
void				picking_forks(t_philo *p);

// mutex
void				delete_mutex(t_table *table);
t_mutex				*init_mutex(t_table *table);

// philosopher
void				free_philo(t_philo *philos);
void				*routine(void *arg);
int					all_philosophers_finished(t_philo *philos);
void				init_philosophers(t_philo *philos, t_table *table);

// table
void				ft_error_table(t_table *table, const char *message);
t_table				*init_table(char **argv);

// utils
void				ft_error_philo(t_philo *philos, const char *message);
int					ft_atoi(const char *str);
size_t				ft_strlen(const char *str);
long long int		time_milliseconds(void);
void				print_time(t_philo *p, t_msg_ids msg_id);

// validations
void				validate_arguments(int argc, char **argv);

#endif
