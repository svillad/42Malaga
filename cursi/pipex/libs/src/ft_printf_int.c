/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:24:56 by svilla-d          #+#    #+#             */
/*   Updated: 2024/02/24 19:44:47 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_count_digits(unsigned int num)
{
	int	count;

	if (num == 0)
		return (1);
	count = 0;
	while (num != 0)
	{
		num /= 10;
		count++;
	}
	return (count);
}

int	ft_print_signed(int num, int fd)
{
	int		printed_chars;
	char	*result;

	printed_chars = 0;
	if (num == 0)
		printed_chars += write(1, "0", 1);
	else
	{
		result = ft_itoa(num);
		printed_chars += ft_putstr_fd(result, fd);
		free(result);
	}
	return (printed_chars);
}

char	*ft_uint_char(unsigned int num)
{
	int				len;
	char			*result;

	len = ft_count_digits(num);
	result = (char *)malloc(len + 1);
	if (!result)
		return (NULL);
	result[len] = '\0';
	while (len--)
	{
		result[len] = num % 10 + '0';
		num /= 10;
	}
	return (result);
}

int	ft_print_unsigned(unsigned int num, int fd)
{
	int		printed_chars;
	char	*result;

	printed_chars = 0;
	if (num == 0)
		printed_chars += write(1, "0", 1);
	else
	{
		result = ft_uint_char(num);
		printed_chars += ft_putstr_fd(result, fd);
		free(result);
	}
	return (printed_chars);
}
