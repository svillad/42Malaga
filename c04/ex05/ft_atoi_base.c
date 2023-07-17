

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (*str++)
		len++;
	return (len);
}

int	ft_get_position_in_base(char c, char *base)
{
	int i;

	i = 0;
	while(base[i])
	{
		if(c == base[i])
			return i;
	}
	return (-1);
}

int	ft_atoi_base(char *str, char *base)
{
	int		i;
	int		num;
	int		b;
	char	dig;

	b = ft_strlen(base);
	i = 0;
	while(str[i])
	{
		dig = str[i];
		if(ft_get_position_in_base(dig, base) == -1)
		{
			return (0);
		}

	}
}
