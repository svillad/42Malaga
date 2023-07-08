/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 00:28:37 by svilla-d          #+#    #+#             */
/*   Updated: 2023/07/09 00:36:15 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr(char *str);

void	ft_putstr(char *str)
{
	while (*str != '\0')
		write(1, str++, 1);
}

int main() {
    char	*myString;

	myString = "Hola, mundo!";
    ft_putstr(myString);
    return (0);
}