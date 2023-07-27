#include "ft_map.h"

char	**ft_init_map(int rows, char *info, char *line1)
{
	int		i;
	int		j;
	int		col_ref;
	char	**map;

	if (info == NULL)
		return (NULL);
	map = (char **)malloc((rows + 1) * sizeof(char *));
	if (!map)
		return (NULL);
	i = 0;
	j = 0;
	col_ref = ft_get_row_size(&info[0]);
	while (info[i])
	{
		map[j] = ft_get_line(col_ref, &info[i], line1);
		if (!map[j])
			return (NULL);
		i += col_ref;
		j++;
	}
	if (j != rows)
		return (NULL);
	map[j] = NULL;
	return (map);
}

char	*ft_get_line(int col_ref, char *info, char *line1)
{
	int		col;
	char	*line;

	col = ft_get_row_size(info);
	if (col != col_ref)
		return (NULL);
	line = (char *)malloc(col * sizeof(char));
	if (!line)
		return (NULL);
	if (ft_copy_line(line, info, line1) < 0)
		return (NULL);
	return (line);
}

int	**ft_process_map(char **map, int rows, int cols, char cobst)
{
	int	i;
	int	j;
	int	**s_map;

	s_map = (int **)malloc(rows * sizeof(int *));
	if (!s_map)
		return (NULL);
	i = -1;
	while (map[++i] != NULL)
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

int	ft_copy_line(char *dest, char *src, char *line1)
{
	int	i;
	int	n;

	i = 0;
	n = ft_strlen(line1);
	while (src[i] && src[i] != '\n')
	{
		if (src[i] != line1[n - 2] && src[i] != line1[n - 3])
			return (-2);
		dest[i] = src[i];
		i++;
	}
	if (src[0] == '\n')
		return (-2);
	dest[i] = '\0';
	return (0);
}
