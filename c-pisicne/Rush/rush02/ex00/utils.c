/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxgarci <maxgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 17:20:27 by maxgarci          #+#    #+#             */
/*   Updated: 2023/07/23 23:33:21 by maxgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

int	ft_atoi(char *str)
{
	int	i;
	int	result;
	int	sign;
	int	check;

	i = 0;
	result = 0;
	sign = 1;
	check = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = (sign * -1);
	while (str[i] != '\0' && str[i] >= 48 && str[i] <= 57)
	{
		check = 1;
		result = (result * 10) + (str[i++] - '0');
	}
	if (!check || (str[i] == '.'))
		return (-1);
	if (sign == -1)
		return ((unsigned)result * sign);
	return (result * sign);
}

void	ft_strcpy(char *src, char *dest)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

int	ft_is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\v' || c == '\n')
		return (1);
	return (0);
}
