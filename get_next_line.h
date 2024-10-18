/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastrov <acastrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:30:15 by acastrov          #+#    #+#             */
/*   Updated: 2024/10/18 16:34:01 by acastrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNLH
#	define GNLH

#include <stddef.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

char	*get_next_line(int fd);

// Utils
char *ft_first_read(const char *buf);
char *ft_malloc_cat(char *old_line, const char *buf);
char	*ft_next_n(char *buf);

#endif
