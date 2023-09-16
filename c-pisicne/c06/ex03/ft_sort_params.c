/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 14:04:53 by svilla-d          #+#    #+#             */
/*   Updated: 2023/07/25 14:12:10 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int		ft_strcmp(char *s1, char *s2);
void	ft_putstr(char *str);

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

void	ft_putstr(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		write(1, &str[i], 1);
}

void	ft_swapstr(char *str1, char *str2)
{
	int		i;
	char	aux[100];

	i = -1;
	while (str1[++i])
		aux[i] = str1[i];
	aux[i] = '\0';
	i = -1;
	while (str2[++i])
		str1[i] = str2[i];
	str1[i] = '\0';
	i = -1;
	while (aux[++i])
		str2[i] = aux[i];
	str2[i] = '\0';
}

int	main(int argn, char *argv[])
{
	int	i;
	int	j;

	if (argn <= 1)
		return (1);
	i = 0;
	j = 0;
	while (++i < argn - 1)
	{
		j = i;
		while (++j < argn)
		{
			if (ft_strcmp(argv[i], argv[j]) > 0)
				ft_swapstr(argv[i], argv[j]);
		}
	}
	i = 0;
	while (++i < argn)
	{
		ft_putstr(argv[i]);
		write(1, "\n", 1);
	}
	return (0);
}
