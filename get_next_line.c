/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastrov <acastrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:30:18 by acastrov          #+#    #+#             */
/*   Updated: 2024/10/29 21:41:57 by acastrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	ft_read(int fd, char **saved);
char	*ft_free(char **to_free, int flag);
char	*ft_split_saved(char **saved);
// Reads and saves text to a file until n, returns line and stores next for future calls
char	*get_next_line(int fd)
{
	static char	*saved; // Static char to store everything read until n
	char		*line_return; // Line to return to user
	char		*temp; // Temp to store and free saved str, used in join
	char		*join; // Temp to store joined str
	ssize_t		bytes_readed;

	if (fd < 0 || BUFFER_SIZE <= 0) // Check for invalid size of not fd
		return (NULL);
	if (!saved) // If there's nothing on saved, we read until next n or EOF
		bytes_readed = ft_read(fd, &saved);
	while ((saved != NULL || bytes_readed > 0)&& ft_strchr_n(saved) == NULL) // We store until n or EOF, I loop indefinetly if 0 bytes readed carefull
	{
		temp = ft_strdup(saved);  // Temp for storing saved string in new pointer address
		free (saved); // Free saved to avoid leaks, it holds the same value as join
		saved = NULL; // Null for ptr handling
		bytes_readed = ft_read(fd, &saved); // Read file for n bytes
		if (bytes_readed == 0)
		{
			saved = temp;
			break;
		}
		join = ft_strjoin(temp, saved); // Add new str readed to what we've saved
		free (temp);
		free (saved);
		saved = join;
	}
	if (ft_strchr_n(saved) != NULL) // If there's N in saved, we split saved and create line_return.
		line_return = ft_split_saved(&saved);
	else // If there's no N, we return the rest of saved.
	{
		line_return = ft_strdup(saved);
		free(saved);
		saved = NULL; // Null reset for next call to GNL
	}
	if (!line_return && saved)
		return (ft_free(&saved, 2)); // Free saved, reset to NULL
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
	if (bytes_readed < 0) // Check for fail, return null
	{
		free(buf);
		return(0);
	}
		//return (ft_free(&buf, 0));
	if (bytes_readed == 0) // If not bytes readed, free buf and return empty string. Here's my problem, if saved is null, then will null join and return null
	{
		free(buf);
		return (0);
	}
	buf[bytes_readed] = '\0'; // Always Null terminate
	if (*saved)
	{
		free(*saved); // Not null reset, may be an issue?
		*saved = NULL;
	}
	*saved = ft_strdup(buf);
	free (buf); // After we used buf, we free it
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
		return (ft_free(saved, 2));

	if (next_n && *(next_n + 1) != '\0') // Check fot n right before EOF, reference to next_n is lost in free saved
	{
		temp = ft_strdup(next_n + 1);
		*saved = NULL;
		free (*saved);
		*saved = temp;
		if (!*saved) // Malloc check
			{
				free(line_return);
				return (NULL);
			}
	}
	else
	{
		free(*saved);
		*saved = NULL;
	}
	return (line_return);
}
// Frees pointer direction and returns different values according to flag
char	*ft_free(char **to_free, int flag)
{
	free(*to_free);
	if (flag == 1) // If empty saved, we return empty string
		return (ft_strdup(""));
	if (flag == 2) // If freeing saved, we must assign NULL value
		*to_free = NULL;
	return (NULL);
}
/*
int	main(void)
{
	int fd;
	char *string;

	fd = open("41_no_nl", O_RDONLY);
	string = get_next_line(fd);
	printf("First gnl, He leido esto: %s", string);
	string = get_next_line(fd);
	printf("------\nCall to second GNL\n------\n");
	printf("Second GNL, He leido esto: %s", string);
	string = get_next_line(fd);
	printf("------\nCall to third GNL\n------\n");
	printf("Third GNL, He leido esto: %s", string);
	string = get_next_line(fd);
	printf("------\nCall to fourth GNL\n------\n");
	printf("Fourth GNL, He leido esto: %s", string);
	string = get_next_line(fd);
	printf("------\nCall to fith GNL\n------\n");
	printf("Fith GNL, He leido esto: %s", string);
	free (string);
	return(0);
}*/
