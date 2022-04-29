/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_gradient.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:36:05 by dpalacio          #+#    #+#             */
/*   Updated: 2022/04/28 16:42:07 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	red_gradient(int color0, int color1, int steps);
static int	green_gradient(int color0, int color1, int steps);
static int	blue_gradient(int color0, int color1, int steps);

//Gets the RGB values of each point in a line based on starting and ending color
int	color_gradient(int color0, int color1, int steps)
{
	int	red;
	int	green;
	int	blue;

	red = red_gradient(color0, color1, steps);
	green = green_gradient(color0, color1, steps);
	blue = blue_gradient(color0, color1, steps);
	return (rgb_to_int(red, green, blue));
}

static int	red_gradient(int color0, int color1, int steps)
{
	int	red;
	int	red0;
	int	red1;

	if (steps < 1)
			steps = 1;
	red0 = int_to_red(color0);
	red1 = int_to_red(color1);
	if (red0 == red1)
		red = red0;
	if (red0 < red1)
		red = (red1 - red0) / steps + red0;
	if (red0 > red1)
		red = red0 - (red0 - red1) / steps;
	return (red);
}

static int	green_gradient(int color0, int color1, int steps)
{
	int	green;
	int	green0;
	int	green1;

	if (steps < 1)
			steps = 1;
	green0 = int_to_green(color0);
	green1 = int_to_green(color1);
	if (green0 == green1)
		green = green0;
	if (green0 < green1)
		green = (green1 - green0) / steps + green0;
	if (green0 > green1)
		green = green0 - (green0 - green1) / steps;
	return (green);
}

static int	blue_gradient(int color0, int color1, int steps)
{
	int	blue;
	int	blue0;
	int	blue1;

	if (steps < 1)
			steps = 1;
	blue0 = int_to_blue(color0);
	blue1 = int_to_blue(color1);
	if (blue0 == blue1)
		blue = blue0;
	if (blue0 < blue1)
		blue = (blue1 - blue0) / steps + blue0;
	if (blue0 > blue1)
		blue = blue0 - (blue0 - blue1) / steps;
	return (blue);
}
