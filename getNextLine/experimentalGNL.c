/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 10:27:44 by mmakinen          #+#    #+#             */
/*   Updated: 2021/12/31 19:03:17 by mmakinen         ###   ########.fr       */
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

static int	cleanup(char **memory, int bytes, char **buffer)
{
	ft_strncpy(*memory, *memory + bytes, ft_strlen(*memory));
	ft_strdel(buffer);
	return (1);
}

static int	last_line(char **line, char **memory, char **buffer, int bytes)
{
	int	check;

	if (bytes < 0)
		return (bytes);
	check = 0;
	if (bytes == 0 && *memory && *memory[0] != '\n' && *memory[0])
	{
		*line = ft_strdup(*memory);
		check = 1;
	}
	ft_strdel(memory);
	ft_strdel(buffer);
	return (check);
}
/*
static int	read_file(char **memory, char **line, char *buffer)
{
	char	*temp;

	temp = *memory;
	*memory = ft_strjoin(*memory, (const char *)buffer);
	free(temp);
	ft_bzero(buffer, BUFF_SIZE);
	return (newline(*memory, line));
}
*/
static int	read_file(char **memory, char **line, char *buffer, int bytes)
{
	char	*temp;
	int		size;
	size_t	memsize;

	if (!*memory)
	{
		*memory = ft_strnew(BUFF_SIZE);
		*line = *memory + BUFF_SIZE + 1;
	}
	size = ft_strlen(*memory) + 1;
	memsize = *line - *memory;
	if ((size + bytes) > (int)memsize)
	{
		temp = *memory;
		*memory = ft_strnew(memsize * 2);
		*line = *memory + (memsize * 2);
		ft_strncpy(*memory, temp, memsize);
		ft_strdel(&temp);
	}
	ft_strlcat(*memory, buffer, size + bytes);
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
		bytes = read_file(&memory[fd], line, buffer, bytes);
		if (bytes > 0)
			return (cleanup(&memory[fd], bytes, &buffer));
		bytes = read(fd, buffer, BUFF_SIZE);
	}
	return (last_line (line, &memory[fd], &buffer, bytes));
}
