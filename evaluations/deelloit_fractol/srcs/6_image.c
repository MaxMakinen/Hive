/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_image.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 15:34:31 by deelliot          #+#    #+#             */
/*   Updated: 2022/08/26 10:31:19 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	img_pixel_put(int n, int x, int y, t_win *win)
{
	int	pix;

	pix = (y * win->img.length) + (x * win->img.bpp / 8);
	if ((x >= 0 && x < WIDTH) && (y >= 0 && y < HEIGHT))
	{
		if (n == win->max_iter)
		{
			win->img.addr[pix + 0] = 0x00;
			win->img.addr[pix + 1] = 0x00;
			win->img.addr[pix + 2] = 0x00;
		}
		else
		{
			win->img.addr[pix + 0] = win->col_start.r * n;
			win->img.addr[pix + 1] = win->col_start.g * n;
			win->img.addr[pix + 2] = win->col_start.b * n;
		}
	}
}
