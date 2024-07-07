/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 12:58:36 by svilla-d          #+#    #+#             */
/*   Updated: 2024/05/20 13:17:15 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/**
 * @brief Checks if a character is an alphabetical letter
 *        (uppercase or lowercase).
 * @param c (int): The character to check.
 * @return The function returns an integer value:
 *         - A non-zero value if `c` is a letter.
 *         - 0 otherwise. \n
 * @ref <ctype.h>
 * @author Sebastian Villa
 */
int					ft_isalpha(int c);
/**
 * @brief Checks if a character is a decimal digit.
 * @param c (int): The character to check.
 * @return The function returns an integer value:
 *         - A non-zero value if `c` is a decimal digit (0-9).
 *         - 0 otherwise. \n
 * @ref <ctype.h>
 * @author Sebastian Villa
 */
int					ft_isdigit(int c);
/**
 * @brief Checks if a character is an alphanumeric character (letter or digit).
 * @param c (int): The character to check.
 * @return The function returns an integer value:
 *         - A non-zero value if `c` is an alphanumeric character.
 *         - 0 otherwise. \n
 * @ref <ctype.h>
 * @author Sebastian Villa
 */
int					ft_isalnum(int c);
/**
 * @brief Checks if an integer value is within the ASCII range (0-127).
 * @param c (int): The integer value to check.
 * @return The function returns an integer value:
 *         - A non-zero value if `c` is within the ASCII range (0-127).
 *         - 0 otherwise. \n
 * @ref <ctype.h>
 * @author Sebastian Villa
 */
int					ft_isascii(int c);
/**
 * @brief Checks if a character is printable.
 * @param c (int): The character to check.
 * @return The function returns an integer value:
 *         - A non-zero value if `c` is a printable character (32-126).
 *         - 0 otherwise. \n
 * @ref <ctype.h>
 * @author Sebastian Villa
 */
int					ft_isprint(int c);
/**
 * @brief Checks if a string consists only of whitespace characters.
 * This function checks if a string consists only of whitespace characters,
 * including spaces, tabs, newlines, and carriage returns.
 * @param str The string to be checked.
 * @return 1 if the string consists only of whitespace characters, otherwise 0.
 */
int					ft_is_str_empty(const char *str);
/**
 * @brief Converts a lowercase character to uppercase.
 * @param c (int): The character to convert to uppercase.
 * @return The function returns the character converted to uppercase if `c` is a
 *         lowercase letter. If `c` is not a lowercase letter, it returns the
 *         same character unchanged.
 * @ref <ctype.h>
 * @author Sebastian Villa
 */
int					ft_toupper(int c);
/**
 * @brief Converts an uppercase character to lowercase.
 * @param c (int): The character to convert to lowercase.
 * @return The function returns the character converted to lowercase if `c` is an
 *         uppercase letter. If `c` is not an uppercase letter, it returns the
 *         same character unchanged.
 * @ref <ctype.h>
 * @author Sebastian Villa
 */
int					ft_tolower(int c);
/**
 * @brief Calculates the length of a string of characters.
 * @param str (const char *): The string of characters from which to calculate
 *        the length.
 * @return The function returns an integer value representing the length of the
 *        `str` string. \n
 * @ref <string.h>
 * @author Sebastian Villa
 */
size_t				ft_strlen(const char *str);
/**
 * @brief Searches for the first occurrence of a character in a string of
 *        characters.
 * @param str (const char *): The string in which the search will be performed.
 * @param c (int): The character to search for in the string.
 * @return The function returns a pointer to the first character `c` found in
 *         `str`, or a null pointer if `c` is not found in the string. \n
 * @ref <string.h>
 * @author Sebastian Villa
 */
char				*ft_strchr(const char *str, int c);
/**
 * @brief Searches for the last occurrence of a character in a string of
 *        characters.
 * @param str (const char *): The string in which the search will be performed.
 * @param c (int): The character to search for in the string.
 * @return The function returns a pointer to the last character `c` found in
 *         `str`, or a null pointer if `c` is not found in the string. \n
 * @ref <string.h>
 * @author Sebastian Villa
 */
