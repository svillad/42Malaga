/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 12:58:36 by svilla-d          #+#    #+#             */
/*   Updated: 2023/09/30 15:58:45 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/**
 * @brief Comprueba si un carácter es una letra del alfabeto 
 *        (mayúscula o minúscula).
 * @param c (int): El carácter que se va a comprobar.
 * @return La función devuelve un valor entero:
 *         - Un valor distinto de cero si `c` es una letra.
 *         - 0 en caso contrario. \n
 * @ref <ctype.h>
 * @author Sebastian Villa
 */
int		ft_isalpha(int c);
/**
 * @brief Comprueba si un carácter es un dígito decimal.
 * @param c (int): El carácter que se va a comprobar.
 * @return La función devuelve un valor entero:
 *         - Un valor distinto de cero si `c` es un dígito decimal (0-9).
 *         - 0 en caso contrario. \n
 * @ref <ctype.h>
 * @author Sebastian Villa
 */
int		ft_isdigit(int c);
/**
 * @brief Comprueba si un carácter es un carácter alfanumérico (letra o dígito).
 * @param c (int): El carácter que se va a comprobar.
 * @return La función devuelve un valor entero:
 *         - Un valor distinto de cero si `c` es un carácter alfanumérico.
 *         - 0 en caso contrario. \n
 * @ref <ctype.h>
 * @author Sebastian Villa
 */
int		ft_isalnum(int c);
/**
 * @brief Comprueba si un valor entero está dentro del rango ASCII (0-127).
 * @param c (int): El valor entero que se va a comprobar.
 * @return La función devuelve un valor entero:
 *         - Un valor distinto de cero si `c` está en el rango ASCII (0-127).
 *         - 0 en caso contrario. \n
 * @ref <ctype.h>
 * @author Sebastian Villa
 */
int		ft_isascii(int c);
/**
 * @brief Comprueba si un carácter es imprimible.
 * @param c (int): El carácter que se va a comprobar.
 * @return La función devuelve un valor entero:
 *         - Un valor distinto de cero si `c` es un carácter imprimible (32-126).
 *         - 0 en caso contrario. \n
 * @ref <ctype.h>
 * @author Sebastian Villa
 */
int		ft_isprint(int c);
/**
 * @brief Convierte un carácter en minúscula a mayúscula.
 * @param c (int): El carácter que se va a convertir a mayúscula.
 * @return La función devuelve el carácter convertido a mayúscula si `c` es una
 *         minúscula.
 *         Si `c` no es una minúscula, se devuelve el mismo carácter sin cambios.
 * @ref <ctype.h>
 * @author Sebastian Villa
 */
int		ft_toupper(int c);
/**
 * @brief Convierte un carácter en mayúscula a minúscula.
 * @param c (int): El carácter que se va a convertir a minúscula.
 * @return La función devuelve el carácter convertido a minúscula si `c` es una
 *         mayúscula.
 *         Si `c` no es una mayúscula, se devuelve el mismo carácter sin cambios.
 * @ref <ctype.h>
 * @author Sebastian Villa
 */
int		ft_tolower(int c);
/**
 * @brief Calcula la longitud de una cadena de caracteres.
 * @param str (const char *): La cadena de caracteres de la que se va a calcular
 *        la longitud.
 * @return La función devuelve un valor entero que representa la longitud de la
 *        cadena `str`. \n
 * @ref <string.h>
 * @author Sebastian Villa
 */
size_t	ft_strlen(const char *str);
/**
 * @brief Busca la primera aparición de un carácter en una cadena de caracteres.
 * @param str (const char *): La cadena en la que se realizará la búsqueda.
 * @param c (int): El carácter que se busca en la cadena.
 * @return La función devuelve un puntero al primer carácter `c` encontrado
 *         en `str`, o un puntero nulo si `c` no se encuentra en la cadena. \n
 * @ref <string.h>
 * @author Sebastian Villa
 */
char	*ft_strchr(const char *str, int c);
/**
 * @brief Busca la última aparición de un carácter en una cadena de caracteres.
 * @param str (const char *): La cadena en la que se realizará la búsqueda.
 * @param c (int): El carácter que se busca en la cadena.
 * @return La función devuelve un puntero al último carácter `c` encontrado
 *         en `str`, o un puntero nulo si `c` no se encuentra en la cadena. \n
 * @ref <string.h>
 * @author Sebastian Villa
 */
