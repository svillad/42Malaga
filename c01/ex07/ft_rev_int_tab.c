/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_rev_int_tab.c								   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: svilla-d <svilla-d@student.42malaga.com	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/07/09 01:08:20 by svilla-d		  #+#	#+#			 */
/*   Updated: 2023/07/09 01:16:12 by svilla-d		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include <stdio.h>

void	ft_rev_int_tab(int *tab, int size);
void	ft_swap(int *a, int *b);

void	ft_swap(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	ft_rev_int_tab(int *tab, int size)
{
	int	i;
	int	temp;

	i = 0;
	while (i < size / 2)
	{
		ft_swap((tab + i), (tab + size - i - 1));
		i++;
	}
}

int main(void) {
	int numbers[] = {1, 2, 3, 4, 5, 6};
	int size = sizeof(numbers) / sizeof(numbers[0]);
	int i;

	printf("Array antes de invertir: ");
	for (i = 0; i < size; i++)
	{
		printf("%d ", numbers[i]);
	}
	printf("\n");

	ft_rev_int_tab(numbers, size);

	printf("Array después de invertir: ");
	for (i = 0; i < size; i++)
	{
		printf("%d ", numbers[i]);
	}
	printf("\n");

	return 0;
}