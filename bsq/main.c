#include <stdio.h>
#include "ft_file.h"
#include "ft_utils.h"
#include "ft_get_sizes.h"
#include "ft_line_one.h"
#include "ft_prints.h"
#include "ft_square.h"
#include "ft_map.h"
#include "ft_case_n.h"

int	ft_case_1(void)
{
	int		len;
	char	buffer[2048];
	char	*line1;
	int		i;
	int		rows;
	int		cols;
	char	**map;
	int		**smap;
	int		*square;
	char	content[1000];

	len = read(STDIN_FILENO, buffer, 100);
	if (len == -1)
		return (-1);
	line1 = ft_get_first_line_input(buffer, len - 1);
	if (line1[0] == -1)
	{
		free(line1);
		return (-1);
	}
	i = -1;
	rows = ft_get_rows(line1);
	int j = 0;
	int k = 0;
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
	printf("data: \n%s\n", content);
	if(rows < 0)
		return (-2);

	map = ft_init_map(rows, content, line1);
	if (!map)
		return (-2);

	cols = ft_get_cols(map);

	ft_print_map(map);
	write(1, "\nBORRAR", 1);
	smap = ft_process_map(map, rows, cols, line1[ft_strlen(line1) - 2]);
	square = ft_find_max_square(smap, rows, cols);
	ft_put_square(map, square, line1);
	ft_print_map(map);
	//ft_free_memory(map, info, line1);
	return (0);
}

int	main(int n, char **arg)
{
	int	i;
	int error;

	if (n == 1)
	{
		error = ft_case_1();
		if (error == -1)
			write(1, "error\n", 6);
		else if (error == -2)
			write(1, "map error\n", 10);
	}
	else
	{
		i = 0;
		while (++i < n)
		{
			error = ft_case_n(arg[i]);
			if (error == -1)
				write(1, "error\n", 6);
			else if (error == -2)
				write(1, "map error\n", 10);
		}
	}
	return (0);
}
