/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_controller.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:43:31 by dpalacio          #+#    #+#             */
/*   Updated: 2022/04/28 19:17:09 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//Closes fdf cleanly and frees all allocated memory
int	exit_fdf(int key, t_data *data)
{
	int	y;

	y = 0;
	if (key == 53)
	{
		if (data->color_matrix && data->matrix)
		{
			while (y <= data->map_height)
			{
				free(data->color_matrix[y]);
				free(data->matrix[y]);
				y++;
			}
			free(data->color_matrix);
			free(data->matrix);
		}
		exit(0);
	}
	return (1);
}

//Moves the "camera" up, left, down and right with W,A,S,D keys
int	pan_view(int key, t_data *data)
{
	if (key == 13)
		data->y_off += data->zoom + 5;
	if (key == 0)
		data->x_off += data->zoom + 5;
	if (key == 1)
		data->y_off -= data->zoom + 5;
	if (key == 2)
		data->x_off -= data->zoom + 5;
	if (key == 49)
	{
		data->iso_angle = 0.9;
		offset_draw(data);
		if (data->view == 1)
			data->x_off += data->zoom * data->map_width / 2;
	}
	draw(data);
	return (1);
}

//Changes between "top-down" and "perspective view" with V key
int	switch_view(int key, t_data *data)
{
	if (key == 9)
	{
		offset_draw(data);
		if (data->zoom <= 1 && data->view == 0)
			data->zoom = 2;
		data->view++;
		if (data->view > 1)
			data->view = 0;
		if (data->view == 1)
		{
			data->iso_angle = 0.9;
			data->x_off += data->zoom * data->map_width / 2;
		}
		if (data->view == 0)
			data->rot_angle = 0;
		draw(data);
	}
	return (1);
}

//Modifies the map altitude of each non-zero point with R,F keys
int	change_height(int key, t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (key == 15 || key == 3)
	{
		while (y < data->map_height)
		{
			while (x < data->map_width)
			{
				if (data->matrix[y][x] != 0 && key == 15
					&& data->matrix[y][x] < 5000000)
					data->matrix[y][x] *= 1.25;
				else if (data->matrix[y][x] != 0 && key == 3)
					data->matrix[y][x] /= 1.25;
				choose_color(data, x, y);
				x++;
			}
			x = 0;
			y++;
		}
	}
	draw(data);
	return (1);
}

//Modifies de viewing angle of "Perspective" view with Q,E,T,G keys
int	change_angle(int key, t_data *data)
{
	if (key == 17 && data->view == 1 && data->iso_angle > 0.01)
	{
			data->iso_angle -= 0.01;
			data->y_off += 5;
	}
	if (key == 5 && data->view == 1 && data->iso_angle < 1)
	{
		data->iso_angle += 0.01;
		data->y_off -= 5;
	}
	if (key == 12 && data->view == 1 && data->rot_angle > -0.4)
	{
		data->rot_angle -= 0.01;
		data->x_off -= 5;
	}
	if (key == 14 && data->view == 1 && data->rot_angle < 0.2)
	{
		data->rot_angle += 0.01;
		data->x_off += 5;
	}
	draw(data);
	return (1);
}
