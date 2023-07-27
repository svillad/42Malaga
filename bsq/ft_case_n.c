/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_case_n.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereca-ca <ereca-ca@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:39:43 by ereca-ca          #+#    #+#             */
/*   Updated: 2023/07/27 13:39:46 by ereca-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_case_n.h"

void	ft_free_info_line1(char *info, char *line1)
{
	if (info != NULL)
		free(info);
	if (line1 != NULL)
		free(line1);
}

void	ft_free_memory_sln(int **smap, int *square)
{
	int	i;

	i = 0;
	if (smap != NULL)
	{
		while (smap[i] != NULL)
		{
			free(smap[i]);
			i++;
		}
		free(smap);
	}
	if (square != NULL)
		free(square);
}

int	ft_process_data(char *info, char *line1)
{
	char	**map;
	int		rows;
	int		cols;
	int		**smap;
	int		*square;

	map = NULL;
	smap = NULL;
	rows = ft_get_rows(line1);
	if (rows < 0)
		return (-2);
	map = ft_init_map(rows, &info[ft_strlen(line1) + 1], line1);
	if (!map)
	{
		ft_free_info_line1(info, line1);
		return (-2);
	}
	cols = ft_get_cols(map);
	smap = ft_process_map(map, rows, cols, line1[ft_strlen(line1) - 2]);
	square = ft_find_max_square(smap, rows, cols);
	ft_put_square(map, square, line1);
	ft_print_map(map);
	ft_free_memory(map, info, line1);
	ft_free_memory_sln(smap, square);
	return (0);
}

int	ft_case_n(char *file_name)
{
	char	*info;
	char	*line1;

	info = ft_read_file(file_name);
	if (!info)
	{
		free(info);
		return (-2);
	}
	line1 = ft_get_first_line_file(info);
	if (!line1 || line1[0] == -1)
	{
		free(info);
		if (!line1)
			free(line1);
		return (-2);
	}
	return (ft_process_data(info, line1));
}
