/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_int_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 01:29:00 by svilla-d          #+#    #+#             */
/*   Updated: 2023/07/09 01:33:08 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	ft_sort_int_tab(int *tab, int size);
void	ft_swap(int *a, int *b);

void	ft_swap(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	ft_sort_int_tab(int *tab, int size)
{
	int	i;
	int	j;
	int	pos_min;
	int	temp;

	i = 0;
	while (i < size - 1)
	{
		pos_min = i;
		j = i + 1;
		while (j < size)
		{
			if (*(tab + j) < *(tab + pos_min))
				pos_min = j;
			j++;
		}
		ft_swap((tab + pos_min), (tab + i));
		i++;
	}
}

void print_array(int *tab, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", tab[i]);
    }
    printf("\n");
}

int main() {
    int numbers[] = {9, 7, 5, 2, 8, 4, 1, 3, 6, 10, 18, 15, 13, 12, 11, 14, 16, 17, 19, 20};
    int size = sizeof(numbers) / sizeof(int);

    printf("Arreglo original: ");
    print_array(numbers, size);

    ft_sort_int_tab(numbers, size);
    printf("Arreglo ordenado por Selección: ");
    print_array(numbers, size);

    return 0;
}