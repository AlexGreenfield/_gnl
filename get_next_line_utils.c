/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastrov <acastrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:30:22 by acastrov          #+#    #+#             */
/*   Updated: 2024/10/20 17:09:04 by acastrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	string_size;

	string_size = 0;
	while (s[string_size] != '\0')
		string_size++;
	return (string_size);
}
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;

	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	while (*src && size-- > 1)
		*dst++ = *src++;
	*dst = '\0';
	return (src_len);
}
// Copies a const string on a new string with malloc
char	*ft_strdup(const char *s)
{
	char	*new_string;
	size_t	sl;

	sl = ft_strlen(s) + 1;
	new_string = malloc(sl);
	if (new_string == NULL)
		return (NULL);
	ft_strlcpy(new_string, s, sl);
	return (new_string);
}

char	*ft_strchr(const char *s)
{
	char	*c_find_pointer;

	c_find_pointer = (char *)s;
	while (*c_find_pointer)
	{
		if (*c_find_pointer == '\n')
			return ((char *)c_find_pointer);
		c_find_pointer++;
	}
	return (NULL);
}
char	*ft_strjoin(char *s1, char *s2)
{
	char	*join_string;
	size_t	len_join_string;

	if (!s1 || !s2)
		return (NULL);
	len_join_string = ft_strlen(s1) + ft_strlen(s2) + 1;
	join_string = malloc(len_join_string);
	if (!join_string)
		return (NULL);
	ft_strlcpy(join_string, s1, ft_strlen(s1) + 1);
	ft_strlcpy(join_string + ft_strlen(s1), s2, ft_strlen(s2) + 1);
	free(s1);
	return (join_string);
}
