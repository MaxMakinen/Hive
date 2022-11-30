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
#include <math.h>

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
		ft_putendl("ERROR: input was directory.\nUsage: ./RT <input .xml file>");
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
//REMOVE?
int ft_atoffy(char **str, char *end, float *output)
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
			 if (!ft_atoffy(&start, end, &output[index++]))
			 	return (FALSE);
		start++;
	}
	return (TRUE);
}

int	get_tuple(char **input, t_tuple *output)
{
	char	*start;
	char	*end;
	int		x;
	int		y;

	x = 0;
	y = 2;
	if (input[x][1])
	{
	start = input[x];
	start++;
	end = input[x];
	while (end && *end != '>' && *end != ' ')
		end++;
	x++;
	while (input[x][0] != '<')
	{
		output->a[x] = ft_atof(input[x]);
		x++;
	}
	if (input[x][1] != '/')
	{
		printf("%s\n",input[x]);
		printf("get_tuple error\n");
		exit(1);
	}
	else
	{
		while (start < end)
		{
			if (*start != input[x][y])
			{
				printf("get_tuple error2\n");
				exit(1);
			}
			start++;
			y++;
		}
	}
	}
	return (TRUE);
}

int	get_end(char ***start, char **parent_end, int mode, t_data *data)
{
	char ***temp;

	temp = start;
	// GET_END FUNCTION give error if finds a copy before end
	while (**temp && **temp < *parent_end)
	{
		if (***temp == "<")
		{
			if (***temp + 1 == "/" && ft_strcmp(&***temp + 2, &data->keyword_array[mode][2]))
				temp;;
			if (ft_strcmp(**temp, data->keyword_array[mode]))
				printf("keyword error\n");
		}
		**temp++;
	}
	if (temp == parent_end)
		return (FALSE);

}

//void	stack_new_object(t_main *main)
//{
//	if (main->o)
//}

//TO DO ENUM FOR MODES
int	parse(char ***start, char ***parent_end, int mode, int *pos, t_main *main, t_data *data)
{
	char	***temp;
	char	*t_word;
	char	*end;
	char	*keyword;
	int		line;
	int		row;
	int		new_mode = 0;

	temp = start;
	//DO PREP DEPENDING ON MODE
//	if (mode == 10)
//		stack_new_object(main);
	if (!get_end(start, parent_end, mode, data))
		return (FALSE);
	// choose mode from func ptr array
	t_word = temp[pos[0]][pos[1]];
	if (t_word[0] == "<")
	{
		while (new_mode < 13)
		{
			if (ft_strcmp(&t_word[1], data->keyword_array[new_mode]))
				break;
		}
		if (new_mode == 13)
			return (FALSE);
		else
			data->func_ptr_array[new_mode](start, end, new_mode, main, data);
	}

	if (mode == 2)
	{
		get_tuple(*start, &main->obj->loc);
		return (TRUE);
	}
	while (**temp < end)
	{

		**temp++;
	}
	if (mode == 1)
	{
	}
}

int	*find_end(t_data *data, int *pos, int *p_end, int mode)
{
	while (pos[0] < p_end[0])
	{
		if (data->storage[pos[0]][pos[1]] == 0)
			pos[1] = 0;
		while (pos[1] < p_end[1])
		{
			if (data->storage[pos[0]][pos[1]][1] == '<')
			{
				if (data->storage[pos[0]][pos[1]][2] == '/')
				{
					if (ft_strcmp(&data->storage[pos[0]][pos[1]][2], data->keyword_array[mode]))
						return (TRUE);
				}
				else if (ft_strcmp(&data->storage[pos[0]][pos[1]][1], data->keyword_array[mode]))
					return (FALSE);
			}
			pos[1]++;
		}
		pos[0]++;
	}
	return (FALSE);

}
int	wordfinder(t_main *main, t_data *data, int *pos, int *parent_end, int mode)
{
	int	end[2];

	//memset(end, 0, (sizeof(int) * 3));
	end[0] = pos[0];
	end[1] = pos[1];
	if (!find_end(data, end, parent_end, mode))
		return (FALSE);
	while (pos[0] < p_end[0])
	{
		if (data->storage[pos[0]][pos[1]] == 0)
			pos[1] = 0;
		while (pos[1] < p_end[1])
		{
			pos[1]++;
		}
		pos[0]++
	}
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
	int		fd_temp;
	char	tmpname[] = "temp_input.xml";
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
	open_file(&fd, tmpname);
	close_file(fd_temp);
	storage = (char ***)ft_calloc(sizeof(char **), nl + 1);
	storage[nl] = 0;
	index = 0;
	while (get_next_line(fd, &line))
	{
		if (*line)
			storage[index++] = ft_strsplit(line, ' ');
		else
			storage[index++] = 0;
		free(line);
	}
	output->storage = storage;
	output->nl = nl;
	printf("index = %d\n", index);
	return (TRUE);
}

void	xml_end(t_data *data)
{
	char	keywords[12][10] = {"loc", "coi", "up", "rot", "size", "brightness", "type", "is", "transform", "color", "material"};
	int		x, y;

	x = 0;
	while (data->storage[x])
	{
		y = 0;
		while (data->storage[x][y])
		{
			if (!ft_strcmp(data->storage[x][y], "<position>"))
			{
				get_tuple(&data->storage[x][y], &data->object->loc);
			}
			y++;
		}
		x++;
	}
}
