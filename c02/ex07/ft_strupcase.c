/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strupcase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 01:18:25 by svilla-d          #+#    #+#             */
/*   Updated: 2023/07/10 01:43:59 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char	*ft_strupcase(char *str);

char	*ft_strupcase(char *str)
{
	unsigned int	i;

	i = 0;
	while (*(str + i) != '\0')
	{
		if (*(str + i) >= 'a' && *(str + i) <= 'z')
			*(str + i) -= 32;
		i++;
	}
	return (str);
}

int main (void)
{
	char	myString1[] = "SebaStian";
	char	myString2[] = "sebastian";
	char	myString3[] = "s3b@st1@n!";
	char	myString4[10];
	char	*upper;

	upper = ft_strupcase(myString1);
	printf("%s\n", upper);

	upper = ft_strupcase(myString2);
	printf("%s\n", upper);

	upper = ft_strupcase(myString3);
	printf("%s\n", upper);

	upper = ft_strupcase(myString4);
	printf("%s\n", upper);
	return (0);
}