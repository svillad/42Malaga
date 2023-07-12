#include <stdio.h>
#include <string.h>

unsigned int ft_strlcat(char *dest, char *src, unsigned int size);

unsigned int ft_strlcat(char *dest, char *src, unsigned int size)
{
	unsigned int i, j, dest_len, src_len, total_len;

    i = 0;
    while (*(dest + i) && i < size)
        i++;
    dest_len = i;

    j = 0;
    while (*(src + j) && i < size - 1) {
        dest[i] = src[j];
        i++;
        j++;
    }
    dest[i] = '\0';

    src_len = 0;
    while (src[src_len])
        src_len++;

    total_len = dest_len + src_len;

    while (src[src_len])
        src_len++;

    if (size < dest_len)
        return size + src_len;

    return total_len;
}

int	main(void)
{
	char palabra1[6] = "ABCDE";
	char destino_a[20] = "123";
	char destino_b[20] = "123";
	int ra, rb;
	unsigned int n = 2;

	ra = strlcat(destino_a, palabra1, 3);
	printf("%s, %s :: %d\n", palabra1, destino_a, ra);

	rb = ft_strlcat(destino_b, palabra1, 3);
	printf("%s, %s :: %d\n", palabra1, destino_b, rb);

	return (0);
}