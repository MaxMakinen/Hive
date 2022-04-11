/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 10:27:44 by mmakinen          #+#    #+#             */
/*   Updated: 2021/12/21 14:58:42 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	newline(const char *memory, char **line)
{
	size_t	finder;

	finder = 0;
	while (memory[finder] != '\n' && memory[finder] != '\0')
		finder++;
	if (memory[finder] == '\n')
	{
		*line = ft_strsub(memory, 0, finder);
		return (finder + 1);
	}
	return (0);
}

static int	cleanup(char **target, int bytes, char **buffer)
{
	char	*temp;

	temp = *target;
	*target = ft_strsub(temp, bytes, (ft_strlen(temp) - bytes));
	free(temp);
	ft_memdel((void **)buffer);
	return (1);
}

static int	last_line(char **line, char **memory, char **buffer)
{
	*line = ft_strdup(*memory);
	ft_memdel((void **)memory);
	ft_memdel((void **)buffer);
	return (1);
}

static int	read_file(char **memory, char **line, char *buffer)
{
	char	*temp;

	temp = *memory;
	*memory = ft_strjoin(*memory, (const char *)buffer);
	free(temp);
	ft_bzero(buffer, BUFF_SIZE);
	return (newline(*memory, line));
}

int	get_next_line(const int fd, char **line)
{
	static char	*memory[MAX_FD];
	char		*buffer;
	int			bytes;

	if (fd < 0 || fd >= MAX_FD || !line)
		return (-1);
	buffer = ft_strnew(BUFF_SIZE);
	if (memory[fd])
	{
		bytes = newline(memory[fd], line);
		if (bytes > 0)
			return (cleanup(&memory[fd], bytes, &buffer));
	}
	bytes = read(fd, buffer, BUFF_SIZE);
	while (bytes > 0)
	{
		bytes = read_file(&memory[fd], line, buffer);
		if (bytes > 0)
			return (cleanup(&memory[fd], bytes, &buffer));
		bytes = read(fd, buffer, BUFF_SIZE);
	}
	if (bytes == 0 && memory[fd] && memory[fd][0] != '\n' && memory[fd][0])
		return (last_line (line, &memory[fd], &buffer));
	ft_memdel((void **)buffer);
	return (bytes);
}
