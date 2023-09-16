/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_comb2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 01:01:39 by svilla-d          #+#    #+#             */
/*   Updated: 2023/07/07 01:02:12 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>

void	ft_print_comb2(void);
void	ft_write_integer(int n, int format);

void	ft_write_integer(int n, int format)
{
	char	buffer[20];
	int		signo;
	int		i;

	signo = 1;
	i = 0;
	if (n < 0)
	{
		signo = -1;
		write(1, "-", 1);
	}
	while (n != 0)
	{
		buffer[i++] = '0' + (n % 10) * signo;
		n = n / 10;
	}
	while (i < format)
	{
		buffer[i++] = '0';
	}
	while (i > 0)
	{
		write(1, &buffer[--i], 1);
	}
}

void	ft_print_comb2(void)
{
	int		n1;
	int		n2;
	bool	print_coma;

	n1 = 0;
	print_coma = false;
	while (n1 <= 99)
	{
		n2 = n1 + 1;
		while (n2 <= 99)
		{
			if (print_coma)
			{
				write(1, ", ", 2);
			}
			print_coma = true;
			ft_write_integer(n1, 2);
			write(1, " ", 1);
			ft_write_integer(n2, 2);
			n2++;
		}
		n1++;
	}
}
