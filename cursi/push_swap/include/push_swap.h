/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:02:45 by svilla-d          #+#    #+#             */
/*   Updated: 2024/04/01 01:05:55 by svilla-d         ###   ########.fr       */
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
	char			*name;
	int				value;
	int				index;
	int				position;
	struct s_node	*next;
}					t_node;

void				validate_input(int argc, char **argv);
void				ft_simple_error(void);
int					*parse_input(int argc, char **argv);
void				ft_free_stack(t_node *head);

t_node				*find_min_node(t_node *head);

//stack
int					get_stack_len(t_node *head);
t_node				*init_stack(int *numbers, int size);
void				print_stack(t_node *head);

// node
t_node				*create_node(t_node *head, t_node node);
void				print_node(t_node *node);

void				set_stack_indexes(t_node *head);

void				swap_positions(t_node **node1, t_node **node2);
void				calculate_position(t_node *head);
t_node				*get_penultimate_node(t_node *head);
t_node				*get_last_node(t_node *head);

void				swap(t_node **head);
void				double_swap(t_node **a, t_node **b);
void				rotate(t_node **head);
void				double_rotate(t_node **a, t_node **b);
void				reverse_rotate(t_node **head);
void				double_reverse_rotate(t_node **a, t_node **b);
void				push(t_node **dst, t_node **src);

void				push_swap(t_node **a, t_node **b);

void				push_a(t_node **a, t_node **b);
void				push_b(t_node **a, t_node **b);

void				rotate_a(t_node **a);
void				rotate_b(t_node **b);
void				rotate_ab(t_node **a, t_node **b);

void				reverse_rotate_a(t_node **a);
void				reverse_rotate_b(t_node **b);
void				reverse_rotate_ab(t_node **a, int b);

#endif
