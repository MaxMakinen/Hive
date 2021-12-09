/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 10:27:44 by mmakinen          #+#    #+#             */
/*   Updated: 2021/12/09 13:59:32 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line(const int fd, char **line)
{
	char	*mem1;
	char	*mem2;
	char	*buffer;
	char	*test;
	size_t			buff_size;
//	size_t			newl;

	buffer = ft_strnew(BUFF_SIZE);
	mem1  = ft_strnew(BUFF_SIZE);
//	mem2  = ft_strnew(BUFF_SIZE);
//	mem1 = 0;
//	mem2 = 0;
	buff_size = 1;
	while (buff_size > 0)
	{
		buff_size = read(fd, buffer, BUFF_SIZE);
		if (buff_size > 0)
		{
			if (mem1)
			{
				mem2 = ft_strdup(mem1);
				free(mem1);
			}
			mem1 = ft_strnew(ft_strlen(mem2) + ft_strlen(buffer));
			if (mem2)
			{
				mem1 = ft_strcpy(mem1, mem2);
				free(mem2);
			}
			mem1 = ft_strcat(mem1, buffer);
//			newl = ft_strlenc(mem1, '\n');
			test = ft_strchr(mem1, '\n');
//			if (newl != 0)
			if (test != NULL)
			{
				mem2 = ft_strcdup(mem1, '\n');
//				mem2 = ft_strnew(newl);
//				mem2 = ft_strncpy(mem2, mem1, newl);
//				if (*line)
//					free(*line);
				*line = mem2;
				return (1);
			}
		}
	}
	return (buff_size);
}
