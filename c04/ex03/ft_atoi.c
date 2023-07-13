typedef enum {
    ESTADO_INICIAL,
	ESTADO_ESPACIOS,
	ESTADO_SIGNOS,
    ESTADO_NUMEROS,
    ESTADO_OTROS
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

int	ft_atoi(char *str)
{
	int	len;
	Estados control;

	len = ft_strlen(str);
	control = ESTADO_INICIAL;
	while (control != ESTADO_OTROS)
		i++;
	return (i);
}

