/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastrov <acastrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:30:22 by acastrov          #+#    #+#             */
/*   Updated: 2024/10/17 18:35:41 by acastrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Finds the next iteration of n in buff
char	*ft_next_n(char *buf)
{
	char	*n_find;

	n_find = buf;
	while (*n_find)
	{
		if (*n_find == '\n')
			return (n_find);
		n_find++;
	}
	return (buf);
}
