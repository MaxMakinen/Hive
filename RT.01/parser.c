/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:52:16 by mmakinen          #+#    #+#             */
/*   Updated: 2022/11/07 14:52:20 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"


int	open_file(int *fd, const char *filename)
{
	*fd = open(filename, O_DIRECTORY);
	if (*fd > 0)
	{
		ft_putendl("ERROR: input was directory.\nUsage: ./RT <input .dae file>");
		close_file(*fd);
		exit(0);
	}
	*fd = open(filename, O_RDONLY);
	if (*fd == -1)
	{
		ft_putendl("ERROR: failed to open file.");
		exit(0);
	}
	return (TRUE);
}

int	close_file(int fd)
{
	if (close(fd) == -1)
	{
		ft_putendl("ERROR: failed to close file");
		exit(0);
	}
	return (TRUE);
}

// can be improved with loop, we're doing the same thing twice
int ft_atof(char **str, char *end, float *output)
{
	int		decimal[2];
	char	number[4096];

	decimal = {0, 0};
	ft_bzero(number, 4096);
	if (**str == '-')
		number[index++] = **str++;
	while (*str < end && !ft_isdigit(*str) && **str != '.' && index < 4096)
		number[index++] = **str++;
	if (*str >= end || !ft_isspace(*str))
		return (FALSE);
	decimal[0] = ft_atoi(number);
	index = 0;
	ft_bzero(number, 4096);
	*str++;
	while (*str < end && ft_isdigit(*str) && index < 4096)
		number[index++] = **str++;
	if (*str >= end || !ft_isspace(*str))
		return (FALSE);
	decimal[1] = ft_atoi(number);
	if (decimal[0] < 0)
	decimal[1] = -decimal[1];
	*output = decimal[1] / powf(10.0, index);
	*output += (float)decimal[0];
	return (TRUE)
}

int	get_floats(char *start, char *end, float *output, int max)
{
	int index;

	index = 0;
	while (start < end && index < max)
	{
		while (ft_isspace(start))
			start++;
		if (start < end)
			 if (!atof(&start, end, &output[index++]))
			 	return (FALSE);
		start++;
	}
	return (TRUE);
}

int	xml_parser(char *input, t_data *output)
{
	int		fd;
	char	buffer[4096];
	char	*ptr;
	int		index;
	int		nl = 0;
	int		len = 0;
	char	***storage;
	char	*line;

	//Count new lines
	open_file(&fd, input);
	while ((len = read(fd, buffer, 4096)) > 0)
	{
		index = 0;
		while (index < len)
		{
			if (buffer[index++] == '\n')
				nl++;
		}
	}
	close_file(fd)
	storage = (char ***)ft_calloc(sizeof(char **), nl + 1);
	storage[nl] = 0;
	index = 0;
	open_file(&fd, input);
	while (get_next_line(fd, &line))
	{
		storage[index++] = ft_strsplit(line, ' ');
	}
}