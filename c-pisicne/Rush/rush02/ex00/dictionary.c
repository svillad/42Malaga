/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxgarci <maxgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 17:17:11 by maxgarci          #+#    #+#             */
/*   Updated: 2023/07/23 22:58:52 by maxgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dictionary.h"

char	*ft_find_number(t_number dictionary[], int num)
{
	int	i;

	i = -1;
	while (dictionary && dictionary[++i].num >= 0)
	{
		if (dictionary[i].num == num)
			return (dictionary[i].name);
	}
	return (NULL);
}

t_number	*ft_process_dict(char *content, int size, int len, t_number *dict)
{
	int	i;
	int	j;
	int	n;

	dict = malloc((size + 1) * sizeof(t_number));
	i = -1;
	n = -1;
	while ((++n < size) && dict)
	{
		while (!(content[++i] >= '0' && content[i] <= '9') && i < len)
			if (!ft_is_space(content[i]))
				return (NULL);
		while (content[i] >= '0' && content[i] <= '9' && i < len)
			dict[n].num = dict[n].num * 10 + content[i++] - '0';
		while ((ft_is_space(content[i]) || content[i] == ':') && i < len)
			i++;
		j = 0;
		while (!ft_is_space(content[i]) && i < len)
			dict[n].name[j++] = content[i++];
		dict[n].name[j] = '\0';
	}
	if (dict && (!dict[n - 1].name[0]))
		return (NULL);
	dict[n].num = -1;
	return (dict);
}

t_number	*ft_read_dictionary(char *file_name)
{
	int			n;
	char		*content;
	t_number	*dictionary;
	int			len;

	dictionary = NULL;
	n = ft_count_lines(file_name);
	if (n < 0)
		return (NULL);
	content = ft_read_file(file_name, &len);
	if (content == NULL)
		return (NULL);
	dictionary = ft_process_dict(content, n, len, dictionary);
	free(content);
	if (!dictionary)
		return (NULL);
	return (dictionary);
}
