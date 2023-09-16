/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_alpha.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 00:40:54 by svilla-d          #+#    #+#             */
/*   Updated: 2023/07/10 01:00:15 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_str_is_alpha(char *str);

int	ft_str_is_alpha(char *str)
{
	unsigned int	i;

	i = 0;
	while (*(str + i) != '\0')
	{
		if (!((*(str + i) >= 'a' && *(str + i) <= 'z')
				|| (*(str + i) >= 'A' && *(str + i) <= 'Z')))
			return (0);
		i++;
	}
	return (1);
}

int main (void)
{
	char	myString1[10] = "Sebastian";
	char	myString2[10] = "S3b4st14n";
	char	myString3[10];
	int		alpha;

	alpha = ft_str_is_alpha(myString1);
	printf("%s: %d\n", myString1, alpha);

	alpha = ft_str_is_alpha(myString2);
	printf("%s: %d\n", myString2, alpha);

	alpha = ft_str_is_alpha(myString3);
	printf("%s: %d\n", myString3, alpha);
	return (0);
}