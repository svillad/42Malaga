/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:20:18 by svilla-d          #+#    #+#             */
/*   Updated: 2023/07/13 10:27:43 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

int	ft_strcmp(char *s1, char *s2);

int	ft_strcmp(char *s1, char *s2)
{
	unsigned int	i;

	i = 0;
	if (s1 == s2)
		return (0);
	while (*(s1 + i) && *(s2 + i))
	{
		if (*(s1 + i) != *(s2 + i))
			break ;
		i++;
	}
	return (*(s1 + i) - *(s2 + i));
}

// int	main(void)
// {
// 	char palabra1[10] = "1230";
// 	char palabra2[10] = "123";
// 	int r;

// 	r = strcmp(palabra1, palabra2);
// 	printf("%s, %s :: %d\n", palabra1, palabra2, r);

// 	r = ft_strcmp(palabra1, palabra2);
// 	printf("%s, %s :: %d\n", palabra1, palabra2, r);

// 	return (0);
// }