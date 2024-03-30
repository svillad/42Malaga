/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:02:45 by svilla-d          #+#    #+#             */
/*   Updated: 2024/03/31 18:41:19 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "ft_printf.h"
# include <stdlib.h>
# include <unistd.h>

# define TRUE 1
# define FALSE 0
# define NOT_ASSIGNED -1

typedef struct s_node
{
	int				value;
	int				index;
	int				position;
	struct s_node	*next;
	struct s_node	*prev;
}					t_node;

void				validate_input(int argc, char **argv);
void				ft_simple_error(void);
int					*parse_input(int argc, char **argv);
t_node				*init_stack(int *numbers, int size);
void				ft_free_stack(t_node *head);
void				ft_print_stack(char *name, t_node *head);

void				push_swap(t_node **a, t_node **b);

void				swap_a(t_node **a);
void				swap_b(t_node **a);
void				swap_ab(t_node **a, t_node **b);

void				push_a(t_node **a, t_node **b);
void				push_b(t_node **a, t_node **b);

void				rotate_a(t_node **a);
void				rotate_b(t_node **b);
void				rotate_ab(t_node **a, t_node **b);

void				reverse_rotate_a(t_node **a);
void				reverse_rotate_b(t_node **b);
void				reverse_rotate_ab(t_node **a, int b);

#endif
