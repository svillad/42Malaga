
#include <stdio.h>
#include <string.h>

char *ft_strncat(char *dest, char *src, unsigned int nb);

char *ft_strncat(char *dest, char *src, unsigned int nb)
{
    unsigned int    i;
    unsigned int    j;

    i = 0;
     while (*(dest+i))
        i++;
    j = 0;
    while (*(src+j) && j < nb)
	{
        *(dest+i+j) = *(src+j);
		j++;
	}
    *(dest+i+j) = '\0';
    return (dest);
}

int	main(void)
{
	char palabra1[10] = "ABCDE";
	char palabra2a[20] = "123";
	char palabra2b[20] = "123";
	char *ra, *rb;
	unsigned int n = -1;

	ra = strncat(palabra2a, palabra1, n);
	printf("%s, %s :: %s\n", palabra1, palabra2a, ra);

	rb = ft_strncat(palabra2b, palabra1, n);
	printf("%s, %s :: %s\n", palabra1, palabra2b, rb);

	return (0);
}