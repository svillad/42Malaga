#include <stdio.h>
#include "file.h"
#include "utils.h"
#include "line_one.h"

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

void ft_print_map(char **map)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (map[i]!=NULL)
	{
		j = 0;
		while (map[i][j])
		{
			write(1, &map[i][j], 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}

void ft_print_smap(int **smap, int rows, int cols)
{
	int i;
	int j;
	char c;

	i = 0;
	j = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			c = smap[i][j] + '0';
			write(1, &c, 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}

int	ft_get_row_size(char *str)
{
	int row_size;
	int i;

	row_size = 0;
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		row_size++;
		i++;
	}
	return (row_size + 1);
}

int	ft_copy_line(char *dest, char *src, char *line1)
{
	int	i;
	int n;

	i = 0;
	n = ft_strlen(line1);
	while (src[i] && src[i] != '\n')
	{
		if(src[i] != line1[n - 2] && src[i] != line1[n - 3])
			return (-2);
		dest[i] = src[i];
		i++;
	}
	if (src[0] == '\n')
		return(-2);
	dest[i] = '\0';
	return (0);
}

char	**ft_init_map(int rows, char *info, char *line1)
{
	int		i;
	int		j;
	int		col;
	int		col_prev;
	char	**map;

	if (info == NULL)
		return (NULL);
	map = (char **)malloc((rows + 1) * sizeof(char *));
	if (!map)
		return (NULL);
	i = 0;
	j = 0;
	col_prev = ft_get_row_size(&info[0]);
	while (info[i])
	{
		col = ft_get_row_size(&info[i]);
		if (col != col_prev)
			return (NULL);
		map[j] = (char *)malloc(col * sizeof(char));
		if (!map[j])
			return (NULL);
		if (ft_copy_line(map[j], &info[i], line1) < 0)
			return (NULL);
		i += col;
		j++;
	}
	if (j != rows)
		return (NULL);

	map[j] = NULL;
	return (map);
}


int	**ft_process_map(char **map, int rows, int cols, char cobst)
{
	int	i;
	int	j;
	int **s_map;

	s_map = (int **)malloc(rows * sizeof(int *));
	if (!s_map)
		return (NULL);
	i = -1;
	while (map[++i]!=NULL)
	{
		s_map[i] = (int *)malloc(cols * sizeof(int));
		j = 0;
		while (map[i][j])
		{
			if ((i == 0 || j == 0) && map[i][j] != cobst)
				s_map[i][j] = 1;
			else if (map[i][j] == cobst)
				s_map[i][j] = 0;
			else
				s_map[i][j] = ft_get_min_value(s_map[i - 1][j],
				s_map[i][j - 1], s_map[i - 1][j - 1]) + 1;
			j++;
		}
	}
	return (s_map);
}

int *ft_find_max_square(int **smap, int rows, int cols)
{
	int	i;
	int	j;
	int *square;

	square = (int *)malloc(3 * sizeof(int));
	if (!square)
		return (NULL);
	i = -1;
	square[2] = smap[0][0];
	while (++i < rows)
	{
		j = -1;
		while (++j < cols)
		{			
			if (smap[i][j] > square[2])
			{
				square[0] = i;
				square[1] = j;
				square[2] = smap[i][j];
			}

		}
	}
	square[0] = square[0] - square[2] + 1;
	square[1] = square[1] - square[2] + 1;
	return (square);
}

void	ft_free_memory(char **map, char *info, char *line1)
{
	int	i;

	i = 0;
	if (map != NULL)
	{
		while (map[i] != NULL)
		{
			free(map[i]);
			map[i] = NULL;
			i++;
		}
		free(map[i]);
		map[i] = NULL;
		free(map);
	}
	if (info != NULL)
		free(info);
	if (line1 != NULL)
		free(line1);
	map = NULL;
	info = NULL;
	line1 = NULL;
}

int ft_get_col(char **map)
{
    int j;

    j = 0;
    while(map && map[0][j] != '\0')
    {
        j++;
    }
    return (j);
}

void   ft_put_square(char **map, int *square, char *line1)
{
	int i;
	int j;
	int n;
	int nx;

	n = ft_strlen(line1);
	i = square[0];
	j = square[1];
	nx = square[2];
	while (i < (square[0] + nx))
	{
		map[i][j] = line1[n - 1];
		j++;
		if (j == (square[1] + nx))
		{
			i++;
			j = j - nx;
		}
	}
}

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

	cols = ft_get_col(map);

	ft_print_map(map);
	write(1, "\nBORRAR", 1);
	smap = ft_process_map(map, rows, cols, line1[ft_strlen(line1) - 2]);
	square = ft_find_max_square(smap, rows, cols);
	ft_put_square(map, square, line1);
	ft_print_map(map);
	//ft_free_memory(map, info, line1);
	return (0);
}

int	ft_case_N(char *file_name)
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
	line1 = ft_get_first_line_file(info);
	if (line1[0] == -1)
	{
		ft_free_memory(map, info, line1);
		return (-2);
	}
	rows = ft_get_rows(line1);
	if(rows < 0)
		return (-2);
	map = ft_init_map(rows, &info[ft_strlen(line1) + 1], line1);
	if (!map)
		return (-2);
	cols = ft_get_col(map);
	ft_print_map(map);
	write(1, "\nBORRAR", 1);
	smap = ft_process_map(map, rows, cols, line1[ft_strlen(line1) - 2]);
	square = ft_find_max_square(smap, rows, cols);
	ft_put_square(map, square, line1);
	ft_print_map(map);
	ft_free_memory(map, info, line1);
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
			error = ft_case_N(arg[i]);
			if (error == -1)
				write(1, "error\n", 6);
			else if (error == -2)
				write(1, "map error\n", 10);
		}
	}
	return (0);
}
