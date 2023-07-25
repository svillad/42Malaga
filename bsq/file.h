#ifndef FILE_H
# define FILE_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 2048

char	*ft_read_file(char *file_name);

#endif
