/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 16:55:17 by svilla-d          #+#    #+#             */
/*   Updated: 2023/07/12 16:55:22 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putnbr(int nb);

void	ft_putnbr(int nb)
{
	char	buffer[20];
	int		signo;
	int		i;

	signo = 1;
	i = 0;
	if (nb < 0)
	{
		signo = -1;
		write(1, "-", 1);
	}
	while (nb != 0)
	{
		buffer[i++] = '0' + (nb % 10) * signo;
		nb = nb / 10;
	}
	while (i < 1)
	{
		buffer[i++] = '0';
	}
	while (i > 0)
	{
		write(1, &buffer[--i], 1);
	}
}
