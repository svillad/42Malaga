#include <stdio.h>
#include <unistd.h>
#include <limits.h>

#define OK				0
#define ERROR			1
#define ERROR_01		2
#define ERROR_POS_NEG	3
#define ERROR_CHAR_DUP	4

int		ft_strlen(char *str);
int		ft_check_base(char *base);
void	ft_putnbr_base(int nbr, char *base);

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (*str++)
		len++;
	return (len);
}

int ft_check_base(char *base)
{
	int	len;
	int i;
	int j;
	
	len = ft_strlen(base);
	if (len == 0 || len == 1)
		return (ERROR_01);
	i = 0;
	while (i < len)
	{
		if (base[i] == '+' || base[i] == '-')
			return (ERROR_POS_NEG);
		j = i+1;
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

void	ft_putnbr_base(int nbr, char *base)
{
	int	b;
	int i;
	char number[20];
	int err;

	err = ft_check_base(base);
	if (err){
		printf("Error: %d\n", err);
		return ;
	}

	if (nbr == 0){
		write(1, "0", 1);
		return ;
	}

	b = ft_strlen(base);
	i = 0;
	if (nbr < 0)
	{
		write(1, "-", 1);
		if (nbr == INT_MIN)
		{
			number[i] = base[(nbr % b) & 0x0F];
			nbr = nbr / b;
			
			// write(1,"**", 2);
			// write(1,&number[i], 1);
			// write(1,"**", 2);
			i++;
		}
		nbr = -nbr;
	}   
	while(nbr>0)
	{
		number[i] = base[(nbr % b) & 0x0F];
		nbr = nbr / b;
		i++;
	}
	while(i>0)
		write(1,&number[--i], 1);
		// printf("%c", number[--i]);
	// printf("\n");
	return ;
}


int		main(void)
{
	printf("c04 - ex04\n");
	write(1, "42:", 3);
	ft_putnbr_base(42, "0123456789");
	write(1, "\n2a:", 4);
	ft_putnbr_base(42, "0123456789abcdef");
	write(1, "\n-2a:", 5);
	ft_putnbr_base(-42, "0123456789abcdef");
	write(1, "\n0:", 3);
	ft_putnbr_base(0, "0123456789abcdef");
	write(1, "\nINT_MAX:", 9);
	ft_putnbr_base(INT_MAX, "0123456789");
	write(1, "\nINT_MAX:", 9);
	ft_putnbr_base(INT_MAX, "0123456789abcdef");
	write(1, "\nINT_MAX:", 9);
	ft_putnbr_base(INT_MAX, "ZYXWVUTSRQPONMLKJIHGFEDCBAzyxwvutsrqponmlkjihgfedcba9876543210");
	write(1, "\nINT_MIN:", 9);
	ft_putnbr_base(INT_MIN, "0123456789");
	write(1, "\nINT_MIN:", 9);
	ft_putnbr_base(INT_MIN, "0123456789abcdef");
	// write(1, "\n-2143247366 : ", 15);
	// ft_putnbr_base(INT_MIN + 4236282, "'~");
	write(1, "\n-1:", 4);
	ft_putnbr_base(-1, "0123456789abcdef");
	write(1, "\n:", 2);
	ft_putnbr_base(42, "");
	write(1, "\n:", 2);
	ft_putnbr_base(42, "0");
	write(1, "\n:", 2);
	ft_putnbr_base(42, "+-0123456789abcdef");
	write(1, "\n:", 2);
	ft_putnbr_base(42, "\v0123456789abcdef");
}