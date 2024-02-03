/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 22:40:35 by svilla-d          #+#    #+#             */
/*   Updated: 2023/11/11 12:27:38 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_putstr_fd(char *s, int fd)
{
	int	printed_chars;

	printed_chars = 0;
	if (s == NULL)
	{
		write(fd, "(null)", 6);
		return (6);
	}
	while (*s)
	{
		write(fd, s, 1);
		s++;
		printed_chars++;
	}
	return (printed_chars);
}
