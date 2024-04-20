/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 23:39:37 by svilla-d          #+#    #+#             */
/*   Updated: 2024/04/20 20:12:44 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*strjoin_next(char *s1, char *s2)
{
	char	*strjoin;
	size_t	len1;
	size_t	len2;

	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char));
		if (!s1)
			return (0);
		s1[0] = 0;
	}
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	strjoin = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (!strjoin)
		return (free_ptr_char(&s1));
	len1 = -1;
	while (s1 && s1[++len1])
		strjoin[len1] = s1[len1];
	len2 = -1;
	while (s2 && s2[++len2])
		strjoin[len1 + len2] = s2[len2];
	strjoin[len1 + len2] = '\0';
	free(s1);
	return (strjoin);
}
