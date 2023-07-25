/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxgarci <maxgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 17:22:58 by maxgarci          #+#    #+#             */
/*   Updated: 2023/07/23 18:10:19 by maxgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DICTIONARY_H
# define DICTIONARY_H

# include <stdlib.h>
# include "file.h"
# include "utils.h"

# define NAME_SIZE 100

typedef struct _number {
	int		num;
	char	name[50];
}	t_number;

t_number	*ft_read_dictionary(char *file_name);
char		*ft_find_number(t_number dictionary[], int num);
void		ft_print_dictionary(t_number *dictionary);

#endif
