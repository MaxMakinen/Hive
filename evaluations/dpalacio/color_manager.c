/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:43:09 by dpalacio          #+#    #+#             */
/*   Updated: 2022/04/28 16:39:03 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	geo_color(t_data *data, int x, int y);
static void	abstract_color(t_data *data, int x, int y);
static void	basic_color(t_data *data, int x, int y);
static void	const_color(t_data *data, int x, int y);

//Sets the color scheme used on the drawing
void	choose_color(t_data *data, int x, int y)
{
	if (data->color_scheme == 0)
		basic_color(data, x, y);
	if (data->color_scheme == 1)
		geo_color(data, x, y);
	if (data->color_scheme == 2)
		abstract_color(data, x, y);
	if (data->color_scheme == 3)
		const_color(data, x, y);
}

static void	basic_color(t_data *data, int x, int y)
{
	if (data->matrix[y][x] <= -50)
		data->color_matrix[y][x] = WHITE;
	else if (data->matrix[y][x] > -50 && data->matrix[y][x] <= -20)
		data->color_matrix[y][x] = GREEN;
	else if (data->matrix[y][x] > -20 && data->matrix[y][x] <= 0)
		data->color_matrix[y][x] = CYAN;
	else if (data->matrix[y][x] > 0 && data->matrix[y][x] <= 20)
		data->color_matrix[y][x] = BLUE;
	else if (data->matrix[y][x] > 20 && data->matrix[y][x] <= 50)
		data->color_matrix[y][x] = YELLOW;
	else if (data->matrix[y][x] > 50 && data->matrix[y][x] <= 80)
		data->color_matrix[y][x] = MAGENTA;
	else if (data->matrix[y][x] > 80)
		data->color_matrix[y][x] = RED;
}

static void	geo_color(t_data *data, int x, int y)
{
	if (data->matrix[y][x] <= -100)
		data->color_matrix[y][x] = 0x02445A;
	else if (data->matrix[y][x] > -100 && data->matrix[y][x] <= -50)
		data->color_matrix[y][x] = 0x046C90;
	else if (data->matrix[y][x] > -50 && data->matrix[y][x] <= -20)
		data->color_matrix[y][x] = 0x0495C7;
	else if (data->matrix[y][x] > -20 && data->matrix[y][x] <= 0)
		data->color_matrix[y][x] = 0x02B6F5;
	else if (data->matrix[y][x] > 0 && data->matrix[y][x] <= 10)
		data->color_matrix[y][x] = 0xB5F989;
	else if (data->matrix[y][x] > 10 && data->matrix[y][x] <= 20)
		data->color_matrix[y][x] = 0x84D855;
	else if (data->matrix[y][x] > 20 && data->matrix[y][x] <= 40)
		data->color_matrix[y][x] = 0x39C135;
	else if (data->matrix[y][x] > 40 && data->matrix[y][x] <= 60)
		data->color_matrix[y][x] = 0xF5AC2E;
	else if (data->matrix[y][x] > 40 && data->matrix[y][x] <= 60)
		data->color_matrix[y][x] = 0xC1800F;
	else if (data->matrix[y][x] > 60 && data->matrix[y][x] <= 100)
		data->color_matrix[y][x] = 0x835404;
	else
		data->color_matrix[y][x] = WHITE;
}

static void	abstract_color(t_data *data, int x, int y)
{
	if (data->matrix[y][x] <= -100)
		data->color_matrix[y][x] = 0xff5488;
	else if (data->matrix[y][x] > -100 && data->matrix[y][x] <= -50)
		data->color_matrix[y][x] = 0x54FCFF;
	else if (data->matrix[y][x] > -50 && data->matrix[y][x] <= -20)
		data->color_matrix[y][x] = 0xF3FF54;
	else if (data->matrix[y][x] > -20 && data->matrix[y][x] <= 0)
		data->color_matrix[y][x] = 0x75FF54;
	else if (data->matrix[y][x] > 0 && data->matrix[y][x] <= 10)
		data->color_matrix[y][x] = 0xB562F1;
	else if (data->matrix[y][x] > 10 && data->matrix[y][x] <= 20)
		data->color_matrix[y][x] = 0xF65DC1;
	else if (data->matrix[y][x] > 20 && data->matrix[y][x] <= 40)
		data->color_matrix[y][x] = 0x54FFB6;
	else if (data->matrix[y][x] > 40 && data->matrix[y][x] <= 60)
		data->color_matrix[y][x] = 0xFFBD54;
	else if (data->matrix[y][x] > 40 && data->matrix[y][x] <= 60)
		data->color_matrix[y][x] = 0x54AEFF;
	else if (data->matrix[y][x] > 60 && data->matrix[y][x] <= 100)
		data->color_matrix[y][x] = 0xF5815E;
	else
		data->color_matrix[y][x] = 0xFF00000;
}

static void	const_color(t_data *data, int x, int y)
{
	if (data->matrix[y][x] <= -10)
		data->color_matrix[y][x] = YELLOW;
	else if (data->matrix[y][x] > -10 && data->matrix[y][x] < 10)
		data->color_matrix[y][x] = 0xFF000000;
	else if (data->matrix[y][x] >= 10)
		data->color_matrix[y][x] = WHITE;
}
