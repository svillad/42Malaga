/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 11:39:08 by svilla-d          #+#    #+#             */
/*   Updated: 2023/11/11 12:41:45 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_count_hex(unsigned int num)
{
	int	count;

	if (num == 0)
		return (1);
	count = 0;
	while (num != 0)
	{
		num /= 16;
		count++;
	}
	return (count);
}

char	*ft_hex_char(unsigned int num, const char format)
{
	int			len;
	char		*result;
	const char	hex_upper[16] = "0123456789ABCDEF";
	const char	hex_lower[16] = "0123456789abcdef";

	len = ft_count_hex(num);
	result = (char *)malloc(len + 1);
	if (!result)
		return (NULL);
	result[len] = '\0';
	while (len--)
	{
		if (format == 'X')
			result[len] = hex_upper[num % 16];
		else
			result[len] = hex_lower[num % 16];
		num /= 16;
	}
	return (result);
}

int	ft_print_hex(unsigned int num, const char format)
{
	int		printed_chars;
	char	*result;

	printed_chars = 0;
	if (num == 0)
		printed_chars += write(1, "0", 1);
	else
	{
		result = ft_hex_char(num, format);
		printed_chars += ft_putstr_fd(result, 1);
		free(result);
	}
	return (printed_chars);
}
