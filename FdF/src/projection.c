/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:19:33 by mmakinen          #+#    #+#             */
/*   Updated: 2022/04/21 19:20:24 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
/*
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
			temp = mat_mul(rotate_z(angle), temp);
			map->coords[y][x].vect = *matrix_to_vect(temp);
			x++;
		}
		y++;
	}
	return (map);
}
*/
t_square	build_square(t_map *map, t_vector v)
{
	t_square	sq;

	sq.p[0] = map->coords[(int)v.y][(int)v.x].vect;
	sq.p[1] = map->coords[(int)v.y][(int)v.x + 1].vect;
	sq.p[2] = map->coords[((int)v.y) + 1][(int)v.x].vect;
	sq.p[3] = map->coords[((int)v.y) + 1][(int)v.x + 1].vect;
	return (sq);
}

t_mesh	*make_grid(t_map *map)
{
	t_mesh	*grid;
	int		x;
	int		y;
	int		z;
	int		len;

	y = 0;
	z = 0;
	len = map->x_max;
	len *= map->y_max;
	grid = (t_mesh *)malloc(sizeof(t_mesh));
	grid->mesh = (t_square *)malloc(sizeof(t_square) * len);
	len -= (map->y_max + map->x_max - 1);
	grid->len = len;
	while (y < map->y_max)
	{
		x = 0;
		while ((x + 1) < map->x_max)
		{
			grid->mesh[z] = build_square(map, map->coords[y][x].vect);
			z++;
			x++;
		}
		y++;
	}
	return (grid);

}

void	draw_square(t_square sq, t_img *img)
{
	render_line(img, sq.p[0], sq.p[1]);
	render_line(img, sq.p[2], sq.p[3]);
	render_line(img, sq.p[0], sq.p[2]);
	render_line(img, sq.p[1], sq.p[3]);
}

void	draw_grid(t_mesh *grid, t_img *img)
{
	int	x;
	int len;

	x = 0;
	while (x < grid->len)
	{
		draw_square(grid->mesh[x], img);
		x++;
	}
}

