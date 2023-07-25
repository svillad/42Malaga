#include "file.h"

char	*ft_read_file(char *file_name)
{
	int		file;
	char	buffer[BUFFER_SIZE];
	char	*content;
	int		len;
	int		i;

	file = open(file_name, O_RDONLY);
	if (file == -1)
		return (NULL);
	len = read(file, buffer, BUFFER_SIZE);
	if (len == -1)
	{
		close(file);
		return (NULL);
	}
	content = (char *)malloc((len + 1) * sizeof(char));
	if (!content)
		return (NULL);
	i = -1;
	while (++i < len)
		content[i] = buffer[i];
	content[i] = '\0';
	if (close(file) == -1)
		return (NULL);
	return (content);
}
