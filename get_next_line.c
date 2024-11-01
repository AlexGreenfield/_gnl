/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastrov <acastrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:30:18 by acastrov          #+#    #+#             */
/*   Updated: 2024/11/01 19:42:22 by acastrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	ft_read(int fd, char **saved);
ssize_t	ft_keep_reading(int fd, char **saved);
char	*ft_split_saved(char **saved);
char	*get_return_line(char **saved);
void	ft_free_fill_saved(char **saved, char *fill);

// Reads and saves until n, returns line and stores for future calls
char	*get_next_line(int fd)
{
	static char	*saved;
	char		*line_return;
	ssize_t		bytes_readed;

	bytes_readed = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!saved)
		bytes_readed = ft_read(fd, &saved);
	while (saved != NULL && ft_strchr_n(saved) == NULL)
	{
		bytes_readed = ft_keep_reading(fd, &saved);
		if (bytes_readed <= 0)
			break ;
	}
	if (bytes_readed < 0)
	{
		ft_free_fill_saved(&saved, NULL);
		return (NULL);
	}
	line_return = get_return_line(&saved);
	return (line_return);
}

// Reads n bytes in buffer and stores it in saved
ssize_t	ft_read(int fd, char **saved)
{
	ssize_t	bytes_readed;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (-1);
	bytes_readed = read(fd, buf, BUFFER_SIZE);
	if (bytes_readed <= 0)
	{
		free(buf);
		return (bytes_readed);
	}
	buf[bytes_readed] = '\0';
	if (*saved)
		ft_free_fill_saved (saved, NULL);
	*saved = ft_strdup(buf);
	free (buf);
	if (!*saved)
	{
		ft_free_fill_saved (saved, NULL);
		return (-1);
	}
	return (bytes_readed);
}

ssize_t	ft_keep_reading(int fd, char **saved)
{
	char	*temp;
	char	*join;
	ssize_t	bytes_readed;

	temp = ft_strdup(*saved);
	if (!temp)
	{
		free (temp);
		return (-1);
	}
	ft_free_fill_saved (saved, NULL);
	bytes_readed = ft_read(fd, saved);
	if (bytes_readed <= 0)
	{
		*saved = temp;
		return (bytes_readed);
	}
	join = ft_strjoin(temp, *saved);
	free (temp);
	free (*saved);
	*saved = join;
	if (!*saved)
		return (-1);
	return (bytes_readed);
}

// Divides saved in two after and before n
char	*ft_split_saved(char **saved)
{
	char	*next_n;
	char	*line_return;
	char	*temp;

	next_n = ft_strchr_n(*saved);
	line_return = ft_substr(*saved, 0, next_n - *saved + 1);
	if (!line_return)
	{
		ft_free_fill_saved (saved, NULL);
		return (NULL);
	}
	if (*next_n && *(next_n + 1))
	{
		temp = ft_strdup(next_n + 1);
		ft_free_fill_saved(saved, temp);
		if (!*saved)
		{
			free (line_return);
			ft_free_fill_saved (saved, NULL);
			return (NULL);
		}
	}
	else
		ft_free_fill_saved (saved, NULL);
	return (line_return);
}

char	*get_return_line(char **saved)
{
	char	*line_return;

	if (ft_strchr_n(*saved) != NULL)
		line_return = ft_split_saved(saved);
	else
	{
		line_return = ft_strdup(*saved);
		ft_free_fill_saved (saved, NULL);
	}
	if (!line_return && *saved)
		ft_free_fill_saved (saved, NULL);
	return (line_return);
}

void	ft_free_fill_saved(char **saved, char *fill)
{
	free (*saved);
	*saved = fill;
}
