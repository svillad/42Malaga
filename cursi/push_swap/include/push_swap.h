/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:02:45 by svilla-d          #+#    #+#             */
/*   Updated: 2024/04/01 14:23:46 by svilla-d         ###   ########.fr       */
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
}					t_node;

void				validate_input(int argc, char **argv);

void				ft_simple_error(void);
int					*parse_input(int argc, char **argv);

void				ft_free_stack(t_node *head);
t_node				*find_min_node(t_node *head);
void				set_stack_indexes(t_node *head);

t_node				*create_node(t_node *head, t_node node);
void				print_node(t_node *node);

void				swap_positions(t_node **node1, t_node **node2);
void				calculate_position(t_node *head);
t_node				*get_penultimate_node(t_node *head);
t_node				*get_last_node(t_node *head);

t_node				*init_stack(int *numbers, int size);
int					get_stack_len(t_node *head);
void				print_stack(char *name, t_node *head);
void				print_stacks(t_node *a, t_node *b);
int					is_stack_ordered(t_node *a, t_node *b);

void				sa(t_node **head);
void				sb(t_node **head);
void				ss(t_node **a, t_node **b);

void				ra(t_node **head);
void				rb(t_node **head);
void				rr(t_node **a, t_node **b);

void				rra(t_node **head);
void				rrb(t_node **head);
void				rrr(t_node **a, t_node **b);

void				pa(t_node **dst, t_node **src);
void				pb(t_node **dst, t_node **src);
#endif
