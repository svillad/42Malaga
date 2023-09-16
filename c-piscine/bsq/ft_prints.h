/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prints.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereca-ca <ereca-ca@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:19:10 by ereca-ca          #+#    #+#             */
/*   Updated: 2023/07/27 12:19:12 by ereca-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTS_H
# define FT_PRINTS_H

# include <unistd.h>

void	ft_print_map(char **map);
void	ft_print_smap(int **smap, int rows, int cols);

#endif
