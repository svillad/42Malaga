/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simolina <simolina@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 12:36:54 by simolina          #+#    #+#             */
/*   Updated: 2023/07/16 12:36:54 by simolina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <unistd.h>

#define SIZE 4
#define PARAMS_SIZE 16
#define OK 0
#define ERROR 1

bool	ft_is_number(char c);
int		ft_strlen(char *str);

int	ft_check_char(char c_curr, char c_prev)
{
	if (c_curr == ' ')
	{
		if (c_prev == ' ')
			return (ERROR);
	}
	else if (ft_is_number(c_curr))
	{
		if (ft_is_number(c_prev))
			return (ERROR);
	}
	else
		return (ERROR);
	return (OK);
}

int	ft_transform_params(char *str, char *params)
{
	int	index;
	int	i;

	index = 0;
	if (!ft_is_number(str[0]) || !ft_is_number(str[ft_strlen(str)-1]))
		return (ERROR);
	params[index++] = str[0];
	i = 0;
	while (str[++i])
	{
		if (ft_check_char(str[i], str[i - 1]))
		{
			return (ERROR);
		}
		if (str[i] != ' ')
			params[index++] = str[i];
	}
	params[index] = '\0';
	return (OK);
}

bool	ft_is_valid_number(char *params)
{
	int	i;

	i = 0;
	while (params[i])
	{
		if (params[i] <= '0' || params[i] > (SIZE + 48))
			return (false);
		i++;
	}
	return (true);
}	

int	ft_get_params(char *argv[], char *params)
{
	int	error;

	error = ft_transform_params(argv[1], params);
	if (error)
	{
		return (ERROR);
	}
	if (ft_strlen(params) != PARAMS_SIZE)
	{
		return (ERROR);
	}
	if (!ft_is_valid_number(params))
	{
		return (ERROR);
	}
	return (OK);
}