char				*ft_strrchr(const char *str, int c);
/**
 * @brief Compares two strings of characters limited by length.
 * @param s1 (const char *): The first string of characters to compare.
 * @param s2 (const char *): The second string of characters to compare.
 * @param n (size_t): The maximum number of characters to compare.
 * @return The function returns an integer value indicating the relationship
 *         between the strings:
 *         - A value less than zero if `s1` is less than `s2`.
 *         - Zero if `s1` is equal to `s2`.
 *         - A value greater than zero if `s1` is greater than `s2`. \n
 * @ref <string.h>
 * @author Sebastian Villa
 */
int					ft_strncmp(const char *s1, const char *s2, size_t n);
/**
 * @brief Compares two strings of characters.
 * @param s1 (const char *): The first string of characters to compare.
 * @param s2 (const char *): The second string of characters to compare.
 * @return The function returns an integer value indicating the relationship
 *         between the strings:
 *         - A value less than zero if `s1` is less than `s2`.
 *         - Zero if `s1` is equal to `s2`.
 *         - A value greater than zero if `s1` is greater than `s2`. \n
 * @ref <string.h>
 * @author Sebastian Villa
 */
int					ft_strcmp(const char *s1, const char *s2);
/**
 * @brief Searches for the first occurrence of a byte in a memory region.
 * @param ptr (const void *): A pointer to the memory region in which the search
 *        will be performed.
 * @param value (int): The byte to search for in the memory region.
 * @param num (size_t): The number of bytes to search.
 * @return The function returns a pointer to the first byte with the `value`
 *         value found in the memory region pointed to by `ptr`,or a null pointer
 *         if `value` is not found in the region. \n
 * @ref <string.h>
 * @author Sebastian Villa
 */
void				*ft_memchr(const void *ptr, int value, size_t n);
/**
 * @brief Compares two memory regions byte by byte.
 * @param p1 (const void *): A pointer to the first memory region.
 * @param p2 (const void *): A pointer to the second memory region.
 * @param num (size_t): The number of bytes to compare.
 * @return The function returns an integer value:
 *         - Less than 0 if the first region is less than the second.
 *         - 0 if both regions are equal.
 *         - Greater than 0 if the first region is greater than the second. \n
 * @ref <string.h>
 * @author Sebastian Villa
 */
int					ft_memcmp(const void *s1, const void *s2, size_t n);
/**
 * @brief Finds the first occurrence of a substring in another string, with a
 *        limit on the search.
 * @param s1 (const char *): The string in which the search will be performed.
 * @param s2 (const char *): The substring to search for in `s1`.
 * @param n (size_t): The maximum number of characters to examine in `s1`.
 * @return The function returns a pointer to the first occurrence of `s2` in `s1`
 *         within the first `n` characters of `s1`,
	or a null pointer if `s2` is not
 *         found in the search region.
 * @ref <string.h>
 * @author Sebastian Villa
 */
char				*ft_strnstr(const char *s1, const char *s2, size_t n);
/**
 * @brief Converts a string of characters to its integer equivalent.
 * @param str (const char *): The string of characters to convert.
 * @return The function returns the integer value equivalent to the string.
 *         If the conversion cannot be performed, it returns 0. If a character
 *         that is not a digit or a sign is encountered, the conversion stops,
 *         and the value obtained up to that point is returned.
 * @ref <stdlib.h>
 * @author Sebastian Villa
 */
int					ft_atoi(const char *str);
/**
 * @brief Fills a block of memory with a specific value.
 * @param ptr (void *): A pointer to the memory block to be filled.
 * @param value (int): The value with which the memory block will be filled.
 * @param n (size_t): The number of bytes to fill with the specified value.
 * @return  The function returns a pointer to the ptr memory block after filling
 * 			it.
 * @ref <string.h>
 * @author Sebastian Villa
 */
