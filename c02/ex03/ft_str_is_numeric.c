/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_numeric.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 00:40:54 by svilla-d          #+#    #+#             */
/*   Updated: 2023/07/10 00:48:20 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_str_is_numeric(char *str);

int	ft_str_is_numeric(char *str)
{
	unsigned int	i;

	i = 0;
	while (*(str + i) != '\0')
	{
		if (!(*(str + i) >= '0' && *(str + i) <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int main (void)
{
	char	myString1[11] = "0123456789";
	char	myString2[11] = "S3b4st14n";
	char	myString3[11];
	int		numeric;

	numeric = ft_str_is_numeric(myString1);
	printf("%s: %d\n", myString1, numeric);

	numeric = ft_str_is_numeric(myString2);
	printf("%s: %d\n", myString2, numeric);

	numeric = ft_str_is_numeric(myString3);
	printf("%s: %d\n", myString3, numeric);
	return (0);
}