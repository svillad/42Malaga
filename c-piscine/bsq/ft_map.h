/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereca-ca <ereca-ca@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:18:48 by ereca-ca          #+#    #+#             */
/*   Updated: 2023/07/27 12:18:51 by ereca-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MAP_H
# define FT_MAP_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "ft_get_sizes.h"

char	**ft_init_map(int rows, char *info, char *line1);
int		**ft_process_map(char **map, int rows, int cols, char cobst);
int		ft_copy_line(char *dest, char *src, char *line1);
char	*ft_get_line(int col_ref, char *info, char *line1);

#endif
