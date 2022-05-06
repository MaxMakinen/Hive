/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:32:59 by mmakinen          #+#    #+#             */
/*   Updated: 2022/05/06 09:52:39 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_matrix	*vec_to_matrix(t_vector *vector, t_matrix *matrix)
{
	matrix->m[0][0] = vector->x;
	matrix->m[1][0] = vector->y;
	matrix->m[2][0] = vector->z;
	return (matrix);
}

t_vector	*matrix_to_vec(t_matrix *matrix, t_vector *vector)
{
	vector->x = matrix->m[0][0];
	vector->y = matrix->m[1][0];
	vector->z = matrix->m[2][0];
	return (vector);
}

t_matrix	*prep_matrix(int x_max, int y_max)
{
	int			x;
	float		*temp;
	t_matrix	*matrix;

	matrix = (t_matrix *)malloc(sizeof(t_matrix));
	if (!matrix)
		ft_error("prep_matrix malloc error");
	matrix->m = (float **)ft_calloc(y_max, sizeof(float *));
	matrix->pool = (float *)ft_calloc(y_max * x_max, sizeof(float));
	temp = matrix->pool;
	x = 0;
	while (x < x_max)
	{
		*(matrix->m + x) = temp;
		temp += x_max;
		x++;
	}
	matrix->x_max = x_max;
	matrix->y_max = y_max;
	return (matrix);
}

t_matrix	*prep_projection_matrix(t_map *map, t_matrix *matrix)
{
	float	aspect_ratio;
	float	fov_rad;

	aspect_ratio = (float)WINDOW_HEIGHT / (float)WINDOW_WIDTH;
	fov_rad = 1.0f / tan(map->f_fov * 0.5f / 180.0f * 3.14159f);
	matrix->m[0][0] = aspect_ratio * fov_rad;
	matrix->m[1][1] = fov_rad;
	matrix->m[2][2] = map->f_far / (map->f_far - map->f_near);
	matrix->m[2][3] = (-map->f_far * map->f_near) / (map->f_far - map->f_near);
	matrix->m[3][2] = 1.0f;
	matrix->m[3][3] = 0.0f;
	return (matrix);
}

t_vector	*mult_matrix_vec(t_vector *src, t_vector *dst, t_matrix *m)
{
	float	w;

	dst->x = src->x * m->m[0][0] + src->y * m->m[0][1] + src->z * m->m[0][2] \
			+ m->m[0][3];
	dst->y = src->x * m->m[1][0] + src->y * m->m[1][1] + src->z * m->m[1][2] \
			+ m->m[1][3];
	dst->z = src->x * m->m[2][0] + src->y * m->m[2][1] + src->z * m->m[2][2] \
			+ m->m[2][3];
	w = src->x * m->m[3][0] + src->y * m->m[3][1] + src->z * m->m[3][2] \
			+ m->m[3][3];
	if (w != 0.0f)
	{
		dst->x /= w;
		dst->y /= w;
		dst->z /= w;
	}
	return (dst);
}
