/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_case_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereca-ca <ereca-ca@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:38:59 by ereca-ca          #+#    #+#             */
/*   Updated: 2023/07/27 13:39:02 by ereca-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_case_1.h"

void	ft_free_memory_sln_1(int **smap, int *square)
{
	int	i;

	i = 0;
	if (smap != NULL)
	{
		while (smap[i] != NULL)
		{
			free(smap[i]);
			smap[i] = NULL;
			i++;
		}
		free(smap[i]);
		smap[i] = NULL;
		free(smap);
	}
	if (square != NULL)
		free(square);
	smap = NULL;
	square = NULL;
}

int	ft_case_1(void)
{
	char	buffer[2048];
	int		len;
	int		rows;
	char	*line1;
	char	*content;

	content = NULL;
	len = read(STDIN_FILENO, buffer, 256);
	if (len == -1)
		return (-2);
	line1 = ft_get_first_line_input(buffer, len - 1);
	if (!line1 || line1[0] == -1)
	{
		free(line1);
		return (-2);
	}
	rows = ft_get_rows(line1);
	content = ft_get_info(rows, content);
	if (!content)
	{
		free(line1);
		return (-2);
	}
	return (ft_process_data_case_1(content, line1));
}

char	*ft_get_info(int rows, char *content)
{
	int		len;
	char	buffer[2048];
	int		i;
	int		j;
	int		k;

	i = -1;
	j = 0;
	k = 0;
	content = (char *)malloc((2049) * sizeof(char));
	while (++i < rows)
	{
		len = read(STDIN_FILENO, buffer, 2048);
		k = 0;
		while (k < len)
		{
			content[j] = buffer[k];
			j++;
			k++;
		}
		content[j] = '\0';
	}
	return (content);
}

int	ft_process_data_case_1(char *content, char *line1)
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
	map = ft_init_map(rows, content, line1);
	if (!map)
	{
		ft_free_memory(map, content, line1);
		return (-2);
	}
	cols = ft_get_cols(map);
	smap = ft_process_map(map, rows, cols, line1[ft_strlen(line1) - 2]);
	square = ft_find_max_square(smap, rows, cols);
	ft_put_square(map, square, line1);
	ft_print_map(map);
	ft_free_memory(map, content, line1);
	ft_free_memory_sln_1(smap, square);
	return (0);
}
