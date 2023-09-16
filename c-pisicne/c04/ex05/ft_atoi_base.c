/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 07:48:47 by svilla-d          #+#    #+#             */
/*   Updated: 2023/07/18 07:59:14 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define OK				0
#define ERROR			1
#define ERROR_01		2
#define ERROR_POS_NEG	3
#define ERROR_CHAR_DUP	4

typedef enum _estados {
	E_INICIAL,
	E_ESPACIOS,
	E_SIGNOS,
	E_NUMEROS,
	E_FIN
}	t_estados;

typedef struct _number
{
	int		n;
	int		b;
	int		signo;
	char	*base;
}	t_number;

int	ft_char_in_str(char c, const char *str);

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (*str++)
		len++;
	return (len);
}

int	ft_char_in_str(char c, const char *str)
{
	int			i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (i);
		i++;
	}
	return (-1);
}

t_estados	ft_get_state(t_estados estado, char c, t_number *num)
{
	int			dig;
	const char	spaces[] = " \n\v\t\r\f";
	const char	signs[] = "+-";

	dig = ft_char_in_str(c, num->base);
	if (ft_char_in_str(c, spaces) != -1
		&& (estado == E_INICIAL || estado == E_ESPACIOS))
		estado = E_ESPACIOS;
	else if (ft_char_in_str(c, signs) != -1
		&& (estado == E_INICIAL || estado == E_ESPACIOS || estado == E_SIGNOS))
	{
		estado = E_SIGNOS;
		if (c == '-')
			num->signo = num->signo * -1;
	}
	else if (dig != -1)
	{
		estado = E_NUMEROS;
		num->n = num->n * num->b + dig;
	}
	else
		estado = E_FIN;
	return (estado);
}

int	ft_check_base(char *base)
{
	int	len;
	int	i;
	int	j;

	len = ft_strlen(base);
	if (len == 0 || len == 1)
		return (ERROR_01);
	i = 0;
	while (i < len)
	{
		if (base[i] < ' ' || base[i] > '~')
			return (ERROR_POS_NEG);
		if (base[i] == '+' || base[i] == '-')
			return (ERROR_POS_NEG);
		j = i + 1;
		while (j < len)
		{
			if (base[i] == base[j])
				return (ERROR_CHAR_DUP);
			j++;
		}
		i++;
	}
	return (OK);
}

int	ft_atoi_base(char *str, char *base)
{
	int			i;
	t_estados	estado;
	t_number	numero;

	if (ft_check_base(base))
		return (0);
	numero.n = 0;
	numero.b = ft_strlen(base);
	numero.base = base;
	numero.signo = 1;
	estado = E_ESPACIOS;
	i = 0;
	while (estado != E_FIN && str[i])
	{
		estado = ft_get_state(estado, str[i], &numero);
		i++;
	}
	numero.n = numero.n * numero.signo;
	return (numero.n);
}
