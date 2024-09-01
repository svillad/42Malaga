#include "get_next_line.h"

char *ft_strchr(char *str, char c) {
  while (*str) {
    if (*str == c)
      return (str);
    str++;
  }
  return (NULL);
}

int ft_strlen(char const *str) {
  int i = 0;
  while (str[i])
    i++;
  return (i);
}

void ft_strcpy(char *dst, const char *src) {
  while (*src)
    *dst++ = *src++;
  *dst = '\0';
}

char *ft_strdup(const char *src) {
  char *dst = malloc(ft_strlen((char *)src) + 1);
  if (!dst)
    return (NULL);
  ft_strcpy(dst, src);
  return (dst);
}

char *ft_strjoin(char *s1, char const *s2) {
  char *join;
  int l1 = ft_strlen(s1);
  int l2 = ft_strlen(s2);
  
  join = malloc(l1 + l2 + 1);
  if (!join)
    return (NULL);
  if (s1) {
    ft_strcpy(join, s1);
    free(s1);
  }
  ft_strcpy(join + l1, s2);
  return (join);
}

char *get_next_line(int fd) {
  static char buf[BUFFER_SIZE + 1];
  char *line;
  char *newline;
  int to_copy;
  int byte_read;

  if (fd < 0 || BUFFER_SIZE <= 0)
    return NULL;
  
  line = ft_strdup(buf);
  if (!line)
    return (NULL);

  while (!(newline = ft_strchr(line, '\n')) &&
         (byte_read = read(fd, buf, BUFFER_SIZE)) > 0) {
    buf[byte_read] = '\0';
    line = ft_strjoin(line, buf);
    if (!line)
      return (NULL);
  }

  if (byte_read < 0 || (byte_read == 0 && ft_strlen(line) == 0)) {
    free(line);
    return (NULL);
  }

  if (newline != NULL) {
    to_copy = newline - line + 1;
    ft_strcpy(buf, newline + 1);
  } else {
    to_copy = ft_strlen(line);
    buf[0] = '\0';
  }

  line[to_copy] = '\0';
  return (line);
}

int main() {
  FILE *file = fopen("test.txt", "r");
  char *line;
  int fd;

  if (!file) {
    perror("Error al abrir el archivo");
    return EXIT_FAILURE;
  }

  fd = fileno(file);

  while ((line = get_next_line(fd)) != NULL) {
    printf("%s", line);
    free(line);
  }

  fclose(file);

  return (EXIT_SUCCESS);
}
