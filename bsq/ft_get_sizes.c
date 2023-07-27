#include "ft_get_sizes.h"

int	ft_get_cols(char **map)
{
	int	j;

	j = 0;
	while (map[1][j] != '\0')
	{
		j++;
	}
	return (j + 1);
}

int	ft_get_row_size(char *str)
{
	int	row_size;
	int	i;

	row_size = 0;
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		row_size++;
		i++;
	}
	return (row_size + 1);
}

int	ft_get_rows(char *str)
{
	int	i;
	int	num;
	int	n;

	n = ft_strlen(str);
	i = 0;
	num = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9'
		&& i < n - 3)
	{
		num = num * 10 + str[i] - '0';
		i++;
	}
	return (num);
}
