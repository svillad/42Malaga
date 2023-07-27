/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereca-ca <ereca-ca@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:42:18 by ereca-ca          #+#    #+#             */
/*   Updated: 2023/07/27 13:42:21 by ereca-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILS_H
# define FT_UTILS_H

# include <unistd.h>
# include <stdlib.h>

int		ft_strlen(char *str);
int		ft_min(int a, int b, int c);
char	*ft_strcpy(char *info, char *line1);
void	ft_free_memory(char **map, char *info, char *line1);

#endif