void				*ft_memset(void *ptr, int value, size_t n);
/**
 * @brief Sets all bytes of a memory block to zero (0).
 * @param ptr (void *): A pointer to the memory block to be zeroed.
 * @param n (size_t): The number of bytes to set to zero.
 * @return No return value.
 * @ref <strings.h>
 * @author Sebastian Villa
 */
void				ft_bzero(void *ptr, size_t n);
/**

 * @brief Copies a memory block from a source location to a destination location.
 * @param dest (void *): A pointer to the destination location.
 * @param src (const void *): A pointer to the source location.
 * @param n (size_t): The number of bytes to copy.
 * @return A pointer to the destination location.
 * @ref <string.h>
 * @author Sebastian Villa
 */
void				*ft_memcpy(void *dest, const void *src, size_t n);
/**

 * @brief Copies a memory block from a source location to a destination location,
 *        allowing the blocks to overlap.
 * @param dest (void *): A pointer to the destination location.
 * @param src (const void *): A pointer to the source location.
 * @param n (size_t): The number of bytes to copy.
 * @return A pointer to the destination location.
 * @ref <string.h>
 * @author Sebastian Villa
 */
void				*ft_memmove(void *dest, const void *src, size_t n);
/**
 * @brief Copies a source string into a destination string with a maximum size,
 *        ensuring that the destination string is properly terminated with the
 *        null character.
 * @param dest (char *): A pointer to the destination string.
 * @param src (const char *): A pointer to the source string.
 * @param n (size_t): The maximum size of the destination string, including the
 *        null character.
 * @return The total number of characters that were attempted to be copied (the
 *         length of src). If the destination string did not have enough space,
 *         the resulting value will be greater than or equal to n.
 * @ref <string.h>
 * @author Sebastian Villa
 */
size_t				ft_strlcpy(char *dest, const char *src, size_t n);
/**

 * @brief Concatenates two strings of characters safely into a destination string
 *        ensuring that the destination string is properly terminated with the
 *        null character.
 * @param dest (char *): A pointer to the destination string.
 * @param src (const char *): A pointer to the source string.
 * @param n (size_t): The maximum size of the destination string, including the
 *        null character.
 * @return The total number of characters that were attempted to be copied (the
 *         length of src plus the length of dest). If the destination string did
 *         not have enough space, the resulting value will be greater than or
 *         equal to n.
 * @ref <string.h>
 * @author Sebastian Villa
 */
size_t				ft_strlcat(char *dest, const char *src, size_t n);
/**
 * @brief Reserves a block of memory for an array of elements, initializing all
 *        bytes to 0.
 * @param num (size_t): The number of elements to allocate space for.
 * @param size (size_t): The size in bytes of each element.
 * @return A pointer to the allocated memory block, or NULL if the allocation
 *         fails.
 * @ref <stdlib.h>
 * @author Sebastian Villa
 */
void				*ft_calloc(size_t count, size_t size);
/**
 * @brief Duplicates a string of characters to a new memory location.
 * @param src (const char *): The string of characters to duplicate.
 * @return A pointer to the new duplicated string, or NULL if memory allocation
 *         fails.
 * @ref <string.h>
 * @author Sebastian Villa
 */
char				*ft_strdup(const char *src);
/**
 * @brief Duplicates a string of characters to a new memory location.
 * @param src (const char *): The string of characters to duplicate.
 * @param n (int):allocate memory size.
 * @return A pointer to the new duplicated string, or NULL if memory allocation
 *         fails.
 * @ref <string.h>
 * @author Sebastian Villa
 */
char				*ft_strndup(const char *src, int n);
/**
 * @brief Creates a new string of characters (substring) from the given string.
 * @param s The original string.
 * @param start The starting index of the substring.
 * @param len The maximum length of the substring.
 * @return The function returns a substring of the original string. If a memory
 *         allocation error occurs or if `start` is out of range for the string,
 *         it returns NULL.
 * @author Sebastian Villa
 */
