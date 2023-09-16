/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_printable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 01:18:14 by svilla-d          #+#    #+#             */
/*   Updated: 2023/07/10 02:16:37 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_str_is_printable(char *str);

int	ft_str_is_printable(char *str)
{
	unsigned int	i;

	i = 0;
	while (*(str + i) != '\0')
	{
		if (*(str + i) < ' ' || *(str + i) > '~')
			return (0);
		i++;
	}
	return (1);
}

int main (void)
{
	char	myString1[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
	char	myString2[10] = {31};
	char	myString3[10] = {127};
	char	myString4[10];
	int		ok;

	ok = ft_str_is_printable(myString1);
	printf("%s: %d\n", myString1, ok);

	ok = ft_str_is_printable(myString2);
	printf("%s: %d\n", myString2, ok);

	ok = ft_str_is_printable(myString3);
	printf("%s: %d\n", myString3, ok);

	ok = ft_str_is_printable(myString4);
	printf("%s: %d\n", myString4, ok);
	return (0);
}