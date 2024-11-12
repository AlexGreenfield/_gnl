/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastrov <acastrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:30:18 by acastrov          #+#    #+#             */
/*   Updated: 2024/11/12 17:26:26 by acastrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	ft_read(int fd, char **saved);
ssize_t	ft_keep_reading(int fd, char **saved);
char	*ft_split_saved(char **saved);
char	*get_return_line(char **saved, ssize_t bytes_readed);

// Reads and saves of a file until n, returns line and stores rest for next calls
char	*get_next_line(int fd)
{
	static char	*saved; // Static char to store everything read until n
	char		*line_return; // Line to return to user
	ssize_t		bytes_readed; // Number of bytes readed

	bytes_readed = 0;
	if (fd < 0 || BUFFER_SIZE <= 0) // Check for invalid size or no valid fd
		return (NULL);
	if (!saved) // If there's nothing in saved, we make a first read
		bytes_readed = ft_read(fd, &saved);
	while (saved != NULL && ft_strchr_n(saved) == NULL) // Read and store until n or EOF
	{
		bytes_readed = ft_keep_reading(fd, &saved);
		if (bytes_readed <= 0) // Check for 0 bytes read or -1 if anything fails
			break ;
	}
	line_return = get_return_line(&saved, bytes_readed); // After reading, we gen our line
	return (line_return);
}

// Reads n bytes into a buffer and stores it in saved
ssize_t	ft_read(int fd, char **saved)
{
	ssize_t	bytes_readed;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1); // Allocate buffer for n bytes to read
	if (!buf) // If it fails, return -1 and free saved on gnl
		return (-1);
	bytes_readed = read(fd, buf, BUFFER_SIZE);
	if (bytes_readed <= 0) // Free buffer on read error or no bytes read
	{
		free(buf);
		return (bytes_readed);
	}
	buf[bytes_readed] = '\0'; // Always null-terminate
	*saved = ft_strdup(buf); // We copy buf into saved
	free (buf); // Free buffer after use
	if (!*saved) // Check for malloc failure in ft_strdup
		return (-1);
	return (bytes_readed);
}
// Join new reads into static saved string
ssize_t	ft_keep_reading(int fd, char **saved)
{
	char	*temp; // Temp to store saved string for joining
	char	*join; // Temp to store joined string
	ssize_t	bytes_readed;

	temp = ft_strdup(*saved);  // Store saved in new pointer address
	free (*saved); // Free saved to avoid leaks
	*saved = NULL; // Always NULL saved after freeing it
	bytes_readed = ft_read(fd, saved); // Read file for n bytes
	if (bytes_readed <= 0) // On error or EOF, restore temp to saved
	{
		*saved = temp;
		return (bytes_readed);
	}
	join = ft_strjoin(temp, *saved); // Append new string to saved
	free (temp); // Free temp and saved to avoid leaks
	free (*saved);
	*saved = join; // Update saved with joined result
	if (!*saved) // Check for malloc failure
		return (-1);
	return (bytes_readed);
}

// Checks for errors and n in saved
char	*get_return_line(char **saved, ssize_t bytes_readed)
{
	char	*line_return;

	if (bytes_readed < 0) // If anything fails (read or malloc), frees saved
	{
		free (*saved);
		*saved = NULL;
		return (NULL);
	}
	if (ft_strchr_n(*saved) != NULL) // If n exists in saved, split saved and return line
		line_return = ft_split_saved(saved);
	else // If no n, return the rest of saved
	{
		line_return = ft_strdup(*saved);
		free (*saved); // Always free saved to avoid leaks
		*saved = NULL; // Reset for next call to GNL
	}
	if (!line_return && *saved) // Check for malloc failure in any previous step
	{
		free (*saved);
		*saved = NULL;
	}
	return (line_return);
}

// If n exists in saved, splits saved into two parts: before and after n
char	*ft_split_saved(char **saved)
{
	char	*next_n; // Pointer to next n
	char	*line_return; // Line to return
	char	*temp; // Temp to store saved

	next_n = ft_strchr_n(*saved); // Find n
	line_return = ft_substr(*saved, 0, next_n - *saved + 1); // New string from start to n, + 1 for \0
	if (*next_n && *(next_n + 1)) // Check in case n is right before EOF
	{
		temp = ft_strdup(next_n + 1); // Copy remaining string after n
		free (*saved); // Free saved to avoid leaks
		*saved = temp; // We update our saved string
	}
	else
	{
		free (*saved); // If there's nothing remaining after n; reset saved
		*saved = NULL; // Always NULL saved after freeing it for future calls to GNL
	}
	return (line_return);
}
