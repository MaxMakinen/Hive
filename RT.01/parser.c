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

int	close_file(int fd)
{
	if (close(fd) == -1)
	{
		ft_putendl("ERROR: failed to close file");
		exit(0);
	}
	return (TRUE);
}

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

// can be improved with loop, we're doing the same thing twice
int ft_atof(char **str, char *end, float *output)
{
	int		decimal[2];
	char	number[4096];
	int		index;

	decimal[0] = 0;
	decimal[1] = 0;
	index = 0;
	ft_bzero(number, 4096);
	if (**str == '-')
		number[index++] = **str++;
	while (*str < end && !ft_isdigit(**str) && **str != '.' && index < 4096)
		number[index++] = **str++;
	if (*str >= end || !ft_isspace(**str))
		return (FALSE);
	decimal[0] = ft_atoi(number);
	index = 0;
	ft_bzero(number, 4096);
//	*str++;
	while (*str < end && ft_isdigit(**str) && index < 4096)
		number[index++] = **str++;
	if (*str >= end || !ft_isspace(**str))
		return (FALSE);
	decimal[1] = ft_atoi(number);
	if (decimal[0] < 0)
	decimal[1] = -decimal[1];
	*output = decimal[1] / powf(10.0, (float)index);
	*output += (float)decimal[0];
	return (TRUE);
}

int	get_floats(char *start, char *end, float *output, int max)
{
	int index;

	index = 0;
	while (start < end && index < max)
	{
		while (ft_isspace(*start))
			start++;
		if (start < end)
			 if (!ft_atof(&start, end, &output[index++]))
			 	return (FALSE);
		start++;
	}
	return (TRUE);
}

int	get_tuple(char *input, t_tuple *output)
{}

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
	int		fd_temp;
	char	tmpname[] = "temp_input.dae";
	int		len2;

	//Count new lines
	open_file(&fd, input);
	if ((fd_temp = open(tmpname, O_CREAT|O_WRONLY|O_TRUNC, 0644)) < 0)
	{
		printf("TEMP CREATION FAILED fd:%d\n", fd_temp);
		exit(12);
	}
	while ((len = read(fd, buffer, 4096)) > 0)
	{
		index = 0;
		while (index < len)
		{
			if (buffer[index] == '<' && buffer[index + 1] == '!' && buffer[index + 2] == '-' && buffer[index + 3] == '-')
			{
				while (index < len)
				{
					if (buffer[index + 2] && buffer[index] == '-' && buffer[index + 1] == '-' && buffer[index + 2] == '>')
					{
						index += 2;
//						printf ("index = %d\n len = %d\n", index, len);
					}
					index++;
				}
			}
			if (index == len)
			{
				nl--;
				break;
			}
			if (buffer[index] != '\t')
				write(fd_temp, &buffer[index], 1);
			if (buffer[index++] == '\n')
				nl++;
		}
	}
	close_file(fd);
	close_file(fd_temp);
	storage = (char ***)ft_calloc(sizeof(char **), nl + 1);
	storage[nl] = 0;
	index = 0;
	open_file(&fd, tmpname);
	while (get_next_line(fd, &line))
	{
		if (*line)
			storage[index++] = ft_strsplit(line, ' ');
		else
			storage[index++] = NULL;
		free(line);
	}
	output->storage = storage;
	output->nl = nl;
	printf("index = %d\n", index);
	return (TRUE);
}

void	xml_reader(t_data *data)
{
	char	keywords[12][10] = {"loc", "coi", "up", "rot", "size", "brightness", "type", "is", "transform", "color", "material"};
}

int	main(int ac, char **av)
{
	t_data	data;
	char	nlc[1];

	int	i = 0;
	int	x = 0;

	xml_parser(av[1], &data);
	xml_reader(&data);
	printf("nl = %d\n", data.nl);
	while (i <= data.nl)
	{
		x = 0;
		if (data.storage[i] == NULL)
		{
			printf("S[%d][%d] -=EMPTY=-\n", i + 1, x);
			i++;
			continue;
		}
		while (data.storage[i][x] && data.storage[i][x] != 0)
		{
			printf("S[%d][%d] = %s	", i + 1, x, data.storage[i][x]);
			x++;
		}
		printf("\n");
		i++;
	}

	return (0);
}