
#include <stdio.h>
#include <string.h>

char *ft_strcat(char *dest, char *src);

char *ft_strcat(char *dest, char *src)
{
    unsigned int    i;
    unsigned int    j;

    i = 0;
     while (*(dest+i))
        i++;
    j = 0;
    while (*(src+j))
	{
        *(dest+i+j) = *(src+j);
		j++;
	}
    *(dest+i+j) = '\0';
    return (dest);
}

int	main(void)
{
	char palabra1[10] = "AB";
	char palabra2a[10] = "1231231";
	char palabra2b[10] = "1231231";
	char *ra, *rb;

	ra = strcat(palabra2a, palabra1);
	printf("%s, %s :: %s\n", palabra1, palabra2a, ra);

	rb = ft_strcat(palabra2b, palabra1);
	printf("%s, %s :: %s\n", palabra1, palabra2b, rb);

	return (0);
}