#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

char  *ft_strchr(char *str, char c);
int   ft_strlen(char const *str);
void  ft_strcpy(char *dst, const char *src);
char  *ft_strdup(const char *src);
char  *ft_strjoin(char *s1, char const *s2);
char  *get_next_line(int fd);

#endif
