/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gaps_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simolina <simolina@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 10:36:24 by simolina          #+#    #+#             */
/*   Updated: 2023/07/16 11:52:16 by simolina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	horizontal_finder(char A[][6])
{
	int	posx;
	int	posy;
	int	gapnbr;

	posy = 1;
	gapnbr = 0;
	while (posy < 5 && gapnbr != 1)
	{
		gapnbr = 0;
		posx = 1;
		while (posx < 5)
		{
			if (A[posx][posy] == '*')
			{
				gapnbr++;
			}
			posx++;
		}
		posy++;
	}
	return (gapnbr);
}

int	vertical_finder(char A[][6])
{
	int	posx;
	int	posy;
	int	gapnbr;

	posx = 1;
	gapnbr = 0;
	while (posx < 5 && gapnbr != 1)
	{
		gapnbr = 0;
		posy = 1;
		while (posy < 5)
		{
			if (A[posx][posy] == '*')
			{
				gapnbr++;
			}
			posy++;
		}
		posx++;
	}
	return (gapnbr);
}

int	ft_gapfinder(char A[][6])
{	
	int	gapnbr;

	gapnbr = 0;
	gapnbr = vertical_finder(A);
	if (gapnbr != 1)
		gapnbr = horizontal_finder(A);
	return (gapnbr);
}
