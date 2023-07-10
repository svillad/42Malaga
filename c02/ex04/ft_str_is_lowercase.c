/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_lowercase.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 00:50:04 by svilla-d          #+#    #+#             */
/*   Updated: 2023/07/10 01:14:12 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_str_is_lowercase(char *str);

int	ft_str_is_lowercase(char *str)
{
	unsigned int	i;

	i = 0;
	while (*(str + i) != '\0')
	{
		if (!(*(str + i) >= 'a' && *(str + i) <= 'z'))
			return (0);
		i++;
	}
	return (1);
}

int main (void)
{
	char	myString1[10] = "sebastian";
	char	myString2[10] = "S3b4st14n";
	char	myString3[10] = "Sebastian";
	char	myString4[10];
	int		lower;

	lower = ft_str_is_lowercase(myString1);
	printf("%s: %d\n", myString1, lower);

	lower = ft_str_is_lowercase(myString2);
	printf("%s: %d\n", myString2, lower);

	lower = ft_str_is_lowercase(myString3);
	printf("%s: %d\n", myString3, lower);

    lower = ft_str_is_lowercase(myString4);
	printf("%s: %d\n", myString4, lower);
	return (0);
}