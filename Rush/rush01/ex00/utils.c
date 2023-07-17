/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simolina <simolina@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 12:35:33 by simolina          #+#    #+#             */
/*   Updated: 2023/07/16 14:22:55 by simolina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

int	ft_char_in_str(char c, const char *str)
{
	int			i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}

bool	ft_is_number(char c)
{
	const char	number[] = "0123456789";

	if (ft_char_in_str(c, number))
		return (true);
	return (false);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_copy(char A[][6], char B[][6])
{
	int	posx;
	int	posy;

	posx = 0;
	while (posx < 6)
	{
		posy = 0;
		while (posy < 6)
		{
			B[posx][posy] = A[posx][posy];
			posy++;
		}
		posx++;
	}
}
