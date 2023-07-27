/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_case_1.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereca-ca <ereca-ca@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:16:16 by ereca-ca          #+#    #+#             */
/*   Updated: 2023/07/27 12:16:20 by ereca-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CASE_1_H
# define FT_CASE_1_H

# include <unistd.h>
# include "ft_file.h"
# include "ft_line_one.h"
# include "ft_utils.h"
# include "ft_get_sizes.h"
# include "ft_map.h"
# include "ft_prints.h"
# include "ft_square.h"

int		ft_case_1(void);
char	*ft_get_info(int rows, char *conent);
int		ft_process_data_case_1(char *content, char *line1);

#endif
