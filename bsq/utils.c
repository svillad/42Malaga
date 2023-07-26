#include "utils.h"

int ft_atoi(char *str)
{
	int i;
	int num;
	int	n;

	n = ft_strlen(str);
	i = 0;
	num = 0;
	while(str[i] && str[i]>='0' && str[i]<='9'
		&& i < n - 3){
		num = num * 10 + str[i] - '0';
		i++;
	}
	return (num);
}

int ft_strlen(char *str)
{
	int i;
	
	i = 0;
	while(str[i])
		i++;
	return (i);
}

int ft_get_min_value(int a, int b, int c) {
    int minimum = a;
    if (b < minimum) {
        minimum = b;
    }
    if (c < minimum) {
        minimum = c;
    }
    return minimum;
}