/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simolina <simolina@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 12:35:11 by simolina          #+#    #+#             */
/*   Updated: 2023/07/16 14:38:38 by simolina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#define SIZE 4
#define OK 0
#define ERROR 1

int		ft_check_rule_serie_4(char A[][6]);
int		ft_check_rule_1(char A[][6]);
int		ft_check_rule_32(char A[][6]);
int		sub_check3y5(char mat[][6]);
int		ft_gapfinder(char A[][6]);
void	ft_gapfiller(char A[][6]);
int		valid_result(char A[][6]);
void	ft_random_filler(char A[][6], int ex);
void	ft_copy(char A[][6], char B[][6]);

int	ft_solve_game(char A[][6])
{
	int		error;
	int		f;
	char	copy[6][6];

	error = 0;
	error += ft_check_rule_serie_4(A);
	error += ft_check_rule_1(A);
	error += ft_check_rule_32(A);
	error += sub_check3y5(A);
	if (error != 0)
		return (error);
	while (ft_gapfinder(A) == 1)
		ft_gapfiller(A);
	error = valid_result(A);
	f = 0;
	while (error != 0 && f < 16)
	{
		ft_copy(A, copy);
		ft_random_filler(copy, f);
		error = valid_result(copy);
		f++;
	}
	ft_copy(copy, A);
	return (error);
}
