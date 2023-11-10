/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 11:42:34 by svilla-d          #+#    #+#             */
/*   Updated: 2023/11/10 22:51:19 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_selection(va_list *args, const char f)
{
	int	printed_chars;

	printed_chars = 0;
	if (f == 'c')
		return (ft_putchar_fd(va_arg(*args, int), 1));
	else if (f == 's')
		return (ft_putstr_fd(va_arg(*args, char *), 1));
	else if (f == 'p')
	{
	}
	else if (f == 'd' || f == 'i')
		return (ft_putstr_fd(ft_itoa(va_arg(*args, int)), 1));
	else if (f == 'u')
		return (ft_print_unsigned(va_arg(*args, unsigned int)));
	else if (f == 'x')
	{
	}
	else if (f == 'X')
	{
	}
	else if (f == '%')
		ft_putchar_fd(va_arg(*args, int), 1);
	else
	{
	}
	return (printed_chars);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		printed_chars;
	va_list	args;

	i = 0;
	printed_chars = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] != '%')
		{
			ft_putchar_fd(str[i], 1);
			printed_chars++;
		}
		else
			printed_chars += ft_selection(&args, str[++i]);
		i++;
	}
	va_end(args);
	return (printed_chars);
}
