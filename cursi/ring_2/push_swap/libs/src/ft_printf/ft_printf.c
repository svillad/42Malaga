/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 11:42:34 by svilla-d          #+#    #+#             */
/*   Updated: 2024/03/29 11:26:49 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

static int	ft_selection(va_list *args, const char f, int fd)
{
	if (f == 'c')
		return (ft_putchar_fd(va_arg(*args, int), fd));
	else if (f == 's')
		return (ft_putstr_fd(va_arg(*args, char *), fd));
	else if (f == 'p')
		return (ft_print_addr(va_arg(*args, unsigned long long), fd));
	else if (f == 'd' || f == 'i')
		return (ft_print_signed(va_arg(*args, int), fd));
	else if (f == 'u')
		return (ft_print_unsigned(va_arg(*args, unsigned int), fd));
	else if (f == 'x' || f == 'X')
		return (ft_print_hex(va_arg(*args, unsigned int), f, fd));
	else if (f == '%')
		return (ft_putchar_fd('%', fd));
	return (0);
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
			ft_putchar_fd(str[i], STDOUT_FILENO);
			printed_chars++;
		}
		else
			printed_chars += ft_selection(&args, str[++i], STDOUT_FILENO);
		i++;
	}
	va_end(args);
	return (printed_chars);
}

int	ft_fprintf(int fd, const char *str, ...)
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
			ft_putchar_fd(str[i], fd);
			printed_chars++;
		}
		else
			printed_chars += ft_selection(&args, str[++i], fd);
		i++;
	}
	va_end(args);
	return (printed_chars);
}
