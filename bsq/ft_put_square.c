
#include <unistd.h>

void   ft_put_square(char **map, int l, int c, int nx)
{
	int i;
	int j;

	i = l;
	j = c;
	while (i < (l + nx))
	{
		map[i][j] = 'x';
		j++;
		if (j == (c + nx))
		{
			i++;
			j = j - nx;
		}
	}
}