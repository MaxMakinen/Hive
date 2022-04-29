/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 18:04:10 by dpalacio          #+#    #+#             */
/*   Updated: 2022/04/28 17:24:16 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_width(char *line, t_data *data);
void	create_matrix(t_data *data);
void	fill_matrix(t_data *data, int fd);
void	fill_line(t_data *data, char **line_arr, int y);

//Opens and reads the file, saving it.
void	read_file(char *file, t_data *data)
{
	char	*line;
	int		fd;

	data->map_height = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_print("Error (0): Failed to open file", data);
	while (get_next_line(fd, &line) == 1)
	{
		get_width(line, data);
		data->map_height += 1;
		free(line);
	}
	close(fd);
	create_matrix(data);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_print("Error (5): Failed to open during fill_matrix()", data);
	fill_matrix(data, fd);
	close(fd);
}

//Gets the width (in number of elements) of the map given
void	get_width(char *line, t_data *data)
{
	int	i;
	int	x;
	int	in;

	i = -1;
	x = 0;
	in = 0;
	while (line[++i])
	{
		if (in && line[i] == ' ')
			in = 0;
		if (!in && line[i] != ' ')
		{
			in = 1;
			x++;
		}
	}
	if (data->map_height == 0)
		data->map_width = x;
	else if (data->map_width != x)
		error_print("Error (1): Map is not rectangular", data);
	if (data->map_width == 0)
		error_print("Error (2): Empty file", data);
}

//Allocates a matrix for colors and another for the value (altitude)
//Each element of the matrices represents a point (x,y)
void	create_matrix(t_data *data)
{
	int	i;

	i = 0;
	data->matrix = (float **)ft_memalloc((data->map_height + 1)
			* sizeof(int *));
	if (!data->matrix)
		error_print("Error (3): Failed to allocate matrix", data);
	data->matrix[data->map_height] = NULL;
	data->color_matrix
		= (int **)ft_memalloc((data->map_height + 1) * sizeof(char *));
	if (!data->color_matrix)
		error_print("Error (4): Failed to allocate color matrix", data);
	data->color_matrix[data->map_height] = NULL;
	while (i <= data->map_height)
	{
		data->matrix[i] = (float *)ft_memalloc((data->map_width) * sizeof(int));
		if (!data->matrix[i])
			error_print("Error (3): Failed to allocate matrix", data);
		data->color_matrix[i]
			= (int *)ft_memalloc((data->map_width) * sizeof(int));
		if (!data->color_matrix[i])
			error_print("Error (4): Failed to allocate color matrix", data);
		i++;
	}
}

//Goes through every line of the matrices filling it with the map values
void	fill_matrix(t_data *data, int fd)
{
	char	**line_arr;
	char	*line;
	int		y;
	int		i;

	y = 0;
	i = 0;
	while (get_next_line(fd, &line) == 1)
	{
		line_arr = ft_strsplit(line, ' ');
		fill_line(data, line_arr, y);
		while (i < data->map_width)
		{
			free(line_arr[i]);
			i++;
		}
		i = 0;
		free(line_arr);
		free(line);
		y++;
	}
}

//Fill each line of both matrices
void	fill_line(t_data *data, char **line_arr, int y)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (line_arr[x] != '\0')
	{
		data->matrix[y][x] = ft_atoi(line_arr[x]);
		while (line_arr[x][i] != 'x' && line_arr[x][i] != '\0')
			i++;
		if (line_arr[x][i++] == 'x')
			data->color_matrix[y][x] = ft_atoi_base(&line_arr[x][i], 16);
		else
		{
			if (data->matrix[y][x] == 0)
				data->color_matrix[y][x] = WHITE;
			else if (data->matrix[y][x] > 0)
				data->color_matrix[y][x] = RED;
			else
				data->color_matrix[y][x] = BLUE;
			choose_color(data, x, y);
		}
		i = 0;
		x++;
	}
}
