/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:29:20 by svilla-d          #+#    #+#             */
/*   Updated: 2024/04/12 11:32:18 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_error_with_message(char *error)
{
	ft_fprintf(STDERR_FILENO, "Error: %s", error);
	exit(EXIT_FAILURE);
}

void	ft_simple_error(void)
{
	ft_fprintf(STDERR_FILENO, "Error");
	exit(EXIT_FAILURE);
}

int	*parse_input(int argc, char **argv, int *size)
{
	int		i;
	char	*input;
	char	**args;
	int		*numbers;

	if (argc > 2)
		input = ft_join_args(argc, argv);
	else
		input = ft_strdup(argv[1]);
	args = ft_split(input, ' ');
	*size = ft_count_words(input, ' ');
	free(input);
	numbers = (int *)malloc((*size) * sizeof(int));
	if (numbers == NULL)
	{
		ft_free_double_ptr(args);
		ft_simple_error();
	}
	i = -1;
	while (++i < *size)
		numbers[i] = ft_atoi(args[i]);
	ft_free_double_ptr(args);
	return (numbers);
}

char	*ft_strcat(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	if (result == NULL)
	{
		if (s1 != NULL)
			free(s1);
		ft_simple_error();
	}
	return (result);
}

char	*ft_join_args(int argc, char **argv)
{
	char	*input;
	char	*temp;
	int		i;

	input = ft_strdup("");
	if (input == NULL)
		ft_simple_error();
	i = 0;
	while (++i < argc)
	{
		temp = ft_strcat(input, argv[i]);
		free(input);
		input = temp;
		temp = ft_strcat(input, " ");
		free(input);
		input = temp;
	}
	return (input);
}
