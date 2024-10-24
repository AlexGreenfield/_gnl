/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastrov <acastrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:30:18 by acastrov          #+#    #+#             */
/*   Updated: 2024/10/24 21:10:03 by acastrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_read(int fd, char **saved);
char	*ft_free(char **to_free, int flag);
char *ft_split_saved(char **saved);

char	*get_next_line(int fd)
{
	static char	*saved;
	char	*line_return;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!saved || ft_strchr_n(saved) != NULL)
		ft_read(fd, &saved);
	line_return = NULL;
	if (ft_strchr_n(saved) != NULL)
	{
		line_return = ft_split_saved(&saved);
		return (line_return);
	}
	else
	{
		line_return = ft_strdup(saved);
		free (saved);
		saved = NULL;
		return (line_return);
	}
	if (!line_return) // This causes doble free, may need fix later
		return (ft_free(&saved, 2));
	//after read, substring separar linea retorno y el resto de guardar con __stub_sigreturn cada free de estatica con = NULL;
}

static char	*ft_read(int fd, char **saved)
{
	ssize_t	bytes_readed;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	bytes_readed = read(fd, buf, BUFFER_SIZE);
	if (bytes_readed < 0)
		return (ft_free(&buf, 0));
	else if (bytes_readed == 0)
		return (ft_free(&buf, 1));
	buf[BUFFER_SIZE] = '\0';
	*saved = ft_strdup(buf);
	if (!*saved)
		return (ft_free(saved, 0));
	while (bytes_readed > 0 && ft_strchr_n(*saved) == NULL)
	{
		bytes_readed = read(fd, buf, BUFFER_SIZE);
		if (bytes_readed < 0)
			return (ft_free(&buf, 0));
		*saved = ft_strjoin(*saved, buf);
		if (!saved)
			return (ft_free(saved, 2));
	}
	free (buf);
	return (*saved);
}
char *ft_split_saved(char **saved)
{
	size_t	ptr_diff;
	char	*next_n;
	char	*temp;
	char	*line_return;

	next_n = ft_strchr_n(*saved);
	//if (next_n != NULL)
	//{
		ptr_diff = next_n - *saved; // We calculate the size to be copied
		line_return = ft_substr(*saved, 0, ptr_diff + 1); // We copy to new pointer
		if (!line_return)
			return (ft_free(saved, 2));
		temp = ft_strdup(next_n + 1);
		free (*saved);
		*saved = temp;
		if (!*saved)
			return (ft_free(saved, 2));
	//}
	/*else
	{
		line_return = ft_strdup(*saved);
		if (!line_return)
			return (ft_free(saved, 2));
		free(*saved);
		*saved = NULL;
	}*/
	return (line_return);
}

char	*ft_free(char **to_free, int flag)
{
	free(*to_free);
	if (flag == 1)
		return (ft_strdup(""));
	if (flag == 2)
		*to_free = NULL;
	return (NULL);
}
