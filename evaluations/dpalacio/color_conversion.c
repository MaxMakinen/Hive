/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_conversion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:16:20 by dpalacio          #+#    #+#             */
/*   Updated: 2022/04/28 16:43:43 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//Makes the 3 RGB values a single int
int	rgb_to_int(int red, int green, int blue)
{
	int	color;

	color = blue + (green << 8) + (red << 16);
	return (color);
}

//Gets the RED value of an int color
int	int_to_red(int color)
{
	int	red;

	red = color >> 16;
	return (red);
}

//Gets the GREEN value of an int color
int	int_to_green(int color)
{
	int	green;

	green = (color & 0x00FF00) >> 8;
	return (green);
}

//Gets the BLUE value of an int color
int	int_to_blue(int color)
{
	int	blue;

	blue = (color & 0x0000FF);
	return (blue);
}
