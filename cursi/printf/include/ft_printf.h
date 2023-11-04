/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 11:42:34 by svilla-d          #+#    #+#             */
/*   Updated: 2023/11/04 14:36:37 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

/**
 * @brief Prints data to the standard output, with a format similar to printf.
 * @param str (const char *): Format string that specifies the arrangement of the
 *        arguments.
 * @param ...: Variable arguments to be formatted and printed according to the
 *        format string.
 * @return The number of characters written or a negative value in case of an
 *         error.
 * @author Sebastian Villa
 */
int	ft_printf(const char *str, ...);

#endif
