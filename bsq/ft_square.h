#ifndef FT_SQUARE_H
# define FT_SQUARE_H

# include <unistd.h>
# include <stdlib.h>
# include "ft_utils.h"

void	ft_put_square(char **map, int *square, char *line1);
int		*ft_find_max_square(int **smap, int rows, int cols);

#endif
