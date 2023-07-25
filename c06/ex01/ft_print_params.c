/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_params.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:44:30 by svilla-d          #+#    #+#             */
/*   Updated: 2023/07/25 14:11:34 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr(char *str);

void	ft_putstr(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		write(1, &str[i], 1);
}

int	main(int argn, char *argv[])
{
	int	i;

	if (argn <= 1)
		return (1);
	i = 0;
	while (++i < argn)
	{
		ft_putstr(argv[i]);
		write(1, "\n", 1);
	}
	return (0);
}
