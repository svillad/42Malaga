/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 13:16:08 by svilla-d          #+#    #+#             */
/*   Updated: 2023/07/13 09:56:09 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

void	ft_print_char(char c);
void	ft_print_addr(void *addr);
void	ft_print_char_hex(char c);
void	ft_print_format(unsigned int i, void *addr, unsigned int size);
void	*ft_print_memory(void *addr, unsigned int size);

void	ft_print_char(char c)
{
	if (c < ' ' || c > '~')
		write(1, ".", 1);
	else
		write(1, &c, 1);
}

void	ft_print_addr(void *addr)
{
	const char		table_hex[] = "0123456789abcdef";
	unsigned long	address;
	char			buffer[20];
	int				i;
	int				digit;

	address = (unsigned long)addr;
	i = 16;
	buffer[i] = '\0';
	while (i > 0)
	{
		digit = address % 16;
		address /= 16;
		buffer[--i] = table_hex[digit];
	}
	write(1, buffer, 16);
}

void	ft_print_char_hex(char c)
{
	const char	table_hex[] = "0123456789abcdef";
	char		hex[2];

	hex[0] = table_hex[(c / 16) & 0x0F];
	hex[1] = table_hex[c & 0x0F];
	write(1, hex, 2);
}

void	ft_print_format(unsigned int i, void *addr, unsigned int size)
{
	unsigned int	j;

	ft_print_addr(addr + i);
	write(1, ":", 1);
	j = i;
	while (j < (i + 16) && j < size)
	{
		if (j % 2 == 0)
			write(1, " ", 1);
		ft_print_char_hex(*(char *)(addr + j++));
	}
	if (j % 2 != 0)
	{
		write(1, "  ", 2);
		j++;
	}
	while (j % 16 != 0)
	{
		write(1, "     ", 5);
		j += 2;
	}
	write(1, " ", 1);
	j = i;
	while (j < (i + 16) && j < size)
		ft_print_char(*(char *)(addr + j++));
}

void	*ft_print_memory(void *addr, unsigned int size)
{
	unsigned int	i;

	i = 0;
	while (i < size)
	{
		ft_print_format(i, addr, size);
		write(1, "\n", 1);
		i += 16;
	}
	return (addr);
}
