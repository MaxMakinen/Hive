/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 10:27:44 by mmakinen          #+#    #+#             */
/*   Updated: 2021/12/07 16:15:36 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line(const int fd, char **line)
{
	unsigned const char	*reader;
	unsigned const char	*counter;
	unsigned char		*printer;
	unsigned char		*buffer;
	size_t				len;
	size_t				buffer_size;
	int					newl;

	newl - '\n';
	buffer = ft_strnew(BUFF_SIZE);
	buffer_size = read(fd, buffer, BUFF_SIZE);
	reader = ft_strdup(buffer);
	end = ft_strchr(reader, newl);
	if (end != NULL)
		found new line and we're finished;
		return (whatever);
	bzero(buffer, ft_strlen(buffer));
	buffer_size = read(fd, buffer, BUFF_SIZE);
	printer = ft_strnew(ft_strlen(reader) + buffer_size); 
	printer = ft_strcpy(printer, reader);


	printer = ft_strnew(ft_strlen(printer) + buffer_size); 

	if (buffer_size > 0)
		return (1);
	else
		return (buffer_size);
}
