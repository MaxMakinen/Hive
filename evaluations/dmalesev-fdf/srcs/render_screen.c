/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_screen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:12:14 by dmalesev          #+#    #+#             */
/*   Updated: 2022/05/03 14:18:15 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_params(t_utils *utils)
{
	char	*str;

	mlx_string_put(utils->mlx, utils->win, 50, 50, 0x00FF45, "x:");
	mlx_string_put(utils->mlx, utils->win, 50, 70, 0x00FF45, "y:");
	mlx_string_put(utils->mlx, utils->win, 90, 130, 0xFF6666, "Red:");
	mlx_string_put(utils->mlx, utils->win, 90, 180, 0x66FF66, "Green:");
	mlx_string_put(utils->mlx, utils->win, 90, 230, 0x6666FF, "Blue:");
	mlx_string_put(utils->mlx, utils->win, 90, 280, 0x00FF45, "Elevation:");
	mlx_string_put(utils->mlx, utils->win, 50, 350, 0x00FF45,
		"Change projection [Space]");
	mlx_string_put(utils->mlx, utils->win, 50, 370, 0x00FF45,
		"Toggle ref. points [.]");
	str = ft_itoa(utils->rot.beta);
	mlx_string_put(utils->mlx, utils->win, 70, 50, 0x00FF45, str);
	free(str);
	str = ft_itoa(utils->rot.alpha);
	mlx_string_put(utils->mlx, utils->win, 70, 70, 0x00FF45, str);
	free(str);
	mlx_string_put(utils->mlx, utils->win, 50, 90, 0x00FF45, "Zoom:");
	str = ft_itoa(utils->scale);
	mlx_string_put(utils->mlx, utils->win, 110, 90, 0x00FF45, str);
	free(str);
}

void	render_screen(t_utils *u)
{
	u->draw_img = &u->img;
	ft_clear_img(u);
	draw_quadrilateral(u, &(t_quadril){0, 0, u->img.max_x - 1, 0,
		u->img.max_x - 1, u->img.max_y - 1, 0, u->img.max_y - 1}, 0xFFDD45);
	iter_coords(u);
	mlx_put_image_to_window(u->mlx, u->win, u->img.ptr, u->screen_x / 5, 0);
	u->draw_img = &u->img2;
	ft_clear_img(u);
	draw_quadrilateral(u, &(t_quadril){0, 0, u->img2.max_x - 1, 0,
		u->img2.max_x - 1, u->img2.max_y - 1, 0, u->img2.max_y - 1}, 0xFFDD45);
	draw_sliders(u);
	mlx_put_image_to_window(u->mlx, u->win, u->img2.ptr, 0, 0);
	draw_params(u);
}

int	clock(void *param)
{
	t_utils	*utils;

	utils = param;
	if (utils->state >= 1)
		render_screen(utils);
	if (utils->clock == 100)
		utils->clock = 0;
	else
		utils->clock += 1;
	return (0);
}
