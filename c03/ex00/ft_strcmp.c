#include <stdio.h>
#include <string.h>

int ft_strcmp(const char *s1, const char *s2) {
    unsigned int    i;

    i = 0;
    if (s1 == s2)
        return 0;
    while (*(s1+i) && *(s2+i))
	{
        if (*(s1+i) != *(s2+i))
			break;
		i++;
	}
    return *(s1+i) - *(s2+i);
}

int	main(void)
{
	char palabra1[10] = "123";
	char palabra2[10] = "1230";
	int r;

	r = strcmp(palabra1, palabra2);
	printf("%s, %s :: %d\n", palabra1, palabra2, r);

	r = ft_strcmp(palabra1, palabra2);
	printf("%s, %s :: %d\n", palabra1, palabra2, r);

	return (0);
}