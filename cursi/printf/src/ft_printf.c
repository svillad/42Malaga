/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 11:42:34 by svilla-d          #+#    #+#             */
/*   Updated: 2023/11/04 14:51:44 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_selection(va_list args, const char f)
{
	ft_putchar_fd(f,1);
	if (f == 'c')
		ft_putchar_fd(va_arg(args, int), 1);
	else if (f == 's')
		ft_putstr_fd(va_arg(args, char *), 1);
	else if (f == 'p'){}
		// Código para el f 'p'
	else if (f == 'd' || f == 'i')
		ft_putnbr_fd(va_arg(args, int), 1);
	else if (f == 'u')
		ft_putnbr_fd(va_arg(args, unsigned int), 1);
	else if (f == 'x'){}
		// Código para el f 'x'
	else if (f == 'X'){}
		// Código para el f 'X'
	else if (f == '%')
		ft_putchar_fd(va_arg(args, int), 1);
	else
	{
		// Código si no coincide con ninguno de los fs
	}
	return (1);
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
			ft_putchar_fd(str[i], 1);
		else
			printed_chars += ft_selection(args, str[++i]);
		i++;
	}
	va_end(args);
	return (printed_chars);
}
