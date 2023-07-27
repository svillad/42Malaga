#include "ft_utils.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_get_min_value(int a, int b, int c)
{
	int	minimum;

	minimum = a;
	if (b < minimum)
		minimum = b;
	if (c < minimum)
		minimum = c;
	return (minimum);
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