char	*ft_strrchr(const char *str, int c);
/**
 * @brief Compara dos cadenas de caracteres limitadas por longitud.
 * @param s1 (const char *): La primera cadena de caracteres a comparar.
 * @param s2 (const char *): La segunda cadena de caracteres a comparar.
 * @param n (size_t): El número máximo de caracteres a comparar.
 * @return La función devuelve un valor entero que indica la relación entre las
 *         cadenas:
 *         - Un valor menor que cero si `s1` es menor que `s2`.
 *         - Cero si `s1` es igual a `s2`.
 *         - Un valor mayor que cero si `s1` es mayor que `s2`. \n
 * @ref <string.h>
 * @author Sebastian Villa
 */
int		ft_strncmp(const char *s1, const char *s2, size_t n);
/**
 * @brief Busca la primera aparición de un byte en una región de memoria.
 * @param ptr (const void *): Un puntero a la región de memoria en la que se
 *        realizará la búsqueda.
 * @param value (int): El byte que se busca en la región de memoria.
 * @param num (size_t): El número de bytes a buscar.
 * @return La función devuelve un puntero al primer byte con el valor `value`
 *         encontrado en la región de memoria apuntada por `ptr`,
 *         o un puntero nulo si `value` no se encuentra en la región. \n
 * @ref <string.h>
 * @author Sebastian Villa
 */
void	*ft_memchr(const void *ptr, int value, size_t n);
/**
 * @brief Compara dos regiones de memoria byte a byte.
 * @param p1 (const void *): Un puntero a la primera región de memoria.
 * @param p2 (const void *): Un puntero a la segunda región de memoria.
 * @param num (size_t): El número de bytes que se van a comparar.
 * @return La función devuelve un valor entero:
 *         - Menor que 0 si la primera región es menor que la segunda.
 *         - 0 si ambas regiones son iguales.
 *         - Mayor que 0 si la primera región es mayor que la segunda.
 * @ref <string.h>
 * @author Sebastian Villa
 */
int		ft_memcmp(const void *s1, const void *s2, size_t n);
/**
 * @brief Encuentra la primera aparición de una subcadena en otra, con un límite
 *        en la búsqueda.
 * @param s1 (const char *): La cadena en la que se realizará la búsqueda.
 * @param s2 (const char *): La subcadena que se busca en `s1`.
 * @param n (size_t): El número máximo de caracteres a examinar en `s1`.
 * @return La función devuelve un puntero a la primera aparición de `s2` en
 *         `s1`, dentro de los primeros `n` caracteres de `s1`, o
 *         un puntero nulo si `s2` no se encuentra en la región de búsqueda.
 * @ref <string.h>
 * @author Sebastian Villa
 */
char	*ft_strnstr(const char *s1, const char *s2, size_t n);
/**
 * @brief Convierte una cadena de caracteres en su equivalente entero.
 * @param str (const char *): La cadena de caracteres que se va a convertir.
 * @return La función devuelve el valor entero equivalente a la cadena. Si no se
 *         puede realizar la conversión, devuelve 0. Si se encuentra un carácter
 *         que no es un dígito o un signo, la conversión se detiene y se
 *         devuelve el valor obtenido hasta ese punto.
 * @ref <stdlib.h>
 * @author Sebastian Villa
 */
int		ft_atoi(const char *str);
/**
 * @brief Llena un bloque de memoria con un valor específico.
 * @param ptr (void *): Un puntero al bloque de memoria que se llenará.
 * @param value (int): El valor con el que se llenará el bloque de memoria.
 * @param n (size_t): El número de bytes que se llenarán con el valor 
 *        especificado.
 * @return La función devuelve un puntero al bloque de memoria 'ptr' después
 *         de llenarlo.
 * @ref <string.h>
 * @author Sebastian Villa
 */
void	*ft_memset(void *ptr, int value, size_t n);
/**
 * @brief Establece todos los bytes de un bloque de memoria en cero (0).
 * @param ptr (void *): Un puntero al bloque de memoria que se llenará de ceros.
 * @param n (size_t): El número de bytes que se establecerán en cero.
 * @return No hay valor de retorno.
 * @ref <strings.h>
 * @author Sebastian Villa
 */
