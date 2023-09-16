/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxgarci <maxgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 17:22:40 by maxgarci          #+#    #+#             */
/*   Updated: 2023/07/23 23:06:24 by maxgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dictionary.h"
#include "rush02.h"
#include "utils.h"

int	ft_one_args(char **argv, t_number **dictionary, int *input_number)
{
	*input_number = ft_atoi(argv[1]);
	if (*input_number < 0)
	{
		ft_putstr("Error atoi: invalid number\n");
		return (1);
	}
	*dictionary = ft_read_dictionary("numbers.dict");
	if (!*dictionary)
	{
		ft_putstr("Dict Error\n");
		return (1);
	}
	return (0);
}

int	check_keys(t_number *dic_aux, t_number **dictionary)
{
	int	i;
	int	j;
	int	found;

	i = -1;
	j = -1;
	found = 1;
	while (found && dic_aux[++i].num != -1)
	{
		found = 0;
		j = -1;
		while (!found && ((*dictionary)[++j].num != -1))
			if (dic_aux[i].num == (*dictionary)[j].num)
				found = 1;
	}
	return (found);
}

int	ft_two_args(char **argv, t_number **dictionary, int *input_number)
{
	t_number	*dic_aux;

	*input_number = ft_atoi(argv[2]);
	if (*input_number < 0)
	{
		ft_putstr("Error atoi: invalid number\n");
		return (1);
	}
	dic_aux = NULL;
	dic_aux = ft_read_dictionary("numbers.dict");
	*dictionary = ft_read_dictionary(argv[1]);
	if (!*dictionary || !(check_keys(dic_aux, dictionary)))
	{
		ft_putstr("Dict Error\n");
		return (1);
	}
	free(dic_aux);
	return (0);
}

int	tam(t_number *dictionary)
{
	int	i;

	i = 0;
	while (dictionary[i].num != -1)
		i++;
	return (i);
}

int	main(int argc, char **argv)
{
	int			input_number;
	t_number	*dictionary;

	input_number = 0;
	dictionary = NULL;
	if (argc == 1)
	{
		ft_putstr("Error\n");
		return (1);
	}
	else if (argc == 2)
	{
		if (ft_one_args(argv, &dictionary, &input_number))
			return (1);
	}
	else if (argc == 3)
	{
		if (ft_two_args(argv, &dictionary, &input_number))
			return (1);
	}
	algorithm(input_number, dictionary, 1, 0);
	free(dictionary);
	return (0);
}
