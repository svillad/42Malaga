/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_square.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereca-ca <ereca-ca@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:19:35 by ereca-ca          #+#    #+#             */
/*   Updated: 2023/07/27 12:19:37 by ereca-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SQUARE_H
# define FT_SQUARE_H

# include <unistd.h>
# include <stdlib.h>
# include "ft_utils.h"

void	ft_put_square(char **map, int *square, char *line1);
int		*ft_find_max_square(int **smap, int rows, int cols);

#endif