char				*ft_substr(char const *s, unsigned int start, size_t len);
/**
 * @brief Concatenates two strings of characters.
 * @param s1 The first string.
 * @param s2 The second string to concatenate to the end of the first.
 * @return The function returns a new string of characters that is the result
 *         of the concatenation of `s1` and `s2`. If a memory allocation error
 *         occurs or if `s1` or `s2` are NULL, it returns NULL.
 * @author Sebastian Villa
 */
char				*ft_strjoin(char const *s1, char const *s2);
/**
 * @brief Removes specific characters from the beginning and end of a string of
 *        characters.
 * @param s1 The string of characters from which characters will be removed.
 * @param set The string of characters containing the characters to be removed.
 * @return It returns a new string of characters that is a copy of `s1` but
 *         without the characters specified in set at the beginning and end. In
 *         case of an error, or if `s1` or set is NULL, it returns NULL.
 * @author Sebastian Villa
 */
char				*ft_strtrim(char const *s1, char const *set);
/**
 * @brief Splits a string into substrings based on a delimiter character.
 * @param s The string to be split.
 * @param c The delimiter character to be used for splitting the string.
 * @return It returns a pointer to an array of strings (a string array)
 *         terminated by NULL, representing the resulting substrings. In case of
 *         an error or if `s` is NULL, it returns NULL.
 * @author Sebastian Villa
 */
char				**ft_split(char const *s, char c);
/**
 * @brief Counts the number of words in a string delimited by a specified
 *        character.
 * @param s A pointer to the string to be analyzed.
 * @param c The delimiter character used to separate words.
 * @return The number of words found in the string.
 */
int					ft_count_words(char const *s, char c);
/**
 * @brief Converts an integer to a string representation.
 * @param n The integer to be converted.
 * @return It returns a string representation of the integer `n`. The string is
 *         dynamically allocated and must be freed by the user when it is no
 *         longer needed.
 * @note In case of an error or if memory allocation fails, it returns NULL.
 * @ref <stdlib.h>
 * @author Sebastian Villa
 */
char				*ft_itoa(int n);
/**
 * @brief Applies a function to each character in a string.
 * @param s The string to be modified.
 * @param f The function to apply to each character.
 * @return It returns a new string created by applying the function `f` to each
 *         character in `s`. In case of an error, or if `s` or `f` is NULL, it
 *         returns NULL.
 * @note The user is responsible for freeing the memory allocated for the
 *       resulting string using the `free()` function.
 * @author Sebastian Villa
 */
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
/**
 * @brief Applies a function to each character in a given string.
 * @param s The string to which the function will be applied.

 * @param f The function to apply to each character.It should take two parameters
 *        - An unsigned integer representing the index of the character.
 *       
	- A ptr to a character representing the current character in the string
 * @return No return value.
 * @author Sebastian Villa
 */
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
/**
 * @brief Writes a character to the specified file descriptor.
 * @param c The character to write to the file.
 * @param fd The file descriptor where the character will be written.
 *        - 1 (stdout): standard output (the screen)
 *        - 2 (stderr): represents standard error output.
 * @return The number of characters written.
 * @author Sebastian Villa
 */
int					ft_putchar_fd(char c, int fd);
/**
 * @brief Writes a string of characters to the specified file descriptor.
 * @param s The string of characters to write to the file.
 * @param fd The file descriptor where the string will be written.
 *        - 1 (stdout): standard output (the screen)
 *        - 2 (stderr): represents standard error output.
 * @return The number of characters written.
 * @author Sebastian Villa
 */
int					ft_putstr_fd(char *s, int fd);
/**
 * @brief Writes a string of characters followed by a newline to the specified
 *        file descriptor.
 * @param s The string of characters to write to the file.
 * @param fd The file descriptor where the string followed by a newline will be
 *        written.
 *        - 1 (stdout): standard output (the screen)
 *        - 2 (stderr): represents standard error output.
 * @return No return value.
 * @author Sebastian Villa
 */
