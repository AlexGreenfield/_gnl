/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastrov <acastrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:30:18 by acastrov          #+#    #+#             */
/*   Updated: 2024/10/18 17:49:06 by acastrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

#include "get_next_line.h"
#include <stdio.h> // REMOVE
#include <string.h>

static char	*ft_fill_line(char *buf);

char	*get_next_line(int fd)
{
	size_t	bytes_readed; // A counter for bytes readed by read
	char	buf[BUFFER_SIZE + 1]; // Buffer to allocate readed bytes
	char	*line_return; // Text where we will store our lines readed
	if (fd < 0)
		return (NULL);
	bytes_readed = read(fd, buf, BUFFER_SIZE); // We read first n bytes
	if (bytes_readed <= 0) // delete this, second call of gnl may display constan varaible and not readed bytes
		return (NULL);
	buf[bytes_readed] = '\0'; // We null terminated to avoid conflicts at ft_strlen
	printf("Buffer size is = %d\n", BUFFER_SIZE);
	printf("I readed %zu bytes\n", bytes_readed);
	printf("First read, buf is: %s\n", buf);
	line_return = ft_first_read(buf); // We do our first read of line, cat if theres constan variable char
	if (!line_return)
		return (NULL);
	printf("First read, line is: %s \n\n\n", line_return);
	while (ft_next_n(line_return) == NULL && bytes_readed > 0) // If we didn't reach \n or EOF, we loop
	{
		bytes_readed = read(fd, buf, BUFFER_SIZE);
		buf[bytes_readed] = '\0';
		printf("In Loop, buf is: %s\n", buf);
		line_return = ft_malloc_cat(line_return, buf);
		printf("In Loop, line is: %s \n\n\n----\n", line_return);
	}
	if (ft_next_n (line_return) != NULL)
		line_return = ft_fill_line(line_return); // Somehow this works
	printf("Out of loop, line is: %s \n\n", line_return);
	return (line_return);
}

// Fills the line with actual buff
static char	*ft_fill_line(char *buf)
{
	char	*line;
	char	*next_n;
	int		ptr_diff;
	int		i;

	i = 0;
	next_n = ft_next_n(buf);
	printf("In fill_line buff is %p, and n_find is %p\n", buf, next_n);
	ptr_diff = next_n - line;
	/*if (ptr_diff == 0)
		ptr_diff = BUFFER_SIZE;*/
	printf("Diff is %d\n", ptr_diff);
	while (i < ptr_diff)
	{
		line[i] = buf[i];
		i++;
	}
	line[i] = '\0'; // Always Null terminate!!!
	return (line);
}

int	main(void)
{
	int fd;
	char *string;

	fd = open("../small_test.txt", O_RDONLY);
	string = get_next_line(fd);
	printf("First gnl, He leido esto: %s\n", string);
	string = get_next_line(fd);
	printf("Second GNL, He leido esto: %s\n", string);
	return(0);
}
// First, we need to read the file in buf
// Then, we copy buff into our static char