void	ft_bzero(void *ptr, size_t n);
/**
 * @brief Copia un bloque de memoria desde una ubicación de origen a una
 *        de destino.
 * @param dest (void *): Un puntero a la ubicación de destino.
 * @param src (const void *): Un puntero a la ubicación de origen.
 * @param n (size_t): El número de bytes que se copiarán.
 * @return Un puntero a la ubicación de destino.
 * @ref <string.h>
 * @author Sebastian Villa
 */
void	*ft_memcpy(void *dest, const void *src, size_t n);
/**
 * @brief Copia un bloque de memoria desde una ubicación de origen a una
 *        de destino, permitiendo que los bloques se superpongan.
 * @param dest (void *): Un puntero a la ubicación de destino.
 * @param src (const void *): Un puntero a la ubicación de origen.
 * @param n (size_t): El número de bytes que se copiarán.
 * @return Un puntero a la ubicación de destino.
 * @ref <string.h>
 * @author Sebastian Villa
 */
void	*ft_memmove(void *dest, const void *src, size_t n);
/**
 * @brief Copia una cadena de origen en una cadena de destino con un tamaño
 *        máximo, garantizando que la cadena de destino esté terminada
 *        correctamente con el carácter nulo.
 * @param dest (char *): Un puntero a la cadena de destino.
 * @param src (const char *): Un puntero a la cadena de origen.
 * @param n (size_t): El tamaño máximo de la cadena de destino, incluyendo el
 *        carácter nulo.
 * @return El número total de caracteres que se intentaron copiar (la longitud
 *         de src). Si la cadena de destino no tenía suficiente espacio, el
 *         valor resultante será mayor o igual a n.
 * @ref <string.h>
 * @author Sebastian Villa
 */
size_t	ft_strlcpy(char *dest, const char *src, size_t n);
/**
 * @brief Concatena dos cadenas de caracteres de manera segura en una cadena
 *        de destino, garantizando que la cadena de destino esté terminada
 *        correctamente con el carácter nulo.
 * @param dest (char *): Un puntero a la cadena de destino.
 * @param src (const char *): Un puntero a la cadena de origen.
 * @param n (size_t): El tamaño máximo de la cadena de destino, incluyendo
 *        el carácter nulo.
 * @return El número total de caracteres que se intentaron copiar (la longitud
 *         de src más la longitud de dest). Si la cadena de destino no tenía
 *         suficiente espacio, el valor resultante será mayor o igual a n.
 * @ref <string.h>
 * @author Sebastian Villa
 */
size_t	ft_strlcat(char *dest, const char *src, size_t n);
/**
 * @brief Reserva un bloque de memoria para un arreglo de elementos,
 *        inicializando todos los bytes en 0.
 * @param num (size_t): La cantidad de elementos que se reservarán.
 * @param size (size_t): El tamaño en bytes de cada elemento.
 * @return Un puntero al bloque de memoria reservado, o NULL si falla la
 *         asignación.
 * @ref <stdlib.h>
 * @author Sebastian Villa
 */
void	*ft_calloc(size_t count, size_t size);
/**
 * @brief Duplica una cadena de caracteres en una nueva ubicación de memoria.
 * @param src (const char *): La cadena de caracteres que se duplicará.
 * @return Un puntero a la nueva cadena duplicada, o NULL si falla la asignación
 *         de memoria.
 * @ref <string.h>
 * @author Sebastian Villa
 */
char	*ft_strdup(const char *src);
/**
 * @brief Crea una nueva cadena de caracteres (subcadena) de la cadena dada.
 * @param s Cadena de caracteres de origen.
 * @param start Índice de inicio de la subcadena.
 * @param len Longitud máxima de la subcadena.
 * @return La función devuelve una subcadena de la cadena de origen.
 *         Si se produce un error en la asignación de memoria o si `start`
 *         está fuera del rango de la cadena, se devuelve NULL.
 * @author Sebastian Villa
 */
char	*ft_substr(char const *s, unsigned int start, size_t len);
/**
 * @brief Concatena dos cadenas de caracteres.
 * @param s1 Primera cadena de caracteres.
 * @param s2 Segunda cadena de caracteres a concatenar al final de la primera.
 * @return La función devuelve una nueva cadena de caracteres que es el
 *         resultado de la concatenación de `s1` y `s2`. Si se produce un error
 *         en la asignación de memoria o si `s1` o `s2` son NULL, se devuelve
 *         NULL.
 * @ref ft_strlen, ft_strdup, free
 * @author Tu nombre (o el autor original, si corresponde)
 */
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new_node);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
