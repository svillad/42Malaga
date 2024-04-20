/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 12:41:29 by svilla-d          #+#    #+#             */
/*   Updated: 2024/03/02 15:29:38 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	char	*s1_copy;
	char	*s2_copy;
	size_t	i;
	size_t	j;

	i = 0;
	if (*s2 == '\0')
		return ((char *)s1);
	while (*s1 && i < n)
	{
		s1_copy = (char *)s1;
		s2_copy = (char *)s2;
		j = i;
		while (*s1_copy == *s2_copy && *s1_copy && *s2_copy && j < n)
		{
			s1_copy++;
			s2_copy++;
			j++;
		}
		if (*s2_copy == '\0')
			return ((char *)s1);
		s1++;
		i++;
	}
	return (NULL);
}
