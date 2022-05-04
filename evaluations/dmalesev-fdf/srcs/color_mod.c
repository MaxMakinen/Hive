/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_mod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:54:41 by dmalesev          #+#    #+#             */
/*   Updated: 2022/05/03 14:55:00 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	combine_channels(int red, int green, int blue)
{
	int	color;

	color = 0;
	color += red << 16;
	color += green << 8;
	color += blue;
	return (color);
}

void	seperate_channels(int color, int *red, int *green, int *blue)
{
	*red = (color & 0xFF0000) >> 16;
	*green = (color & 0x00FF00) >> 8;
	*blue = (color & 0x0000FF);
}

int	mix_colors(int color, int color2, float percent)
{
	t_cols	chn[2];

	if (percent == 0)
		return (color);
	seperate_channels(color, &chn[0].r, &chn[0].g, &chn[0].b);
	seperate_channels(color2, &chn[1].r, &chn[1].g, &chn[1].b);
	if (chn[0].r <= chn[1].r)
		chn[0].r = abs(chn[0].r - chn[1].r) * percent + chn[0].r;
	else
		chn[0].r = abs(chn[0].r - chn[1].r) * (1.0 - percent) + chn[1].r;
	if (chn[0].g <= chn[1].g)
		chn[0].g = abs(chn[0].g - chn[1].g) * percent + chn[0].g;
	else
		chn[0].g = abs(chn[0].g - chn[1].g) * (1.0 - percent) + chn[1].g;
	if (chn[0].b <= chn[1].b)
		chn[0].b = abs(chn[0].b - chn[1].b) * percent + chn[0].b;
	else
		chn[0].b = abs(chn[0].b - chn[1].b) * (1.0 - percent) + chn[1].b;
	color = combine_channels(chn[0].r, chn[0].g, chn[0].b);
	return (color);
}
