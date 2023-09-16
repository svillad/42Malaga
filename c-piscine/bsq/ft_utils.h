/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:42:18 by ereca-ca          #+#    #+#             */
/*   Updated: 2023/07/27 17:20:38 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILS_H
# define FT_UTILS_H

# include <unistd.h>
# include <stdlib.h>
#include <stdio.h>


int		ft_strlen(char *str);
int		ft_min(int a, int b, int c);
char	*ft_strcpy(char *info, char *line1);
void	ft_free_memory(char **map, char *info, char *line1);

#endif
