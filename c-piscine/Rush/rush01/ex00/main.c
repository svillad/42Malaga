/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simolina <simolina@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 12:36:40 by simolina          #+#    #+#             */
/*   Updated: 2023/07/16 14:18:53 by simolina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 4
#define PARAMS_SIZE 16

int		ft_get_params(char *argv[], char *params);
void	matrix_filler(char mat[][6], char c, char ls[]);
int		ft_solve_game(char A[][6]);
void	result_shower(char mat[][6]);

int	main(int argc, char *argv[])
{
	int		error;
	char	*params;
	char	table[6][6];

	params = malloc((PARAMS_SIZE + 1) * sizeof(char));
	if (argc != 2)
	{
		write(1, "Error\n", 6);
		return (1);
	}
	error = ft_get_params(argv, params);
	if (error)
	{
		write(1, "Error\n", 6);
		return (1);
	}
	matrix_filler(table, '*', params);
	error = ft_solve_game(table);
	if (error)
	{
		write(1, "Error\n", 6);
		return (1);
	}	
	result_shower(table);
	return (0);
}
