/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereca-ca <ereca-ca@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:40:47 by ereca-ca          #+#    #+#             */
/*   Updated: 2023/07/27 13:40:50 by ereca-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_line_one.h"

/*
*	Validate line 1:
*	1) min size: 4 (lines + empty + obstacle + mark)
*	2) lines: just numbers
*	3) disallow duplicate characters
*/
void	ft_check_first_line(char *line1, int n)
{
	int	i;

	if (n < 4)
		line1[0] = -1;
	i = 0;
	while ((line1[i] < '0' || line1[i] > '9') && i < n - 3)
	{
		line1[0] = -1;
		i++;
	}
	if (line1[n - 3] == line1[n - 2]
		|| line1[n - 3] == line1[n - 1]
		|| line1[n - 2] == line1[n - 1])
		line1[0] = -1;
}

char	*ft_get_first_line_file(char *str)
{
	int		n;
	int		i;
	char	*line1;

	n = 0;
	while (str[n] && str[n] != '\n')
		n++;
	line1 = (char *)malloc(n * sizeof(char));
	if (!line1)
		return (NULL);
	i = -1;
	while (++i < n)
		line1[i] = str[i];
	line1[n] = '\0';
	ft_check_first_line(line1, n);
	return (line1);
}

char	*ft_get_first_line_input(char *str, int n)
{
	char	*line1;
	int		i;

	line1 = (char *)malloc(n * sizeof(char));
	if (!line1)
		return (NULL);
	i = -1;
	while (++i < n)
		line1[i] = str[i];
	line1[n] = '\0';
	ft_check_first_line(line1, n);
	return (line1);
}
