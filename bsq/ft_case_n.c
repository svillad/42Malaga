#include "ft_case_n.h"

int	ft_case_n(char *file_name)
{
	char	*info;
	char	*line1;
	char	**map;
	int		rows;
	int		cols;
	int		**smap;
	int		*square;

	map = NULL;
	smap = NULL;
	info = ft_read_file(file_name);
	if (!info)
		return (-2);
	line1 = ft_get_first_line_file(info);
	if (!line1 || line1[0] == -1)
	{
		ft_free_memory(map, info, line1);
		return (-2);
	}
	rows = ft_get_rows(line1);
	if (rows < 0)
		return (-2);
	map = ft_init_map(rows, &info[ft_strlen(line1) + 1], line1);
	if (!map)
		return (-2);
	cols = ft_get_cols(map);
	ft_print_map(map);
	write(1, "\nBORRAR", 1);
	smap = ft_process_map(map, rows, cols, line1[ft_strlen(line1) - 2]);
	square = ft_find_max_square(smap, rows, cols);
	ft_put_square(map, square, line1);
	ft_print_map(map);
	ft_free_memory(map, info, line1);
	return (0);
}

