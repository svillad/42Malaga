/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlowcase.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 01:21:31 by svilla-d          #+#    #+#             */
/*   Updated: 2023/07/10 01:44:06 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char	*ft_strlowcase(char *str);

char	*ft_strlowcase(char *str)
{
	unsigned int	i;

	i = 0;
	while (*(str + i) != '\0')
	{
		if (*(str + i) >= 'A' && *(str + i) <= 'Z')
			*(str + i) += 32;
		i++;
	}
	return (str);
}

int main (void)
{
	char	myString1[] = "SebaStian";
	char	myString2[] = "SEBASTIAN";
	char	myString3[] = "s3b@st1@n!";
	char	myString4[10];
	char	*lower;

	lower = ft_strlowcase(myString1);
	printf("%s\n", lower);

	lower = ft_strlowcase(myString2);
	printf("%s\n", lower);

	lower = ft_strlowcase(myString3);
	printf("%s\n", lower);

	lower = ft_strlowcase(myString4);
	printf("%s\n", lower);
	return (0);
}