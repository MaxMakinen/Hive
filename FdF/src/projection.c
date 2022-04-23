/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:19:33 by mmakinen          #+#    #+#             */
/*   Updated: 2022/04/23 12:14:36 by mmakinen         ###   ########.fr       */
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
	t_matrix	rotx;
	t_matrix	roty;
	t_matrix	rotz;

	map->angle = 2.5f;
	rotx = *prep_rotate_x(map->angle);
	printf("rotx\n");
	log_matrix(rotx);
	map->angle = 1.0f;
	roty = *prep_rotate_y(map->angle);
	printf("roty\n");
	log_matrix(roty);
	map->angle = 0.0f;
	rotz = *prep_rotate_z(map->angle);
	printf("rotz\n");
	log_matrix(rotz);
	y = 0;
	while (y < map->y_max)
	{
		x = 0;
		while (x < map->x_max)
		{
			temp = map->coords[y][x].vect;
			tempx = map->coords[y][x].vect;
			tempxz = map->coords[y][x].vect;

			tempx = *mult_matrix_vec(&map->coords[y][x].vect, &tempx, &rotx);
			temp = *mult_matrix_vec(&tempx, &tempxz, &rotz);
			//temp = *mult_matrix_vec(&tempxz, &temp, &roty);
			temp.z += map->x_max + 4;
			map->coords[y][x].vect = *mult_matrix_vec(&temp, &map->coords[y][x].vect, matrix);
			map->coords[y][x].vect.x += 1.0f;
			map->coords[y][x].vect.y += 1.0f;
			map->coords[y][x].vect.x *= 0.5f * (float)WINDOW_WIDTH;
			map->coords[y][x].vect.y *= 0.5f * (float)WINDOW_HEIGHT;
			x++;
		}
		y++;
	}
	free(rotx.m);
	free(rotx.pool);
	free(roty.m);
	free(roty.pool);
	free(rotz.m);
	free(rotz.pool);
	return (map);
}

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

t_matrix	*isometric(t_map *map, t_img *img, float xoff)
{
	t_vector	temp;
	t_matrix	*minmax = prep_matrix(2,2);
	//float		origin;
	int			x;
	int			y;
	//float		diff;
/*
	diff = 0.0f;
	a = map->x_max;
	b = map->y_max;
	if (a < b)
		ft_swapint(&a,&b);
	if (a != b)
	{
		a -= b;
		diff = (float)a;
	}
	//xoff = (WINDOW_WIDTH / (map->x_max * 3));
*/	//origin = (WINDOW_WIDTH / 2) * (WINDOW_HEIGHT / 2 + 1) - ((diff / 2) * xoff);
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
