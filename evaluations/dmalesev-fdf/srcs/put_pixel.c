/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <dmalesev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 08:25:53 by dmalesev          #+#    #+#             */
/*   Updated: 2022/05/03 15:18:33 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_clear_img(t_utils *utils)
{
	int	x;
	int	y;

	y = 0;
	while (y < utils->draw_img->max_y)
	{
		x = 0;
		while (x < utils->draw_img->max_x)
		{
			ft_pixel_put(utils, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

void	ft_pixel_put(t_utils *u, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && y >= 0 && x < u->draw_img->max_x && y < u->draw_img->max_y)
	{
		dst = u->draw_img->addr + (y * u->draw_img->line_length
				+ x * (u->draw_img->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}
