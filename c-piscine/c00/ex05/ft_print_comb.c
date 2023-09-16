/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_comb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 00:55:52 by svilla-d          #+#    #+#             */
/*   Updated: 2023/07/07 00:56:58 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>

void	ft_print_comb(void);
void	ft_write_integer(int n, int format);
bool	ft_is_new_combination(int n);

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

bool	ft_is_new_combination(int n)
{
	int	count;
	int	d1;
	int	d2;

	count = 0;
	while (count < 2)
	{
		d1 = n % 10;
		n = n / 10;
		d2 = n % 10;
		if (d1 < d2 || d1 == d2)
		{
			return (false);
		}
		count++;
	}
	return (true);
}

void	ft_print_comb(void)
{
	int		x;
	bool	firs_number;

	x = 0;
	firs_number = true;
	while (x <= 999)
	{
		if (ft_is_new_combination(x))
		{
			if (!firs_number)
			{
				write(1, ", ", 2);
			}
			firs_number = false;
			ft_write_integer(x, 3);
		}
		x++;
	}
}
