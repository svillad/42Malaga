/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:43:30 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/23 19:16:35 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;
	char	*p;

	len = (ft_strlen(s));
	p = (char *)s;
	while (len > 0)
	{
		if (p[len] == (char)c)
			return (&p[len]);
		len--;
	}
	if (!(p[len] == (char)c))
		return (0);
	return (&p[len]);
}
