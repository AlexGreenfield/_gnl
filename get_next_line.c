/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastrov <acastrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:30:18 by acastrov          #+#    #+#             */
/*   Updated: 2024/10/28 18:00:12 by acastrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read(int fd, char **saved);
char	*ft_free(char **to_free, int flag);
char *ft_split_saved(char **saved);

char	*get_next_line(int fd)
{
	static char	*saved;
	char		*line_return;
	char		*temp;
	char		*join;

	if (fd < 0 || BUFFER_SIZE <= 0) // Check for invalid size of not fd
		return (NULL);
	if (!saved) // If there's nothing on saved, we read until next n or EOF
		ft_read(fd, &saved);
	while (saved && ft_strchr_n(saved) == NULL)
	{
		temp = ft_strdup(saved);
		free (saved);
		saved = NULL;
		ft_read(fd, &saved);
		join = ft_strjoin(temp, saved); // May cause leaks? Look for previous version Heres my leak!!
		saved = join;
	}
	if (ft_strchr_n(saved) != NULL) // If there's N in saved, we must split saved and create line_return. Here's my double free
		line_return = ft_split_saved(&saved);
	else // If there's no N, we return the rest of saved. Now it fails cause of this, we need to read more
	{
		line_return = ft_strdup(saved);
		free(saved);
		saved = NULL;
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
		return (ft_free(&buf, 0));
	buf[bytes_readed] = '\0'; // Always Null terminate
	*saved = ft_strdup(buf); // First fill of saved, check for fail
	free (buf); // After we used buf, we free it
	if (!*saved)
		return (ft_free(saved, 0));
	return (*saved);
}
char *ft_split_saved(char **saved)
{
	size_t	ptr_diff;
	char	*next_n;
	char	*line_return;

	next_n = ft_strchr_n(*saved); // We need a join if saved left
	ptr_diff = next_n - *saved; // We calculate the size to be copied
	line_return = ft_substr(*saved, 0, ptr_diff + 1); // We make a new string from actual string to n
	if (!line_return)
		return (ft_free(saved, 2));
	free (*saved);
	*saved = ft_strdup(next_n + 1); // Se save the string after n, CHECK IF VALID
	if (!*saved)
		{
			free(line_return);
			return (NULL);
		}
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
/*
int	main(void)
{
	int fd;
	char *string;

	fd = open("loreipsum_one_jump.txt", O_RDONLY);
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
