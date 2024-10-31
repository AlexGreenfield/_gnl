/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastrov <acastrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:30:18 by acastrov          #+#    #+#             */
/*   Updated: 2024/10/31 16:43:34 by acastrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	ft_read(int fd, char **saved);
ssize_t	ft_keep_reading(int fd, char **saved);
char	*ft_free(char **to_free, int flag);
char	*ft_split_saved(char **saved);
void	ft_free_null_saved(char **saved);
void	ft_free_fill_saved(char **saved, char *fill);


// Reads and saves text to a file until n, returns line and stores next for future calls
char	*get_next_line(int fd)
{
	static char	*saved; // Static char to store everything read until n
	char		*line_return; // Line to return to user
	ssize_t		bytes_readed;

	bytes_readed = 0;
	if (fd < 0 || BUFFER_SIZE <= 0) // Check for invalid size of not fd
		return (NULL);
	if (!saved) // If there's nothing on saved, we read until next n or EOF
		bytes_readed = ft_read(fd, &saved);
	while (saved != NULL && ft_strchr_n(saved) == NULL) // We store until n or EOF, I loop indefinetly if 0 bytes readed carefull
	{
		bytes_readed = ft_keep_reading(fd, &saved);
		if (bytes_readed <= 0) // Checks for 0 or error, if error should return null!!! Only paco test that fails
			break;
	}
	if (bytes_readed < 0)
	{
		ft_free_fill_saved(&saved, NULL);
		return (NULL);
	}
	if (ft_strchr_n(saved) != NULL) // If there's N in saved, we split saved and create line_return.
		line_return = ft_split_saved(&saved);
	else// If there's no N, we return the rest of saved.
	{
		line_return = ft_strdup(saved);
		ft_free_fill_saved (&saved, NULL); // Null reset for next call to GNL, fill version works for simplicity but I need to check if its valid
	}
	if (!line_return && saved) // Malloc check
			ft_free_null_saved (&saved); // Same, check for fill version
	return (line_return);
}
// Reads n bytes in buffer and stores it in saved
ssize_t	ft_read(int fd, char **saved)
{
	ssize_t	bytes_readed;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1); // We alloc buffer for n bytes to read
	if (!buf)
		return(0);
	bytes_readed = read(fd, buf, BUFFER_SIZE);
	if (bytes_readed <= 0) // Check for fail, need to make exception for this
	{
		free(buf);
		return(bytes_readed);
	}
	buf[bytes_readed] = '\0'; // Always Null terminate
	if (*saved)
		ft_free_fill_saved (saved, NULL);
	*saved = ft_strdup(buf);
	free (buf); // After we used buf, we free it
	return (bytes_readed);
}
ssize_t	ft_keep_reading(int fd, char **saved)
{
	char	*temp; // Temp to store and free saved str, used in join
	char	*join; // Temp to store joined str
	ssize_t	bytes_readed;

	temp = ft_strdup(*saved);  // Temp for storing saved string in new pointer address
	ft_free_null_saved (saved);
	bytes_readed = ft_read(fd, saved); // Read file for n bytes
	if (bytes_readed <= 0)
	{
		*saved = temp;
		return (bytes_readed);
	}
	join = ft_strjoin(temp, *saved); // Add new str readed to what we've saved
	free (temp);
	free (*saved);
	*saved = join;
	return (bytes_readed);
}
// If n, divides saved in two : the line to return before n and new saved after n
char *ft_split_saved(char **saved)
{
	size_t	ptr_diff; // N bytes to copy with substr
	char	*next_n; // Pointer to next n
	char	*line_return;
	char	*temp;

	next_n = ft_strchr_n(*saved); // We find n
	ptr_diff = next_n - *saved; // We calculate the size to be copied
	line_return = ft_substr(*saved, 0, ptr_diff + 1); // We make a new string from actual string to n
	if (!line_return) // Malloc check
		{
			ft_free_null_saved (saved); // Ask for free and null
			return (NULL);
		}
	if (*next_n && *(next_n + 1) != '\0') // Check fot n right before EOF, reference to next_n is lost in free saved
	{
		temp = ft_strdup(next_n + 1);
		free (*saved);
		*saved = temp;
		if (!*saved) // Malloc check
			{
				free(line_return); // Ask for free and null
				ft_free_fill_saved(saved, NULL);
				return (NULL);
			}
	}
	else
		ft_free_null_saved (saved);
	return (line_return);
}
// Frees pointer direction and returns different values according to flag. Right now it has no use
char	*ft_free(char **to_free, int flag)
{
	free(*to_free);
	if (flag == 1) // If empty saved, we return empty string
		return (ft_strdup(""));
	if (flag == 2) // If freeing saved, we must assign NULL value
		*to_free = NULL;
	return (NULL);
}

void	ft_free_null_saved(char **saved) // Maybe be deprecated by fill version
{
	free (*saved);
	*saved = NULL;
}

void	ft_free_fill_saved(char **saved, char *fill) // If this is legit with NULL, use it for every call of saved
{
	free (*saved);
	*saved = fill;
}
