/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:26:01 by mmakinen          #+#    #+#             */
/*   Updated: 2022/05/02 16:11:49 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void rot_topleft(t_data *data)
{
	pitch(data, -0.05f);
	yaw(data, 0.05f);
}

void rot_topright(t_data *data)
{
	pitch(data, -0.05f);
	yaw(data, -0.05f);
}

void rot_bottomleft(t_data *data)
{
	pitch(data, 0.05f);
	yaw(data, 0.05f);
}

void rot_bottomright(t_data *data)
{
	pitch(data, 0.05f);
	yaw(data, -0.05f);
}

void spin(t_data *data)
{
	pitch(data, 0.02f);
	yaw(data, 0.04f);
	roll(data, 0.04f);
}
