/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastrov <acastrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:30:18 by acastrov          #+#    #+#             */
/*   Updated: 2024/10/17 20:28:49 by acastrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

#include "get_next_line.h"
#include <stdio.h> // REMOVE
#include <string.h>

static char *ft_fill_line(char *buf, char *line);
void *ft_free(char *line);

char	*get_next_line(int fd)
{
	size_t bytes_readed; // A counter for bytes readed by read
	char buf[BUFFER_SIZE]; // Buffer to allocate readed bytes
	char *line; // Text where we will store our lines readed

	printf("Buffer size is = %d\n", BUFFER_SIZE);
	line = malloc(BUFFER_SIZE + 1 * sizeof(char)); // This malloc should increase over time
	while ((bytes_readed = read(fd, buf, BUFFER_SIZE))) // The start of our loop, read until EOF
	{
		if (bytes_readed < 0) // Control check
			return (NULL);
		printf("I readed %zu bytes\n", bytes_readed);
		printf("buf is: %s \n", buf);
		line = ft_fill_line(buf, line);
		printf("line is: %s \n\n", line);
	}
	return (line);
}
// Fills the line with actual buff
static char *ft_fill_line(char *buf, char *line)
{
	char *next_n;
	int ptr_diff;
	int	i;

	i = 0;
	next_n = ft_next_n(buf);
	printf("buff is %p, and n_find is %p\n", buf, next_n);
	ptr_diff = next_n - buf;
	if (ptr_diff == 0)
		ptr_diff = BUFFER_SIZE;
	printf("Diff is %d\n", ptr_diff);
	while (i < ptr_diff)
	{
		line[i] = buf[i];
		i++;
	}
	line[i] = '\0'; // Always Null terminate!!!
	return (line);
}
// If malloc error, frees all
void *ft_free(char *line);

int	main(void)
{
	int fd;
	char *string;

	fd = open("loreipsum.txt", O_RDONLY);
	string = get_next_line(fd);
	printf("He leido esto: %s", string);
	return(0);
}
