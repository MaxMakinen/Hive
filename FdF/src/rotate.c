/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:21:48 by mmakinen          #+#    #+#             */
/*   Updated: 2022/05/02 14:24:12 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int rotate(t_data *data)
{
	if (data->map->rotate == 1)
	{
		data->map->anglex +=0.01f;
		data->map->angley +=0.02f;
		data->map->anglez +=0.02f;
		project(data->map, data->map->proj);
		render(data);
	}
	return (1);
}

t_matrix	*prep_rotate_z(t_matrix *matrix, float angle)
{

	matrix->m[0][0] = cosf(angle);
	matrix->m[0][1] = -sinf(angle);
	matrix->m[1][0] = sinf(angle);
	matrix->m[1][1] = cosf(angle);
	matrix->m[2][2] = 1.0f;
	return (matrix);
}

t_matrix	*prep_rotate_x(t_matrix *matrix, float angle)
{
	matrix->m[0][0] = 1.0f;
	matrix->m[1][1] = cosf(angle);
	matrix->m[1][2] = -sinf(angle);
	matrix->m[2][1] = sinf(angle);
	matrix->m[2][2] = cosf(angle);
	return (matrix);
}

t_matrix	*prep_rotate_y(t_matrix *matrix, float angle)
{
	matrix->m[0][0] = cosf(angle);
	matrix->m[0][2] = sinf(angle);
	matrix->m[2][0] = -sinf(angle);
	matrix->m[2][2] = cosf(angle);
	matrix->m[1][1] = 1.0f;
	return (matrix);
}
