/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:29:48 by svilla-d          #+#    #+#             */
/*   Updated: 2023/07/21 01:15:38 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define R_MAX 65535

int	ft_sqrt(int nb);

int	ft_sqrt(int nb)
{
	unsigned int	r;
	unsigned int	num;

	num = (unsigned int)nb;
	if (num <= 0)
		return (0);
	if (num == 1)
		return (1);
	r = 2;
	while (r < R_MAX && r * r < num)
		r++;
	if (r * r == num)
		return (r);
	return (0);
}
