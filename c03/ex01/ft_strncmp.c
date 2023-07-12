#include <stdio.h>
#include <string.h>
int ft_strncmp(char *s1, char *s2, unsigned int n);

int ft_strncmp(char *s1, char *s2, unsigned int n) {
    unsigned int    i;

    if (s1 == s2)
        return 0;
    i = 0;
    while (*(s1+i) && *(s2+i) && i < n - 1)
	{        
        if (*(s1+i) != *(s2+i))
			break;
		i++;
	}
    return *(s1+i) - *(s2+i);
}

int	main(void)
{
	char palabra1[10] = "123457";
	char palabra2[10] = "123456 7";
	int r;

	r = strncmp(palabra1, palabra2, 6);
	printf("%s, %s :: %d\n", palabra1, palabra2, r);

	r = ft_strncmp(palabra1, palabra2, 6);
	printf("%s, %s :: %d\n", palabra1, palabra2, r);

	return (0);
}