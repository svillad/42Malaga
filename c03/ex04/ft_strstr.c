/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:33:55 by svilla-d          #+#    #+#             */
/*   Updated: 2023/07/12 12:34:36 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

char	*ft_strstr(char *str, char *to_find);

char	*ft_strstr(char *str, char *to_find)
{
	char	*str_copy;
	char	*to_find_copy;

	if (*to_find == '\0')
		return (str);
	while (*str)
	{
		str_copy = str;
		to_find_copy = to_find;
		while (*str_copy == *to_find_copy && *str_copy && *to_find_copy)
		{
			str_copy++;
			to_find_copy++;
		}
		if (*to_find_copy == '\0')
			return (str);
		str++;
	}
	return (0);
}

// int	main(void)
// {
// 	char palabra1[] = "123 56 789 0";
// 	char to_find[] = "56";
// 	char *ra, *rb;

// 	ra = strstr(palabra1, to_find);
// 	printf("%s, %s :: %s(%p)\n", palabra1, to_find, ra, ra);

// 	rb = ft_strstr(palabra1, to_find);
// 	printf("%s, %s :: %s(%p)\n", palabra1, to_find, rb, rb);

// 	return (0);
// }