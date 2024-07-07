/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 23:29:05 by svilla-d          #+#    #+#             */
/*   Updated: 2024/04/20 19:59:54 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	validate_operation(char *line, char *operations)
{
	if (ft_strcmp(line, "sa\n") == OK)
		return ;
	else if (ft_strcmp(line, "sb\n") == OK)
		return ;
	else if (ft_strcmp(line, "ss\n") == OK)
		return ;
	else if (ft_strcmp(line, "ra\n") == OK)
		return ;
	else if (ft_strcmp(line, "rb\n") == OK)
		return ;
	else if (ft_strcmp(line, "rr\n") == OK)
		return ;
	else if (ft_strcmp(line, "rra\n") == OK)
		return ;
	else if (ft_strcmp(line, "rrb\n") == OK)
		return ;
	else if (ft_strcmp(line, "rrr\n") == OK)
		return ;
	else if (ft_strcmp(line, "pa\n") == OK)
		return ;
	else if (ft_strcmp(line, "pb\n") == OK)
		return ;
	free(line);
	free(operations);
	ft_simple_error();
}

char	*ft_read_operations(int *size)
{
	char	*line;
	char	*temp;
	char	*operations;

	*size = 0;
	operations = ft_strdup("");
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (line)
		{
			validate_operation(line, operations);
			(*size)++;
			temp = ft_strdup(operations);
			free(operations);
			operations = ft_strjoin(temp, line);
			free(temp);
		}
		free(line);
	}
	return (operations);
}

void	exec_operation(t_node **a, t_node**b, char *operation)
{
	if (ft_strcmp(operation, "sa") == OK || ft_strcmp(operation, "ss") == OK)
		swap_op(a);
	if (ft_strcmp(operation, "sb") == OK || ft_strcmp(operation, "ss") == OK)
		swap_op(b);
	if (ft_strcmp(operation, "ra") == OK || ft_strcmp(operation, "rr") == OK)
		rotate_op(a);
	if (ft_strcmp(operation, "rb") == OK || ft_strcmp(operation, "rr") == OK)
		rotate_op(b);
	if (ft_strcmp(operation, "rra") == OK || ft_strcmp(operation, "rrr") == OK)
		reverse_rotate_op(a);
	if (ft_strcmp(operation, "rrb") == OK || ft_strcmp(operation, "rrr") == OK)
		reverse_rotate_op(b);
	if (ft_strcmp(operation, "pa") == OK)
		push_op(a, b);
	if (ft_strcmp(operation, "pb") == OK)
		push_op(b, a);
}

void	process(t_node **a, t_node **b, char *operations)
{
	int		i;
	int		size;
	char	**ope;

	ope = ft_split(operations, '\n');
	size = ft_count_words(operations, '\n');
	i = -1;
	while (++i < size)
		exec_operation(a, b, ope[i]);
	ft_free_double_ptr(ope);
}

int	checker(int argc, char **argv)
{
	t_node	*a;
	t_node	*b;
	int		*numbers;
	int		size;
	char	*operations;

	if (argc == 1)
		return (OK);
	validate_input(argc, argv);
	numbers = parse_input(argc, argv, &size);
	a = init_stack(numbers, size);
	b = NULL;
	operations = ft_read_operations(&size);
	process(&a, &b, operations);
	if (is_stack_ordered(a, b))
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
	free(numbers);
	free(operations);
	ft_free_stack(a);
	return (OK);
}
