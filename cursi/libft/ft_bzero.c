/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 08:40:28 by svilla-d          #+#    #+#             */
/*   Updated: 2023/09/30 14:23:49 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	ft_bzero(void *ptr, size_t n)
{
	unsigned char	*str;

	str = (unsigned char *)ptr;
	while (n > 0)
	{
		*str = 0;
		str++;
		n--;
	}
}
