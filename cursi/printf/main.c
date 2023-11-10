/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 11:57:02 by svilla-d          #+#    #+#             */
/*   Updated: 2023/11/04 20:05:35 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"
#include "ft_printf.h"

int main() {
   
   printf("%d: ", printf("Letras:%c,%c,%c\n", 'A', 'B', 'C'));
   printf("%d: ", ft_printf("Letras:%c,%c,%c\n", 'A', 'B', 'C'));
   printf("\n\n");
   
   printf("%d: ", printf("Palabras:%s,%s,%s\n", "S3b@st1@n", "Villa", "Duarte"));
   printf("%d: ", ft_printf("Palabras:%s,%s,%s\n", "S3b@st1@n", "Villa", "Duarte"));
   printf("\n\n");

   printf("%d: ", printf("Numeros:%d,%i,%d\n", 123, 321, -123456789));
   printf("%d: ", ft_printf("Numeros:%d,%i,%d\n", 123, 321, -123456789));
   printf("\n\n");

   printf("%d: ", printf("UNumeros:%u,%u,%u\n", 123, 321, -123456789));
   printf("%d: ", ft_printf("UNumeros:%u,%u,%u\n", 123, 321, -123456789));
   printf("\n\n");

   printf("%d: ", printf("Porcentaje:%%\n"));
   printf("%d: ", ft_printf("Porcentaje:%%\n"));
   return 0;
}
