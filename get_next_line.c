/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastrov <acastrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:30:18 by acastrov          #+#    #+#             */
/*   Updated: 2024/10/19 21:52:49 by acastrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

#include "get_next_line.h"
#include <stdio.h> // REMOVE
#include <string.h>

static char	*ft_fill_line(char *line);
static char *ft_fill_saved(char *line, char *saved);

char	*get_next_line(int fd)
{
	size_t		bytes_readed; // A counter for bytes readed by read
	size_t		ptr_diff;
	char		buf[BUFFER_SIZE + 1]; // Buffer to allocate readed bytes
	char		*line_return; // Text where we will store our lines readed
	static char *saved;
	char		*new_n;

	if (fd < 0)
		return (NULL);
	bytes_readed = read(fd, buf, BUFFER_SIZE); // We read first n bytes
	if (bytes_readed <= 0 && saved == NULL) // Return if nothing to read
		return (NULL);
	buf[bytes_readed] = '\0';

	printf("Buffer size is = %d\n", BUFFER_SIZE);
	printf("I readed %zu bytes\n", bytes_readed);
	printf("First read, buf is: %s\n", buf);
	printf("First read, saved is: %s\n", saved);

	if (saved)
	{
		printf("Something was saved: %s\n", saved);
		line_return = ft_strdup(saved);
		printf("After strdup, line should had value: %s\n", line_return);
		line_return = ft_strjoin(line_return, buf); // We need to fix this
		printf("After join, line should had value: %s\n", line_return);
	}
	else if (!saved)
		line_return = ft_strdup(buf); // We do our first read of line, cat if theres constan variable char
	if (!line_return)
		return (NULL);

	printf("First read, line is: %s \n\n\n", line_return);

	while (ft_strchr(line_return) == NULL && bytes_readed > 0) // If we didn't reach \n or EOF, we loop
	{
		bytes_readed = read(fd, buf, BUFFER_SIZE);
		buf[bytes_readed] = '\0';

		printf("In Loop, buf is: %s\n", buf);

		line_return = ft_strjoin(line_return, buf);

		printf("In Loop, line is: %s \n\n\n----\n", line_return);

	}
	new_n = ft_strchr(line_return);
	ptr_diff= new_n - line_return;
	printf("After loop, there's n if there's pointer: %s\n", new_n);
	printf("After loop, diff is: %zu\n", ptr_diff);

	if (new_n != NULL)
	{
		printf("I enter n separator\n");
		saved = ft_strdup(new_n + 1);
		ft_strlcpy(line_return, line_return, ptr_diff + 1); // Somehow this works
	}
	printf("Out of loop, line is: %s \n", line_return);
	printf("Out of loop, saved is: %s\n\n", saved);
	return (line_return);
}

/* Fills the line with actual buff
static char	*ft_fill_line(char *line)
{
	char			*trim_line;
	char			*next_n;
	int				ptr_diff;
	int				i;

	i = 0;
	next_n = ft_next_n(line); // We find next n pointer
	ptr_diff = next_n - line; // We find the diff in bytes bewteen ptrs
	if (ptr_diff == 0)
		ptr_diff = BUFFER_SIZE;

	printf("Diff is %d\n", ptr_diff);

	trim_line = malloc (ptr_diff + 1 * sizeof(char)); // We allocate and fill just to next_n
	while (i < ptr_diff)
	{
		trim_line[i] = line[i];
		i++;
	}
	trim_line[i] = '\0'; // Always Null terminate!!!
	free(line);
	return (trim_line);
}

static char *ft_fill_saved(char *line, char *saved)
{
	char		*next_n;
	int			i;

	i = 0;
	next_n = ft_next_n(line); // We find next n pointer
	saved = malloc (ft_strlen(next_n) + 1 * sizeof(char)); // We fill buffer from next_n to the rest
	if(!saved)
		return (NULL);
	while(next_n[i] != '\0')
	{
		saved[i] = next_n[i];
		i++;
	}
	saved[i] = '\0';
	return (saved);
}*/

int	main(void)
{
	int fd;
	char *string;

	fd = open("../loreipsum.txt", O_RDONLY);
	string = get_next_line(fd);

	printf("First gnl, He leido esto: %s\n\n", string);

	string = get_next_line(fd);
	printf("\n------\nCall to second GNL\n------\n");
	printf("Second GNL, He leido esto: %s\n", string);
	string = get_next_line(fd);
	printf("\n------\nCall to third GNL\n------\n");
	printf("Third GNL, He leido esto: %s\n", string);
	string = get_next_line(fd);
	printf("\n------\nCall to fourth GNL\n------\n");
	printf("fourth GNL, He leido esto: %s\n", string);
	return(0);
}
// First, we need to read the file in buf
// Then, we copy buff into our static char
