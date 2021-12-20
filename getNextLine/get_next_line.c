/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 10:27:44 by mmakinen          #+#    #+#             */
/*   Updated: 2021/12/20 21:07:02 by mmakinen         ###   ########.fr       */
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

static int	last_line(char **line, char **memory)
{
	*line = ft_strdup(*memory);
	ft_memdel((void **)memory);
	return (1);
}

static int	read_file(char **memory, char **line, char *buffer)
{
	char	*temp;

	temp = *memory;
	*memory = ft_strjoin(temp, (const char *)buffer);
	free(temp);
	ft_bzero(buffer, BUFF_SIZE);
	return (newline(*memory, line));
}

int	get_next_line(const int fd, char **line)
{
	static char	*memory[MAX_FD];
	char		buffer[BUFF_SIZE + 1];
	int			bytes;

	if (fd < 0 || fd > MAX_FD || !line)
		return (-1);
	if (memory[fd])
	{
		bytes = newline(memory[fd], line);
		if (bytes > 0)
			return (cleanup(&memory[fd], bytes));
	}
	ft_bzero(buffer, BUFF_SIZE);
	bytes = read(fd, buffer, BUFF_SIZE);
	while (bytes > 0)
	{
		bytes = read_file(&memory[fd], line, buffer);
		if (bytes > 0)
			return (cleanup(&memory[fd], bytes));
		bytes = read(fd, buffer, BUFF_SIZE);
	}
	if (bytes == 0 && memory[fd] && memory[fd][0] != '\n' && memory[fd][0])
		return (last_line (line, &memory[fd]));
	return (bytes);
}
