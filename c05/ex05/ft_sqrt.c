/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:29:48 by svilla-d          #+#    #+#             */
/*   Updated: 2023/07/18 14:35:42 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_sqrt(int nb);

int	ft_sqrt(int nb)
{
	int	r;

	if (nb <= 0)
		return (0);
	if (nb == 1)
		return (1);
	r = nb / 2;
	while (r > 0 && r * r != nb)
		r--;
	return (r);
}

// int	ft_sqrt_recursive(int nb, int r)
// {
// 	if (r == 0)
// 		return (0);
// 	if (r * r == nb)
// 		return r;
//     return (ft_sqrt_recursive(nb, r - 1));
// }