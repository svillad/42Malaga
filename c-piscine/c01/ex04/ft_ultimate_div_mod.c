/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultimate_div_mod.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 00:12:12 by svilla-d          #+#    #+#             */
/*   Updated: 2023/07/09 00:20:22 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	ft_ultimate_div_mod(int *a, int *b);

void	ft_ultimate_div_mod(int *a, int *b)
{
	int	temp;

	if (*b == 0)
	{
		*a = 0;
		*b = 0;
		return ;
	}
	temp = *a / *b;
	*b = *a % *b;
	*a = temp;
}

// int	main (void)
// {
// 	int div;
// 	int mod;

// 	div = 7;
// 	mod = 2;
// 	printf("%d %d\n", div, mod);
// 	ft_ultimate_div_mod(&div, &mod);
// 	printf("%d %d\n", div, mod);
// 	return (0);
// }
