/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_non_printable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 02:08:55 by svilla-d          #+#    #+#             */
/*   Updated: 2023/07/14 09:59:56 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_char_to_hex(char c, char *hex)
{
	const char	table_hex[] = "0123456789abcdef";

	hex[0] = '\\';
	hex[1] = table_hex[(c / 16) & 0x0F];
	hex[2] = table_hex[c % 16];
}

void	ft_putstr_non_printable(char *str)
{
	unsigned int	i;
	char			hex[3];

	i = 0;
	while (*(str + i) != '\0')
	{
		if (*str < ' ' || *str > '~')
		{
			ft_char_to_hex(*str + i, hex);
			write(1, hex, 3);
		}
		else
		{
			write(1, str, 1);
		}
		str++;
	}
}

int	main(void)
{
	char	myString1[] = "Coucou\ntu vas bien ?";

	ft_putstr_non_printable(myString1);

	return (0);
}