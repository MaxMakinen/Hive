/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pitch_roll_yaw.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:14:30 by mmakinen          #+#    #+#             */
/*   Updated: 2022/05/02 15:33:08 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	pitch(t_data *data, float angle)
{
	data->map->anglex += angle;
}

void	roll(t_data *data, float angle)
{
	data->map->anglez += angle;
}

void	yaw(t_data *data, float angle)
{
	data->map->angley += angle;
}
