/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 10:27:44 by mmakinen          #+#    #+#             */
/*   Updated: 2021/12/16 14:49:19 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t newline(const char *src, char **dst)
{
	size_t	finder;

	finder = 0;
	while (src[finder] != '\n' && src[finder] != '\0')
		finder++;
	if (src[finder] == '\n')
	{
		*dst = ft_strsub(src, 0, finder);
		return (finder + 1);
	}
	return (0);
}
/*
static void cleanup(void)
{
	temp = memory[fd];
	memory[fd] = ft_strsub(temp, bytes, (ft_strlen(temp) - bytes));
	free(temp);
	return (1);
}
*/

int	get_next_line(const int fd, char **line)
{
	static char	*memory[MAX_FD];
	char		*buffer[BUFF_SIZE + 1];
	char		*temp;
	int			bytes;
	size_t		test;

	if (fd < 0 || fd > MAX_FD || !line)
		return (-1);
	if (memory[fd])
	{
		test = newline(memory[fd], line);
		if (test > 0)
		{
			temp = memory[fd];
			memory[fd] = ft_strsub(temp, (test), (ft_strlen(temp) - test));
			free(temp);
			return (1);
		}
	}
	ft_bzero(buffer, BUFF_SIZE);
	bytes = read(fd, buffer, BUFF_SIZE);
	while (bytes > 0)
	{
		temp = memory[fd];
		memory[fd] = ft_strjoin(temp, (const char *)buffer);
		free(temp);
		test = newline(memory[fd], line);
		if (test > 0)
		{
			temp = memory[fd];
			memory[fd] = ft_strsub(temp, (test), (ft_strlen(temp) - test));
			free(temp);
			return (1);
		}
		ft_bzero(buffer, BUFF_SIZE);
		bytes = read(fd, buffer, BUFF_SIZE);
		if (bytes == 0)
		{
			*line = memory[fd];
			return (1);
		}
	}
	return (bytes);
}
