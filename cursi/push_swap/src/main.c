/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:40:04 by svilla-d          #+#    #+#             */
/*   Updated: 2024/03/30 19:17:50 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	int		*numbers;
	t_node	*a;

	validate_input(argc, argv);
	numbers = parse_input(argc, argv);
	a = init_stack(numbers, argc - 1);
	ft_print_stack("a", a);
	free(numbers);
	ft_free_stack(a);
	return (0);
}
