/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 13:55:50 by dmalesev          #+#    #+#             */
/*   Updated: 2022/05/03 14:32:48 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_hooks(t_utils *utils)
{
	mlx_hook(utils->win, 2, 1L << 0, &key_down, utils);
	mlx_hook(utils->win, 6, 1L << 6, &mouse_move, utils);
	mlx_hook(utils->win, 5, 1L << 3, &mouse_up, utils);
	mlx_hook(utils->win, 4, 1L << 2, &mouse_down, utils);
	mlx_loop_hook(utils->mlx, &clock, utils);
	if (utils->longest_line >= utils->lines)
		utils->scale = utils->longest_line * 50;
	else
		utils->scale = utils->lines * 50;
}

void	init_sliders(t_utils *u)
{
	u->slid.fov = 0;
	u->slid.elev = 10;
	u->slid.red = 0;
	u->slid.green = 128;
	u->slid.blue = 230;
	u->map_color = combine_channels(u->slid.red, u->slid.green, u->slid.blue);
	u->reference = -1;
}

void	init_proj(t_utils *utils)
{
	utils->proj.z_near = 0.1;
	utils->proj.z_far = 1000;
	utils->proj.fov = 0.001;
	utils->proj.asp_ratio = (float)utils->screen_y / (utils->screen_x / 5 * 4);
	utils->proj.fov_rad = 1 / tan((utils->proj.fov) / 2 / 180 * PI);
}

void	init_values(t_utils *utils)
{
	utils->longest_line = 0;
	utils->color = 0xFFFFFF;
	utils->color_top = 0xFFFFFF;
	utils->dest_color = 0xFFFFFF;
	utils->scale = 2800;
	utils->clock = 0;
	utils->h_point = 0;
	utils->l_point = 0;
	utils->state = 0;
	utils->mlx = NULL;
	utils->win = NULL;
	utils->img.ptr = NULL;
	utils->img2.ptr = NULL;
	utils->map_x = 0;
	utils->map_y = 0;
	utils->screen_x = SCREEN_X;
	utils->screen_y = SCREEN_Y;
	utils->mouse_x = 0;
	utils->mouse_y = 0;
}

void	init(t_utils *utils)
{
	utils->move_x = 0;
	utils->move_y = 0;
	utils->rot.alpha = 30;
	utils->rot.beta = 315;
	utils->rot.gamma = 0;
	utils->perspective = 0;
	init_values(utils);
	init_sliders(utils);
	init_proj(utils);
	init_matrix(&utils->pmatrix);
	init_matrix(&utils->rmatrix_x);
	init_matrix(&utils->rmatrix_y);
	init_matrix(&utils->rmatrix_z);
	init_pmatrix(utils);
	init_rmatrix_x(utils);
	init_rmatrix_y(utils);
	init_rmatrix_z(utils);
}
