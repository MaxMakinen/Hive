/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 10:30:27 by mmakinen          #+#    #+#             */
/*   Updated: 2022/04/22 11:10:43 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "../libft/libft.h"
#define DISTANCE 38
/*
 * Code realloc for easier array shape changes?
 * Need new version of splitstr in order to extract info like wordcount?
 * Make libft versions of openfd and closefd, add options for opening choices. Enum?
 */

int openfd(char *filename, int *fd)
{
	*fd = open(filename, O_RDONLY);
	if (*fd == -1)
		exit (2);
	return (*fd);
}

int closefd(int fd)
{
	if (close(fd) == -1)
		exit(2);
	return (1);
}

void	count_elems(char *filename, int *fd, t_map *map)
{
	char	check;
	char	previous;
	int		rows;
	int		len;

	rows = 0;
	len = 0;
	*fd = openfd(filename, fd);
	while (read(*fd, &check, 1))
	{
		if ((check == ' ' || check == '\n') && previous != ' ' && rows == 0)
			len++;
		if (check == '\n')
			rows++;
		if (rows == 0)
			previous = check;
	}
	map->x_max = len;
	map->y_max = rows;
	closefd(*fd);
}

void	prep_map(t_map *map)
{
	int		counter;
	t_coord	*temp_coord;
	t_vector	*temp_vec;

	counter = 0;
	map->coords = (t_coord **)ft_calloc(map->y_max, sizeof(t_coord *));
	map->pool = (t_coord *)ft_calloc(map->x_max * map->y_max, sizeof(t_coord));
	map->vec = (t_vector **)ft_calloc(map->y_max, sizeof(t_vector *));
	map->pvec = (t_vector *)ft_calloc(map->y_max * map->x_max, sizeof(t_vector));
	temp_coord = map->pool;
	temp_vec = map->pvec;
	while (counter < map->y_max)
	{
		*(map->coords + counter) = temp_coord;
		temp_coord += map->x_max;
		*(map->vec + counter) = temp_vec;
		temp_vec += map->x_max;
		counter++;
	}
}

t_map	input (char *filename, t_map *map)
{
	char	**temp;
	char	*line;
	int		x;
	int		y;
	int		fd;
	int		exp = 0;

	y = 0;
	count_elems(filename, &fd, map);
	openfd(filename, &fd);
	prep_map(map);
	while (get_next_line(fd, &line))
	{
		x = 0;
		temp = ft_strsplit(line, ' ');
		while (temp[x])
		{
			if (temp[x][0] == 'e')
				map->coords[y][x].invisible = 1;
			map->coords[y][x].vect.z = ft_atoi(temp[x]);
			map->coords[y][x].vect.x = x;
			map->coords[y][x].vect.y = y;
			x++;
			exp++;
		}
		y++;
		free(line);
		ft_arrfree(temp);
	}
	closefd(fd);
	return (*map);
}
