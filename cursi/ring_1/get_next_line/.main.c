#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"


int	main(void)
{
	char	*line;
	int		i = 0;
	int		fd1;
	int		fd2;

    printf("Programa get_next_line\n");
	fd1 = open("tests/test1.txt", O_RDONLY);
	// fd2 = open("tests/test2.txt", O_RDONLY);

   i = 0;
	while (i < 10)
	{
        line = get_next_line(fd1);
        printf("line[%d]: %s, %zu\n", i+1, line, ft_strlen(line));
		free(line);

        // line = get_next_line(fd2);
        // printf("line2[%d]: %s, %zu\n", i+1, line, ft_strlen(line));
		i++;
	}
	close(fd1);
	return (0);
}