void				ft_putendl_fd(char *s, int fd);
/**
 * @brief Writes an integer to a specified file descriptor.
 * @param n (int): The integer to write to the file descriptor.
 * @param fd (int): The file descriptor where the number will be written.
 *        - 1 (stdout): standard output (the screen)
 *        - 2 (stderr): represents standard error output.
 * @return No return value.
 * @author Sebastian Villa
 */
void				ft_putnbr_fd(int n, int fd);
/**
 * @brief Creates a new list node with the specified content.
 * @param content (void *): The content to assign to the new node.
 * @return A pointer to the new list node if memory allocation was successful.
 *         NULL if memory allocation failed.
 * @author Sebastian Villa
 */
t_list				*ft_lstnew(void *content);
/**
 * @brief Adds a new node to the beginning of a linked list.
 * @param lst (t_list **): A pointer to a pointer to the first node of the list.
 * @param new (t_list *): The new node to add to the beginning of the list.
 * @return Nothing.
 * @author Sebastian Villa
 */
void				ft_lstadd_front(t_list **lst, t_list *new);
/**
 * @brief Calculates the size (number of nodes) of a linked list.
 * @param lst (t_list *): A pointer to the first node of the list.
 * @return The number of nodes in the list.
 * @note This function traverses the linked list from the given node and counts
 *       the number of nodes in the list, returning this value as the result.
 * @author Sebastian Villa
 */
int					ft_lstsize(t_list *lst);
/**
 * @brief Returns a pointer to the last node of a linked list.
 * @param lst (t_list *): A pointer to the first node of the list.
 * @return A pointer to the last node of the list. If the list is empty.
 *         it returns NULL.
 * @note This function traverses the linked list from the given node until it
 *       finds the last node and returns a pointer to that last node.
 * @author Sebastian Villa
 */
t_list				*ft_lstlast(t_list *lst);
/**
 * @brief Adds a new node to the end of a linked list.
 * @param lst (t_list **): A pointer to a pointer to the first node of the list.
 * @param new_node (t_list *): A pointer to the new node to add to the end
 *        of the list.
 * @return Nothing.
 * @author Sebastian Villa
 */
void				ft_lstadd_back(t_list **lst, t_list *new_node);
/**
 * @brief Deletes a node from a linked list and frees its memory.
 * @param lst (t_list *): A pointer to the node to be deleted.
 * @param del (void (*)(void*)): A pointer to a function used to free
 *        the memory occupied by the content of the node.
 * @return Nothing.
 * @author Sebastian Villa
 */
void				ft_lstdelone(t_list *lst, void (*del)(void *));
/**
 * @brief Deletes and frees the memory of all nodes in a linked list and their
 *        content.
 * @param lst (t_list **): A pointer to a pointer to the list to be deleted.
 * @param del (void (*)(void*)): A pointer to a function used to free the memory
 *        occupied by the content of each node.
 * @return Nothing.
 * @author Sebastian Villa
 */
void				ft_lstclear(t_list **lst, void (*del)(void *));
/**
 * @brief Iterates through a linked list and applies a function to each element.
 * @param lst (t_list *): A pointer to the first element of the list.
 * @param f (void (*)(void *)): A pointer to a function that is applied to each
 *        element of the list.
 * @return Nothing.
 * @author Sebastian Villa
 */
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
/**
 * @brief Creates a new list by applying a function to each element of the
 *        original list.
 * @param lst (t_list *): A pointer to the first element of the original list.
 * @param f (void *(*)(void *)): A pointer to a function that is applied to each
 *        element of the original list.
 * @param del (void (*)(void *)): A pointer to a function used to delete the
 *        content of a node if necessary.
 * @author Sebastian Villa
 */

#endif
