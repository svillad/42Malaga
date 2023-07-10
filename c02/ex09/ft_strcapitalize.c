/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 01:27:11 by svilla-d          #+#    #+#             */
/*   Updated: 2023/07/10 01:49:09 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char	*ft_strcapitalize(char *str);
int		ft_is_alphanumeric(char c);

int	ft_is_alphanumeric(char c)
{
	if ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

char	*ft_strcapitalize(char *str)
{
	unsigned int	i;

	if (*str >= 'a' && *str <= 'z')
		*str -= 32;
	i = 1;
	while (*(str + i) != '\0')
	{
		if (*(str + i) >= 'A' && *(str + i) <= 'Z')
			*(str + i) += 32;
		if (!ft_is_alphanumeric(*(str + i - 1)))
		{
			if (*(str + i) >= 'a' && *(str + i) <= 'z')
				*(str + i) -= 32;
		}
		i++;
	}
	return (str);
}

int main (void)
{
	char	myString1[] = "salut, comment tu vas ? 42mots quarante-deux; cinquante+et+un";
	char	myString2[] = " uno dos+tres@cuatroCinco";
	char	myString3[] = "sebastian.villa.duarte, malaga, andalucia.";
	char	myString4[10];
	char	*capitalize;

	capitalize = ft_strcapitalize(myString1);
	printf("%s\n", capitalize);

	capitalize = ft_strcapitalize(myString2);
	printf("%s\n", capitalize);

	capitalize = ft_strcapitalize(myString3);
	printf("%s\n", capitalize);

	capitalize = ft_strcapitalize(myString4);
	printf("%s\n", capitalize);
	return (0);
}
