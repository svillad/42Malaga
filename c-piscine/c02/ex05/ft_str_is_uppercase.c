/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_uppercase.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 00:54:39 by svilla-d          #+#    #+#             */
/*   Updated: 2023/07/10 01:04:37 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_str_is_uppercase(char *str);

int	ft_str_is_uppercase(char *str)
{
	unsigned int	i;

	i = 0;
	while (*(str + i) != '\0')
	{
		if (!(*(str + i) >= 'A' && *(str + i) <= 'Z'))
			return (0);
		i++;
	}
	return (1);
}

int main (void)
{
	char	myString1[10] = "SEBASTIAN";
	char	myString2[10] = "S3b4st14n";
	char	myString3[10] = "Sebastian";
	char	myString4[10];
	int		upper;

	upper = ft_str_is_uppercase(myString1);
	printf("%s: %d\n", myString1, upper);

	upper = ft_str_is_uppercase(myString2);
	printf("%s: %d\n", myString2, upper);

	upper = ft_str_is_uppercase(myString3);
	printf("%s: %d\n", myString3, upper);

    upper = ft_str_is_uppercase(myString4);
	printf("%s: %d\n", myString4, upper);
	return (0);
}