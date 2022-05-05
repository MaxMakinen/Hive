/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:19:33 by mmakinen          #+#    #+#             */
/*   Updated: 2022/05/05 09:52:36 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	prep_rotate(t_map *map)
{
	prep_rotate_x(map->rot_x, map->anglex);
	prep_rotate_y(map->rot_y, map->angley);
	prep_rotate_z(map->rot_z, map->anglez);
}

void	apply_rotation(t_map *map, t_vector *temp)
{
	t_vector	tempx;
	t_vector	tempxz;

	vec_adjust(temp, &map->offset);
	mult_matrix_vec(temp, &tempx, map->rot_x);
	mult_matrix_vec(&tempx, &tempxz, map->rot_z);
	mult_matrix_vec(&tempxz, temp, map->rot_y);
}

void	center_view(t_map *map, int y, int x)
{
	map->vec[y][x].vect.x += 1.0f;
	map->vec[y][x].vect.y += 1.0f;
	map->vec[y][x].vect.z *= -1;
	map->vec[y][x].vect.x *= 0.5f * (float)WINDOW_WIDTH;
	map->vec[y][x].vect.y *= 0.5f * (float)WINDOW_HEIGHT;
	map->vec[y][x].color = map->coords[y][x].color;
	map->vec[y][x].visible = map->coords[y][x].visible;
}

t_map	*project(t_map *map, t_matrix *matrix)
{
	int			x;
	int			y;
	t_vector	temp;

	prep_rotate(map);
	y = 0;
	while (y < map->y_max)
	{
		x = 0;
		while (x < map->x_max)
		{
			temp = map->coords[y][x].vect;
			temp.z = -temp.z;
			apply_rotation(map, &temp);
			temp.z += map->zoom;
			map->vec[y][x].vect = *mult_matrix_vec(&temp, \
					&map->vec[y][x].vect, matrix);
			center_view(map, y, x);
			x++;
		}
		y++;
	}
	return (map);
}
