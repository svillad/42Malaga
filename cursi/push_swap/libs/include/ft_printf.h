/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 11:42:34 by svilla-d          #+#    #+#             */
/*   Updated: 2024/02/24 20:48:53 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

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
/**
 * @brief Prints data to the fd, with a format similar to fprintf.
 * @param fd (int fd): File descriptor (1: standar, 2: error)
 * @param str (const char *): Format string that specifies the arrangement of the
 *        arguments.
 * @param ...: Variable arguments to be formatted and printed according to the
 *        format string.
 * @return The number of characters written or a negative value in case of an
 *         error.
 * @author Sebastian Villa
 */
int	ft_fprintf(int fd, const char *str, ...);
/**
 * @brief Prints unsigned int to the standard output.
 * @param num (unsigned int): number you want to write.
 * @return The number of characters written.
 * @author Sebastian Villa
 */
int	ft_print_unsigned(unsigned int num, int fd);
/**
 * @brief Prints int to the standard output.
 * @param num (int): number you want to write.
 * @return The number of characters written.
 * @author Sebastian Villa
 */
int	ft_print_signed(int num, int fd);
/**
 * @brief Prints hex to the standard output.
 * @param num (unsigned int): hex you want to write.
 * @param format (const char): hex you want to write ('x' or 'X').
 * @return The number of characters written.
 * @author Sebastian Villa
 */
int	ft_print_hex(unsigned int num, const char format, int fd);
/**
 * @brief Prints address to the standard output.
 * @param ptr (unsigned long long): address you want to write.
 * @return The number of characters written.
 * @author Sebastian Villa
 */
int	ft_print_addr(unsigned long long ptr, int fd);

#endif
