/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:24:56 by svilla-d          #+#    #+#             */
/*   Updated: 2023/11/10 22:49:55 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_uint_char(unsigned int num)
{
	int				len;
	unsigned int	temp;
	char			*result;

	len = 0;
	temp = num;
	while (temp)
	{
		temp /= 10;
		len++;
	}
	result = (char *)malloc(len + 1);
	if (!result)
		return (0);
	result[len] = '\0';
	while (len--)
	{
		result[len] = num % 10 + '0';
		num /= 10;
	}
	return (result);
}

int	ft_print_unsigned(unsigned int num)
{
	int		printed_chars;
	char	*result;

	printed_chars = 0;
	if (num == 0)
		printed_chars += write(1, "0", 1);
	else
	{
		result = ft_uint_char(num);
		printed_chars += ft_putstr_fd(result, 1);
		free(result);
	}
	return (printed_chars);
}
