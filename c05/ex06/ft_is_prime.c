/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_prime.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:41:00 by svilla-d          #+#    #+#             */
/*   Updated: 2023/07/19 10:09:15 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_prime(int nb);

int	ft_is_prime(int nb)
{
	int	i;
	int	mitad;

	if (nb <= 1)
		return (0);
	if (nb > 2 && nb % 2 == 0)
		return (0);
	i = 3;
	mitad = nb / 2;
	while (i < mitad)
	{
		if (nb % i == 0)
			return (0);
		i += 2;
	}
	return (1);
}
