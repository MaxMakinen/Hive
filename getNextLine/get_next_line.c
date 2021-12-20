/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 10:27:44 by mmakinen          #+#    #+#             */
/*   Updated: 2021/12/20 15:00:10 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	newline(const char *src, char **dst)
{
	size_t	finder;

	finder = 0;
	while (src[finder] != '\n' && src[finder] != '\0')
		finder++;
	if (src[finder] == '\n')
	{
		*dst = ft_strsub(src, 0, finder);
		if (src[finder] + 1 == '\0')
			return (finder + 2);
		return (finder + 1);
	}
	return (0);
}

static int	cleanup(char **target, int bytes)
{
	char	*temp;

	temp = *target;
	*target = ft_strsub(temp, bytes, (ft_strlen(temp) - bytes));
	free(temp);
	return (1);
}

int	get_next_line(const int fd, char **line)
{
	static char	*memory[MAX_FD];
	char		buffer[BUFF_SIZE + 1];
	char		*temp;
	int			bytes;
	size_t		test;

	if (fd < 0 || fd > MAX_FD || !line)
		return (-1);
	if (memory[fd])
	{
		test = newline(memory[fd], line);
		if (test > 0)
			return (cleanup(&memory[fd], test));
	}
	ft_bzero(buffer, BUFF_SIZE);
	bytes = read(fd, buffer, BUFF_SIZE);
	if (bytes == 0 && memory[fd] && memory[fd][0] != '\n' && memory[fd][0])
	{
		*line = ft_strdup(memory[fd]);
		ft_memdel((void **)&memory[fd]);
		return (1);
	}
	while (bytes > 0)
	{
		temp = memory[fd];
		memory[fd] = ft_strjoin(temp, (const char *)buffer);
		free(temp);
		test = newline(memory[fd], line);
		if (test > 0)
			return (cleanup(&memory[fd], test));
		ft_bzero(buffer, BUFF_SIZE);
		bytes = read(fd, buffer, BUFF_SIZE);
		if (bytes == 0)
		{
			*line = ft_strdup(memory[fd]);
			ft_memdel((void **)&memory[fd]);
			return (1);
		}
	}
	return (bytes);
}
