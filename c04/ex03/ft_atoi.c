/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:25:22 by svilla-d          #+#    #+#             */
/*   Updated: 2023/07/17 18:20:31 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

typedef enum _estados {
	E_INICIAL,
	E_ESPACIOS,
	E_SIGNOS,
	E_NUMEROS,
	E_FIN
}	t_estados;

int	ft_char_in_str(char c, const char *str);
int	ft_atoi(char *str);

int	ft_char_in_str(char c, const char *str)
{
	int			i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}

t_estados	ft_get_state(t_estados estado, char c, int *num, int *signo)
{
	const char	spaces[] = " \n\v\t\r\f";
	const char	signs[] = "+-";
	const char	numbers[] = "0123456789";

	if (ft_char_in_str(c, spaces)
		&& (estado == E_INICIAL || estado == E_ESPACIOS))
		estado = E_ESPACIOS;
	else if (ft_char_in_str(c, signs)
		&& (estado == E_INICIAL || estado == E_ESPACIOS || estado == E_SIGNOS))
	{
		estado = E_SIGNOS;
		if (c == '-')
			*signo = *signo * -1;
	}
	else if (ft_char_in_str(c, numbers))
	{
		estado = E_NUMEROS;
		*num = *num * 10 + (c - 48);
	}
	else
		estado = E_FIN;
	return (estado);
}

int	ft_atoi(char *str)
{
	int			i;
	int			num;
	int			signo;
	t_estados	estado;

	estado = E_ESPACIOS;
	i = 0;
	signo = 1;
	num = 0;
	while (estado != E_FIN && str[i])
	{
		estado = ft_get_state(estado, str[i], &num, &signo);
		i++;
	}
	num = num * signo;
	return (num);
}

int	ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9'))
		return (1);
	return (0);
}

int	ft_atoi2(char *str)
{
	int	s;
	int	val;

	s = 1;
	val = 0;
	while (*str == ' ' || *str == '\n' || *str == '\t' || *str == '\f'
		|| *str == '\v' || *str == '\r')
		str++;
	if (*str == '-')
		s = -1;
	if (*str == '-' || *str == '+')
		++str;
	while (ft_isdigit(*str))
	{
		val = val * 10 + (*str - '0');
		str++;
	}
	val *= s;
	return (val);
}

int main() {
	printf("TEST\n");
	printf("%i\n", ft_atoi("\t\n\v\f\r      23"));
	printf("%i\n", ft_atoi(" -h1"));
	printf("%i\n", ft_atoi("     ------+++++---12341"));
	printf("%i\n", ft_atoi("     ------+++++---123413"));
	printf("%i\n", ft_atoi("00000000002147483647"));
	printf("%i\n", ft_atoi("-2147483648"));
	printf("%i\n", ft_atoi("a"));
	return (0);
}
