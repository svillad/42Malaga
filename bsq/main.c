#include <stdio.h>
#include "file.h"
#include "utils.h"

/*
*	Validate line 1:
*	1) min size: 4 (lines + empty + obstacle + mark)
*	2) lines: just numbers
*	3) disallow duplicate characters
*/
void		ft_check_first_line(char *line1, int n)
{
	int i;
	printf("line1 size: %d\n", n);
	printf("line1: %s\n", line1);
	if (n < 4)
		line1[0] = -1;
	i = 0;
	while ((line1[i] < '0' || line1[i] > '9') && i < n - 4)
	{
		line1[0] = -1;
		i++;
	}
	if (line1[n - 3] == line1[n - 2]
		|| line1[n - 3] == line1[n - 1]
		|| line1[n - 2] == line1[n - 1])
		line1[0] = -1;
}

char	*ft_get_first_line_input(char *str, int n)
{
	char	*line1;
	int		i;

	line1 = (char *)malloc(n * sizeof(char));
	i = -1;
	while (++i < n)
		line1[i] = str[i];
	line1[n] = '\0';
	ft_check_first_line(line1, n);
	return (line1);
}

int	ft_case_1(void)
{
	int		len;
	char	buffer[2048];
	char	*line1;
	int		i;
	int		lines;

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
	lines = ft_atoi(line1);
	while (++i < lines)
		read(STDIN_FILENO, buffer, 2048);
	return (0);
}

char	*ft_get_first_line_file(char *str)
{
	int		n;
	int		i;
	char	*line1;

	n = 0;
	while(str[n] && str[n] != '\n')
		n++;
	line1 = (char *)malloc(n * sizeof(char));
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

void	ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] && src[i] != '\n')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

int	ft_init_map(char **map, int rows, char *info)
{
	int	i;
	int	row_size;
	int j;

	map = (char **)malloc((rows + 1) * sizeof(char *));
	i = 0;
	j = 0;
	while (info[i])
	{
		row_size = ft_get_row_size(&info[i]);
		map[j] = (char *)malloc(row_size * sizeof(char));
		ft_strcpy(map[j], &info[i]);
		i += row_size;
		j++;
	}
	map[j] = NULL;
	ft_print_map(map);
	return (0);
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

int	ft_case_N(char *file_name)
{
	char	*info;
	char	*line1;
	int		rows;
	char	**map;

	map = NULL;
	info = ft_read_file(file_name);
	line1 = ft_get_first_line_file(info);
	if (line1[0] == -1)
	{
		ft_free_memory(map, info, line1);
		return (-1);
	}
	rows = ft_atoi(line1);
	ft_init_map(map, rows, &info[ft_strlen(line1)] + 1);
	ft_free_memory(map, info, line1);
	return (0);
}

int	main(int n, char **arg)
{
	int	i;

	if (n == 1)
	{
		if (ft_case_1() == -1)
			write(1, "Error\n", 6);
	}
	else
	{
		i = 0;
		while (++i < n)
		{
			if (ft_case_N(arg[i]) == -1)
				write(1, "Error\n", 6);
		}
	}
	return (0);
}
