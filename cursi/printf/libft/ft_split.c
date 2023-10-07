/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:53:28 by svilla-d          #+#    #+#             */
/*   Updated: 2023/09/29 08:07:35 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

#define TRUE 1
#define FALSE 0

static int	ft_count_words(char const *s, char c)
{
	size_t	i;
	int		num_words;
	int		new_word;

	i = 0;
	num_words = 0;
	new_word = FALSE;
	while (s[i])
	{
		if (s[i] == c)
			new_word = FALSE;
		else if (!new_word)
		{
			new_word = TRUE;
			num_words++;
		}
		i++;
	}
	return (num_words);
}

static char	*ft_add_word(const char *s, char c)
{
	int		start;
	int		end;

	start = 0;
	while (s[start] && s[start] == c)
		start++;
	end = start;
	while (s[end] && s[end] != c)
		end++;
	return (ft_substr(s, start, end - start));
}

static char	**ft_allocate_memory(const char *s, char c)
{
	int		num_words;

	if (!s)
		return (NULL);
	num_words = ft_count_words(s, c);
	return ((char **)malloc((num_words + 1) * sizeof(char *)));
}

static void	*ft_free_memory(char **result, int i)
{
	while (i > 0)
		free(result[--i]);
	free(result);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		i;

	result = ft_allocate_memory(s, c);
	if (!result)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			result[i] = ft_add_word(s, c);
			if (!result[i])
				return (ft_free_memory(result, i));
			s += ft_strlen(result[i++]);
		}
		else
			s++;
	}
	result[i] = NULL;
	return (result);
}
