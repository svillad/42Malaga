/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gap_filler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simolina <simolina@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 10:50:34 by simolina          #+#    #+#             */
/*   Updated: 2023/07/16 13:01:21 by simolina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	vertical_finder(char A[][6]);
int	horizontal_finder(char A[][6]);

void	horizontal_filler(char A[][6], int posx, int posy, char r)
{
	int		count;
	int		p;

	if (horizontal_finder(A) != 1)
		return ;
	while (posy < 5)
	{	
		posx = 1;
		r = ':';
		count = 0;
		while (posx < 5)
		{
			if (A[posx][posy] != '*')
				r -= A[posx][posy] - '0';
			else
			{
				count++;
				p = posx;
			}
			posx++;
		}
		if (count == 1)
			A[p][posy] = r + '0';
		posy++;
	}
}

void	vertical_filler(char A[][6], int posx, int posy, char r)
{
	int		count;
	int		p;

	if (vertical_finder(A) != 1)
		return ;
	while (posx < 5)
	{	
		posy = 1;
		r = 10;
		count = 0;
		while (posy < 5)
		{
			if (A[posx][posy] != '*')
				r -= A[posx][posy] - '0';
			else
			{
				count++;
				p = posy;
			}
			posy++;
		}
		if (count == 1)
			A[posx][p] = r + '0';
		posx++;
	}
}

void	ft_gapfiller(char A[][6])
{	
	char	aux;

	aux = '0';
	vertical_filler(A, 1, 1, aux);
	horizontal_filler(A, 1, 1, aux);
}
