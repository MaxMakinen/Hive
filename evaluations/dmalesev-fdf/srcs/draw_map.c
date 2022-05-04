/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <dmalesev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:19:03 by dmalesev          #+#    #+#             */
/*   Updated: 2022/05/03 14:30:46 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_sliders(t_utils *utils)
{
	draw_quadrilateral(utils, &(t_quadril){90, 160, 94 + 255, 160,
		94 + 255, 166, 90, 166}, 0xFFFFFF);
	draw_quadrilateral(utils, &(t_quadril){92, 162, 92 + utils->slid.red,
		162, 92 + utils->slid.red, 164, 92, 164}, 0xFF6666);
	draw_quadrilateral(utils, &(t_quadril){90, 210, 94 + 255, 210,
		94 + 255, 216, 90, 216}, 0xFFFFFF);
	draw_quadrilateral(utils, &(t_quadril){92, 212, 92 + utils->slid.green,
		212, 92 + utils->slid.green, 214, 92, 214}, 0x66FF66);
	draw_quadrilateral(utils, &(t_quadril){90, 260, 94 + 255, 260,
		94 + 255, 266, 90, 266}, 0xFFFFFF);
	draw_quadrilateral(utils, &(t_quadril){92, 262, 92 + utils->slid.blue,
		262, 92 + utils->slid.blue, 264, 92, 264}, 0x6666FF);
	draw_quadrilateral(utils, &(t_quadril){90, 310, 294, 310,
		294, 316, 90, 316}, 0xFFDD45);
	ft_pixel_put(utils, 192, 311, 0xFFDD45);
	ft_pixel_put(utils, 192, 315, 0xFFDD45);
	draw_quadrilateral(utils, &(t_quadril){192, 312, 192 + utils->slid.elev,
		312, 192 + utils->slid.elev, 314, 192, 314}, 0xFFDD45);
}

t_3d	get_points(t_utils *utils, float x, float y, float z)
{
	t_3d	point;
	t_3d	point_proj;
	t_3d	point_rot;
	t_3d	point_rot_temp;
	t_3d	point_rot_temp2;

	point.x = x;
	point.y = y;
	point.z = z;
	init_rmatrix_x(utils);
	init_rmatrix_y(utils);
	init_rmatrix_z(utils);
	matrix_multip(&point, &point_rot_temp, &utils->rmatrix_z);
	matrix_multip(&point_rot_temp, &point_rot_temp2, &utils->rmatrix_y);
	matrix_multip(&point_rot_temp2, &point_rot, &utils->rmatrix_x);
	scale_depth(utils, &point_rot.z);
	matrix_multip(&point_rot, &point_proj, &utils->pmatrix);
	scale_into_view(utils, &point_proj.x, &point_proj.y);
	return (point_proj);
}

void	checkerboard_carpet(t_utils *utils)
{
	int		x;
	int		y;
	t_3d	point;

	x = -50;
	y = -50;
	while (x <= 50)
	{
		y = -50;
		while (y <= 50)
		{
			point = get_points(utils, x, 0, y);
			ft_pixel_put(utils, point.x, point.y, 0xFFFFFF);
			y++;
		}
		x++;
	}
}

void	draw_coords(t_utils *u, int x, int y, t_2d *mod)
{
	t_3d	p[2];
	int		mix1;
	int		mix2;
	float	perc;

	p[0] = get_points(u, x - u->lines / 2,
			u->map[x][y] * (float)u->slid.elev / 25,
			y - u->longest_line / 2);
	p[1] = get_points(u, mod->a - u->lines / 2,
			u->map[mod->a][mod->b] * (float)u->slid.elev / 25,
			mod->b - u->longest_line / 2);
	perc = (float)(u->map[x][y] - (u->h_point - u->map_h)) / u->map_h;
	mix1 = mix_colors(u->map_color, u->color_top, perc);
	perc = (float)(u->map[mod->a][mod->b] - (u->h_point - u->map_h)) / u->map_h;
	mix2 = mix_colors(u->map_color, u->color_top, perc);
	if (u->map_h == 0)
		draw_line(u, &(t_line){p[0].x, p[0].y, p[1].x, p[1].y},
			u->map_color, u->map_color);
	else
		draw_line(u, &(t_line){p[0].x, p[0].y, p[1].x, p[1].y}, mix1, mix2);
}

void	iter_coords(t_utils *utils)
{
	int		x;
	int		y;

	x = 0;
	if (utils->reference == 1)
		checkerboard_carpet(utils);
	while (x < utils->lines)
	{
		y = 1;
		while (y <= utils->map[x][0])
		{
			if (y + 1 <= utils->map[x][0])
				draw_coords(utils, x, y, &(t_2d){x, y + 1});
			if (x + 1 < utils->lines && y <= utils->map[x + 1][0])
				draw_coords(utils, x, y, &(t_2d){x + 1, y});
			y++;
		}
		x++;
	}
}
