#include <stdlib.h>

char    *ft_strdup(char *src)
{
	int 	len;
	int		i;
	char	*dest;

	len = 0;
	while (src[i] != '\0') {
		len++;
	}
	dest = (char *)malloc((len + 1) * sizeof(char));
	if (dest == NULL) {
		return NULL;
	}
	i = -1;
	while (++i <= len)
		dest[i] = src[i];
	return (dest);
}
