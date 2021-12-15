/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 10:27:44 by mmakinen          #+#    #+#             */
/*   Updated: 2021/12/15 16:21:32 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line(const int fd, char **line)
{
	static char	*memory[MAX_FD];
	char			*temp;
	char			*buffer;
	char			*reader;
	size_t					buff_size;
	size_t					newLine;

	buff_size = 1;
	buffer = ft_strnew(BUFF_SIZE);
	newLine = 0;
	reader = memory[fd];
	if (reader)
		newLine = ft_strlenc(reader, '\n');
	if (newLine != 0)
	{
		*line = ft_strcdup(reader, '\n');
		temp = ft_strdup(&reader[newLine]);
		free(reader);
		reader = temp;
//		ft_putstr("CraP");
		free(temp);
		return (1);
	}
	while (buff_size > 0)
	{
		buff_size = read(fd, buffer, BUFF_SIZE);
		if (buff_size > 0)
		{	
			if (reader != 0)
			{
				temp = ft_strdup(reader);
//				free(reader);
				reader = ft_strnew(ft_strlen(temp) + ft_strlen(buffer));
				reader = ft_strcpy(reader, temp);
				reader = ft_strcat(reader, buffer);
//				free(temp);
			}
			else 
				reader = ft_strdup(buffer);
			ft_bzero(buffer, BUFF_SIZE);
			newLine = ft_strlenc(reader, '\n');
			if (newLine != 0)
			{
				*line = ft_strsub(temp, 0, newLine);	
				reader = ft_strdup(temp + newLine);
				memory[fd]= reader;
//				free(reader);
				return (1);
			}
		}
	}
	return (buff_size);
}
