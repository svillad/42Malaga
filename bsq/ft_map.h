#ifndef FT_MAP_H
# define FT_MAP_H

# include <unistd.h>
# include <stdlib.h>
# include "ft_get_sizes.h"

char	**ft_init_map(int rows, char *info, char *line1);
int		**ft_process_map(char **map, int rows, int cols, char cobst);
int		ft_copy_line(char *dest, char *src, char *line1);
char	*ft_get_line(int col_ref, char *info, char *line1);

#endif
