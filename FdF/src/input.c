/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 10:30:27 by mmakinen          #+#    #+#             */
/*   Updated: 2022/05/03 10:09:00 by mmakinen         ###   ########.fr       */
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
	previous = 0;
	*fd = openfd(filename, fd);
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
	closefd(*fd);
}

void	prep_map(t_map *map)
{
	int		counter;
	t_coord	*temp_coord;
	t_coord	*temp_vec;

	counter = 0;
	if (!(map->coords = (t_coord **)ft_calloc(map->y_max, sizeof(t_coord *))))
		err_msg(ERR_MALLOC);
	if (!(map->pool = (t_coord *)ft_calloc(map->x_max * map->y_max, sizeof(t_coord))))
		err_msg(ERR_MALLOC);
	if (!(map->vec = (t_coord **)ft_calloc(map->y_max, sizeof(t_coord *))))
		err_msg(ERR_MALLOC);
	if (!(map->pvec = (t_coord *)ft_calloc(map->y_max * map->x_max, sizeof(t_coord))))
		err_msg(ERR_MALLOC);
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

void	err_msg(const char *str)
{
	ft_putendl_fd(str, 2);
	exit(0);
}

int ft_isprefix(const char *str, int base)
{
	int i;

	i = 0;
	if (base == 2 || base == 8 || base == 16)
	{
		if (str[i++] != '0')
			return (FALSE);
		if (base == 2 && (str[i] == 'b' || str[i] == 'B'))
			return (TRUE);
		if (base == 16 && (str[i] == 'x' || str[i] == 'X'))
			return (TRUE);
		if (base == 8)
			return (TRUE);
	}
	return (FALSE);
}

int	ft_isnumber(const char *str, int base)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (base != 10 && !ft_isprefix(&str[i], base))
		return (FALSE);
	if (base == 2 || base == 16)
		i += 2;
	else if (base == 8)
		i += 1;
	else if (base == 10 && (str[i] == '+' || str [i] == '-'))
		i += 1;
	while(str[i])
	{
		if(!ft_isdigit_base(str[i], base))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

t_map	*input (char *filename, t_map *map)
{
	char	**temp;
	char	*line;
	char	**num;
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
			if(!(num = ft_strsplit(temp[x], ',')))
				err_msg(ERR_INPUT_READ);
			if(!ft_isnumber(num[0], 10))
				err_msg(ERR_INPUT_READ);
			map->coords[y][x].vect.z = ft_atoi(num[0]);
			map->coords[y][x].vect.x = x;
			map->coords[y][x].vect.y = y;
			map->coords[y][x].visible = 1;
			if (map->coords[y][x].vect.z > map->z_max)
				map->z_max = map->coords[y][x].vect.z;
			if (map->coords[y][x].vect.z < map->z_min)
				map->z_min = map->coords[y][x].vect.z;
			if (num[1])
			{
				if (!ft_isnumber(num[1], 16))
					err_msg(ERR_INPUT_READ);
				map->coords[y][x].color = int_rgb(ft_atoi(num[1]));
			}
			else
			{
				if (map->coords[y][x].vect.z > 0)
					map->coords[y][x].color = int_rgb(RED_PIXEL);
				else if (map->coords[y][x].vect.z < 0)
					map->coords[y][x].color = int_rgb(GREEN_PIXEL);
				else if (map->coords[y][x].vect.z == 0)
					map->coords[y][x].color = int_rgb(BLUE_PIXEL);
			}
			ft_arrfree(num);
			x++;
			exp++;
		}
		y++;
		free(line);
		ft_arrfree(temp);
	}
	closefd(fd);
	if (map->z_max > map->zoom)
		map->zoom = map->z_max + 10;
	return (map);
}
