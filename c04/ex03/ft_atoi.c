typedef enum {
	E_INICIAL,
	E_ESPACIOS,
	E_SIGNOS,
	E_NUMEROS,
	E_OTROS
} Estados;

int	ft_atoi(char *str);
int	ft_strlen(char *str);

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (*(str+i))
		i++;
	return (i);
}

int	ft_is_space(char c){
	int i;
	const char	spaces[] = " \n\v\t\r\f";

	int i = 0;
	while (spaces[i])
	{
		if (c == spaces[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_is_sign(char c){
	int i;
	const char	sign[] = "+-";

	int i = 0;
	while (sign[i])
	{
		if (c == sign[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_atoi(char *str)
{
	int	len;
	Estados control;

	len = ft_strlen(str);
	control = E_INICIAL;
	while (control != E_OTROS){
		if (ft_is_space(*str))
			control = ESTADO_ESPACIOS;
		else if (ft_is_sign(*str))
			control = ESTADO_SIGNOS;
		else if ()
	}
	return (i);
}

