/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 19:02:11 by svilla-d          #+#    #+#             */
/*   Updated: 2023/07/17 19:56:40 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>

#define OK				0
#define ERROR			1
#define ERROR_01		2
#define ERROR_POS_NEG	3
#define ERROR_CHAR_DUP	4

int		ft_strlen(char *str);
int		ft_check_base(char *base);
void	ft_putnbr_base(int nbr, char *base);
int		ft_process_negative(int *nbr, char *number, char *base);
int		ft_process_number(int nbr, int pos, char *number, char *base);

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (*str++)
		len++;
	return (len);
}

int	ft_check_base(char *base)
{
	int	len;
	int	i;
	int	j;

	len = ft_strlen(base);
	if (len == 0 || len == 1)
		return (ERROR_01);
	i = 0;
	while (i < len)
	{
		if (base[i] < ' ' || base[i] > '~')
			return (ERROR_POS_NEG);
		if (base[i] == '+' || base[i] == '-')
			return (ERROR_POS_NEG);
		j = i + 1;
		while (j < len)
		{
			if (base[i] == base[j])
				return (ERROR_CHAR_DUP);
			j++;
		}
		i++;
	}
	return (OK);
}

int	ft_process_negative(int *nbr, char *number, char *base)
{
	int	i;
	int	b;

	b = ft_strlen(base);
	i = 0;
	if (*nbr < 0)
	{
		write(1, "-", 1);
		if (*nbr == INT_MIN)
		{
			number[i] = base[(*nbr % b)];
			*nbr = *nbr / b;
			i++;
		}
		*nbr = -*nbr;
	}
	return (i);
}

int	ft_process_number(int nbr, int pos, char *number, char *base)
{
	int	b;

	b = ft_strlen(base);
	while (nbr > 0)
	{
		number[pos] = base[(nbr % b)];
		nbr = nbr / b;
		pos++;
	}
	return (pos);
}

void	ft_putnbr_base(int nbr, char *base)
{
	int		i;
	char	number[100];
	int		err;

	err = ft_check_base(base);
	if (err)
		return ;
	if (nbr == 0)
	{
		write(1, "0", 1);
		return ;
	}
	i = ft_process_negative(&nbr, number, base);
	i = ft_process_number(nbr, i, number, base);
	while (i > 0)
		write(1, &number[--i], 1);
	return ;
}
