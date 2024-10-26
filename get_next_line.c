/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastrov <acastrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:30:18 by acastrov          #+#    #+#             */
/*   Updated: 2024/10/26 17:15:34 by acastrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
// Leaks cause not join yet
char	*ft_read(int fd, char **saved);
char	*ft_free(char **to_free, int flag);
static char *ft_split_saved(char **saved);

char	*get_next_line(int fd)
{
	static char	*saved;
	char		*line_return;

	if (fd < 0 || BUFFER_SIZE <= 0) // Check for invalid size of not fd
		return (NULL);
	if (!saved) // If there's nothing on saved, we read until next n or EOF
		ft_read(fd, &saved);
	while (saved && ft_strchr_n(saved) == NULL)
		saved = ft_strjoin(saved, ft_read(fd, &saved)); // May cause leaks?
	if (ft_strchr_n(saved) != NULL) // If there's N in saved, we must split saved and create line_return
		line_return = ft_split_saved(&saved);
	else // If there's no N, we return the rest of saved. Now it fails cause of this, we need to read more
	{
		line_return = ft_strdup(saved);
		return (ft_free(&saved, 2));
	}
	if (!line_return)
		return (ft_free(&saved, 2));
	return (line_return);
}

char	*ft_read(int fd, char **saved)
{
	ssize_t	bytes_readed;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1); // We alloc buffer and read
	if (!buf)
		return(NULL);
	bytes_readed = read(fd, buf, BUFFER_SIZE);
	if (bytes_readed < 0) // Check for fail, return null
		return (ft_free(&buf, 0));
	else if (bytes_readed == 0) // If not bytes readed, free buf and return empty string
		return (ft_free(&buf, 1));
	buf[bytes_readed] = '\0'; // Always Null terminate
	*saved = ft_strdup(buf); // First fill of saved, check for fail
	if (!*saved)
		return (ft_free(saved, 0));
	while (bytes_readed > 0 && ft_strchr_n(*saved) == NULL) // If there's saved left, we read
	{
		bytes_readed = read(fd, buf, BUFFER_SIZE);
		if (bytes_readed < 0)
			return (ft_free(&buf, 0));
		*saved = ft_strjoin(*saved, buf); // Join for keeping fill saved
		if (!saved)
			return (ft_free(saved, 2));
	}
	free (buf); // After we used buf, we free it
	return (*saved);
}
static char *ft_split_saved(char **saved)
{
	size_t	ptr_diff;
	char	*next_n;
	char	*temp;
	char	*line_return;

	next_n = ft_strchr_n(*saved); // We need a join if saved left
	ptr_diff = next_n - *saved; // We calculate the size to be copied
	line_return = ft_substr(*saved, 0, ptr_diff + 1); // We make a new string from actual string to n
	if (!line_return)
		return (ft_free(saved, 2));
	temp = ft_strdup(next_n + 1); // Se save the string after n
	free (*saved);
	*saved = temp;
	if (!*saved)
		return (ft_free(saved, 2));
	return (line_return);
}
// Frees pointer direction and returns different values according to flag
char	*ft_free(char **to_free, int flag)
{
	free(*to_free);
	if (flag == 1) // If empty saved, we return empty string, may cause leaks cause not free?
		return (ft_strdup(""));
	if (flag == 2) // If freeing saved, we must assign NULL value
		*to_free = NULL;
	return (NULL);
}
