/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_div_mod.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 00:05:39 by svilla-d          #+#    #+#             */
/*   Updated: 2023/07/09 00:19:38 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	ft_div_mod(int a, int b, int *div, int *mod);

void	ft_div_mod(int a, int b, int *div, int *mod)
{
	if (b == 0)
	{
		*div = 0;
		*mod = 0;
		return ;
	}
	*div = a / b;
	*mod = a % b;
}

// int	main (void)
// {
// 	int div;
// 	int mod;

// 	div = 0;
// 	mod = 0;
// 	printf("%d %d\n", div, mod);
// 	ft_div_mod(7, 3, &div, &mod);
// 	printf("%d %d\n", div, mod);
// 	return (0);
// }
