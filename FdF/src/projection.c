/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:19:33 by mmakinen          #+#    #+#             */
/*   Updated: 2022/05/02 14:23:37 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map *project(t_map *map, t_matrix *matrix)
{
	int	x;
	int	y;
	t_vector	temp;
	t_vector	tempx;
	t_vector	tempxz;

	prep_rotate_x(map->rot_x, map->anglex);
	prep_rotate_y(map->rot_y, map->angley);
	prep_rotate_z(map->rot_z, map->anglez);
	y = 0;
	while (y < map->y_max)
	{
		x = 0;
		while (x < map->x_max)
		{
			mult_matrix_vec(&map->coords[y][x].vect, &tempx, map->rot_x);
			mult_matrix_vec(&tempx, &tempxz, map->rot_z);
			mult_matrix_vec(&tempxz, &temp, map->rot_y);
			temp.z += map->zoom;
			map->vec[y][x].vect = *mult_matrix_vec(&temp, &map->vec[y][x].vect, matrix);
			map->vec[y][x].vect.x += 1.0f;
			map->vec[y][x].vect.y += 1.0f;
			map->vec[y][x].vect.x *= 0.5f * (float)WINDOW_WIDTH;
			map->vec[y][x].vect.y *= 0.5f * (float)WINDOW_HEIGHT;
			map->vec[y][x].color = map->coords[y][x].color;
			map->vec[y][x].visible = map->coords[y][x].visible;
			x++;
		}
		y++;
	}
	return (map);
}

t_matrix	*isometric(t_map *map, float xoff)
{
	t_vector	temp;
	t_matrix	*minmax = prep_matrix(2,2);
	int			x;
	int			y;
	y = 0;
	while (y < map->y_max)
	{
		x = 0;
		while (x < map->x_max)
		{
			temp.x = (map->coords[y][x].vect.x * xoff - map->coords[y][x].vect.y * xoff);
			temp.y = ((map->coords[y][x].vect.x + map->coords[y][x].vect.y) * (xoff * 0.5));
			temp.y += (-(map->coords[y][x].vect.z * xoff));
			if (temp.x < minmax->m[0][0])
				minmax->m[0][0] = temp.x;
			if (temp.x > minmax->m[0][1])
				minmax->m[0][1] = temp.x;
			if (temp.y < minmax->m[1][0])
				minmax->m[1][0] = temp.y;
			if (temp.y > minmax->m[1][1])
				minmax->m[1][1] = temp.y;
			map->coords[y][x].vect.x = temp.x;
			map->coords[y][x].vect.y = temp.y;
			x++;
		}
		y++;
	}
	return (minmax);
}
