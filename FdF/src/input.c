/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 10:30:27 by mmakinen          #+#    #+#             */
/*   Updated: 2022/05/05 14:32:20 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
//#define DISTANCE 38

/*
 * Code realloc for easier array shape changes?
 * Need new version of splitstr in order to extract info like wordcount?
 * Make libft versions of ft_openfd and ft_closefd,
 * add options for opening choices.
 * Enum?
 */

void	count_elems(char *filename, int	*fd, t_map *map)
{
	char	check;
	char	previous;
	int		rows;
	int		len;

	rows = 0;
	len = 0;
	previous = 0;
	*fd = ft_openfd(filename, fd);
	while (read(*fd, &check, 1))
	{
		if ((check == ' ' || check == '\n') && previous != ' ' && rows == 0)
			len++;
		if (check == '\n')
			rows++;
		previous = check;
	}
	if (previous != '\n')
		rows++;
	map->x_max = len;
	map->y_max = rows;
	map->zoom = len;
	if (rows > len)
		map->zoom = rows;
	ft_closefd(*fd);
}

void	import_color(char **num, t_map *map, t_intvec pos)
{
	if (num[1])
	{
		if (!ft_isnumber(num[1], 16))
			ft_error(ERR_INPUT_READ);
		map->coords[pos.y][pos.x].color = int_rgb(ft_atoi(num[1]));
	}
	else
	{
		if (map->coords[pos.y][pos.x].vect.z > 0)
			map->coords[pos.y][pos.x].color = int_rgb(RED_PIXEL);
		else if (map->coords[pos.y][pos.x].vect.z < 0)
			map->coords[pos.y][pos.x].color = int_rgb(GREEN_PIXEL);
		else if (map->coords[pos.y][pos.x].vect.z == 0)
			map->coords[pos.y][pos.x].color = int_rgb(BLUE_PIXEL);
	}
}

void	get_values(char **num, t_map *map, t_intvec pos)
{
	if (!num)
		ft_error(ERR_INPUT_READ);
	if (!ft_isnumber(num[0], 10))
		ft_error(ERR_INPUT_READ);
	map->coords[pos.y][pos.x].vect.z = ft_atoi(num[0]);
	map->coords[pos.y][pos.x].vect.x = pos.x;
	map->coords[pos.y][pos.x].vect.y = pos.y;
	map->coords[pos.y][pos.x].visible = 1;
	if (map->coords[pos.y][pos.x].vect.z > map->z_max)
		map->z_max = map->coords[pos.y][pos.x].vect.z;
	if (map->coords[pos.y][pos.x].vect.z < map->z_min)
		map->z_min = map->coords[pos.y][pos.x].vect.z;
}

void	disect(char **temp, t_map *map, t_intvec pos)
{
	char	**num;

	while (temp[pos.x])
	{
		num = ft_strsplit(temp[pos.x], ',');
		get_values(num, map, pos);
		import_color(num, map, pos);
		ft_arrfree(num);
		pos.x++;
	}
}

t_map	*input(char *filename, t_map *map)
{
	char		**temp;
	char		*line;
	int			fd;
	t_intvec	pos;

	pos.y = 0;
	count_elems(filename, &fd, map);
	ft_openfd(filename, &fd);
	prep_map(map);
	while (get_next_line(fd, &line))
	{
		pos.x = 0;
		temp = ft_strsplit(line, ' ');
		disect(temp, map, pos);
		pos.y++;
		free(line);
		ft_arrfree(temp);
	}
	ft_closefd(fd);
	if (map->z_max > map->zoom)
		map->zoom = map->z_max + 10;
	return (map);
}
