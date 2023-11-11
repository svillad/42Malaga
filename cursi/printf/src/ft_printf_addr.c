/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_addr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 12:38:21 by svilla-d          #+#    #+#             */
/*   Updated: 2023/11/11 12:41:21 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_count_addr(unsigned long long num)
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

char	*ft_hex_addr(unsigned long long num)
{
	int			len;
	char		*result;
	const char	hex_lower[16] = "0123456789abcdef";

	len = ft_count_addr(num);
	result = (char *)malloc(len + 1);
	if (!result)
		return (NULL);
	result[len] = '\0';
	while (len--)
	{
		result[len] = hex_lower[num % 16];
		num /= 16;
	}
	return (result);
}

int	ft_print_addr(unsigned long long ptr)
{
	int		printed_chars;
	char	*result;

	printed_chars = write(1, "0x", 2);
	if (ptr == 0)
		printed_chars += write(1, "0", 1);
	else
	{
		result = ft_hex_addr(ptr);
		printed_chars += ft_putstr_fd(result, 1);
		free(result);
	}
	return (printed_chars);
}
