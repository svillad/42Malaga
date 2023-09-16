/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simolina <simolina@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 13:07:11 by simolina          #+#    #+#             */
/*   Updated: 2023/07/16 14:01:53 by simolina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	valid_up(char A[][6])
{
	char	max;
	int		posx;
	int		posy;
	char	count;

	posx = 1;
	while (posx < 5)
	{	
		max = '0';
		count = '0';
		posy = 1;
		while (posy < 5)
		{
			if (A[posx][posy] > max)
			{
				count++;
				max = A[posx][posy];
			}
			posy++;
		}
		if (count != A[posx][0])
			return (1);
		posx++;
	}
	return (0);
}

int	valid_down(char A[][6])
{
	char	max;
	int		posx;
	int		posy;
	char	count;

	posx = 1;
	while (posx < 5)
	{	
		max = '0';
		count = '0';
		posy = 4;
		while (posy > 0)
		{
			if (A[posx][posy] > max)
			{
				count++;
				max = A[posx][posy];
			}
			posy--;
		}
		if (count != A[posx][5])
			return (1);
		posx++;
	}
	return (0);
}

int	valid_left(char A[][6])
{
	char	max;
	int		posx;
	int		posy;
	char	count;

	posy = 1;
	while (posy < 5)
	{	
		max = '0';
		count = '0';
		posx = 1;
		while (posx < 5)
		{
			if (A[posx][posy] > max)
			{
				count++;
				max = A[posx][posy];
			}
			posx++;
		}
		if (count != A[0][posy])
			return (1);
		posy++;
	}
	return (0);
}

int	valid_right(char A[][6])
{
	char	max;
	int		posx;
	int		posy;
	char	count;

	posy = 1;
	while (posy < 5)
	{	
		max = '0';
		count = '0';
		posx = 4;
		while (posx > 0)
		{
			if (A[posx][posy] > max)
			{
				count++;
				max = A[posx][posy];
			}
			posx--;
		}
		if (count != A[5][posy])
			return (1);
		posy++;
	}
	return (0);
}

int	valid_result(char A[][6])
{
	int	ok;

	ok = valid_up(A);
	ok += valid_down(A);
	ok += valid_left(A);
	ok += valid_right(A);
	return (ok);
}
