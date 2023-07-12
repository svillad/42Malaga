/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:23:18 by svilla-d          #+#    #+#             */
/*   Updated: 2023/07/12 12:26:31 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

int	ft_strncmp(char *s1, char *s2, unsigned int n);

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	if (s1 == s2)
		return (0);
	i = 0;
	while (*(s1 + i) && *(s2 + i) && i < n - 1)
	{
		if (*(s1 + i) != *(s2 + i))
			break ;
		i++;
	}
	return (*(s1 + i) - *(s2 + i));
}

// int	main(void)
// {
// 	char palabra1[10] = "123455";
// 	char palabra2[10] = "123456";
// 	int r;
// 	int n = 6;

// 	r = strncmp(palabra1, palabra2, n);
// 	printf("%s, %s :: %d\n", palabra1, palabra2, r);

// 	r = ft_strncmp(palabra1, palabra2, n);
// 	printf("%s, %s :: %d\n", palabra1, palabra2, r);

// 	return (0);
// }