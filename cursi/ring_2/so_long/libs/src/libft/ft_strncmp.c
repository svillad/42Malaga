/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 10:18:51 by svilla-d          #+#    #+#             */
/*   Updated: 2024/03/06 11:47:36 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t				i;
	const unsigned char	*cp_s1 = (unsigned char *)s1;
	const unsigned char	*cp_s2 = (unsigned char *)s2;

	i = 0;
	if (s1 == s2 || n == 0)
		return (0);
	while (i < n && cp_s1[i] && cp_s2[i])
	{
		if (cp_s1[i] != cp_s2[i])
			return (cp_s1[i] - cp_s2[i]);
		i++;
	}
	if (i >= n)
		i--;
	return (cp_s1[i] - cp_s2[i]);
}
