#ifndef FT_UTILS_H
# define FT_UTILS_H

# include <unistd.h>
# include <stdlib.h>

int		ft_strlen(char *str);
int		ft_get_min_value(int a, int b, int c);
void	ft_free_memory(char **map, char *info, char *line1);

#endif
