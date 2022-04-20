/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:19:33 by mmakinen          #+#    #+#             */
/*   Updated: 2022/04/20 15:45:44 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map *project(t_map *map, t_matrix *matrix)
{
	int	x;
	int	y;
	t_matrix	*temp;

	y = 0;
	while (y < map->y_max)
	{
		x = 0;
		while (x < map->x_max)
		{
			temp = vect_to_matrix(map->coords[y][x].vect);
			mat_mul(rotate_z(0.1), temp);
			map->coords[y][x].vect = *matrix_to_vect(temp);
			x++;
		}
		y++;
	}
	return (map);
}
