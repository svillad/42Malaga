#ifndef SO_LONG_H
# define SO_LONG_H

# include "ft_printf.h"
# include "push_swap.h"

typedef struct s_map
{
    char    **map;
	char	*name;
	int		height;
	int		width;
    int     capacity;
}	t_map;

#include "so_long.h"

void	check_extension(t_map *map);
void	init_map(t_map *map);
void	read_map(t_map *map);

void	ft_error_map(t_map *map, const char *message);
void	ft_free_map(t_map *map);

void    validate_map(t_map *map);

#endif