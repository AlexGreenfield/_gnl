/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastrov <acastrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:30:22 by acastrov          #+#    #+#             */
/*   Updated: 2024/10/18 17:46:33 by acastrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

#include "get_next_line.h"

char	*ft_first_read(const char *buf) // We need to read const variable char here
{
	char	*first_line;
	int		i;

	i = 0;
	first_line = malloc (BUFFER_SIZE + 1 * sizeof(char)); // Not buffersize, but buf_len
	if (!first_line)
		return (NULL);
	while (buf[i] != '\0') // Call to ft_strlen?
	{
		first_line[i] = buf[i];
		i++;
	}
	first_line[i] = '\0';
	return (first_line);
}

// Cats line with buffer
char	*ft_malloc_cat(char *old_line, const char *buf) // Liberar lineeeee
{
	int		line_len;
	int		buf_len;
	int		i;
	char	*line_cat;

	line_len = 0;
	buf_len = 0;
	i = 0;
	while (old_line [line_len] != '\0') // Maybe we should create ft_strlen
		line_len++;
	while (buf [buf_len] != '\0')
		buf_len++;
	line_cat = malloc(line_len + buf_len + 1 * sizeof(char));
	if (!line_cat)
		return (NULL);
	while (i < line_len)
	{
		line_cat[i] = old_line[i];
		i++;
	}
	free (old_line);
	while (i < line_len + buf_len)
		line_cat[i++] = *buf++;
	line_cat[i] = '\0';
	return (line_cat);
}

// Finds the next iteration of n in line, NULL if not finded
char	*ft_next_n(char *line)
{
	char	*n_find;

	n_find = line;
	while (*n_find)
	{
		if (*n_find == '\n')
			return (n_find);
		n_find++;
	}
	return (NULL);
}
