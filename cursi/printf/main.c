/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 11:57:02 by svilla-d          #+#    #+#             */
/*   Updated: 2023/11/04 13:50:47 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"
#include "ft_printf.h"

int main() {
   printf("Letras:%c,%c,%c\n", 'A', 'B', 'C');
   ft_printf("Letras:%c,%c,%c\n", 'A', 'B', 'C');

   printf("Palabras:%s,%s,%s\n", "S3b@st1@n", "Villa", "Duarte");
   ft_printf("Palabras:%s,%s,%s\n", "S3b@st1@n", "Villa", "Duarte");

   printf("Numeros:%d,%i,%d\n", 123, 321, -123456789);
   ft_printf("Numeros:%d,%i,%d\n", 123, 321, -123456789);

   printf("UNumeros:%u,%u,%u\n", 123, 321, -123456789);
   ft_printf("UNumeros:%u,%u,%u\n", 123, 321, -123456789);

   printf("Porcentaje:%%\n");
   ft_printf("Porcentaje:%%\n");

   return 0;
}
