/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:32:59 by mmakinen          #+#    #+#             */
/*   Updated: 2022/04/21 15:11:43 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


t_matrix *vec_to_matrix(t_vector *vector, t_matrix *matrix)
{

	matrix->m[0][0] = vector->x;
	matrix->m[1][0] = vector->y;
	matrix->m[2][0] = vector->z;
	matrix->m[3][0] = vector->w;
	return (matrix);
}

t_vector	*matrix_to_vec(t_matrix *matrix, t_vector *vector)
{
	vector->x = matrix->m[0][0];
	vector->y = matrix->m[1][0];
	vector->z = matrix->m[2][0];
	vector->w = matrix->m[3][0];
	return (vector);
}

t_matrix	*prep_rotate_z(float angle)
{
	t_matrix	*matrix;

	matrix = prep_matrix(4,4);
	matrix->m[0][0] = cos(angle);
	matrix->m[0][1] = -sin(angle);
	matrix->m[1][0] = sin(angle);
	matrix->m[1][1] = cos(angle);
	matrix->m[2][2] = 1.0f;
	matrix->m[3][3] = 1.0f;
	return (matrix);
}

t_matrix	*prep_rotate_x(float angle)
{
	t_matrix	*matrix;
	float x[3] = {1.0f,0.0f,0.0f};
	float y[3] = {0.0f, cos(angle), -sin(angle)};
	float z[3] = {0.0f, sin(angle), cos(angle)};

	matrix = prep_matrix(4,4);
	matrix->m[0] = x;
	matrix->m[1] = y;
	matrix->m[2] = z;
	return (matrix);
}

t_matrix	*prep_rotate_y(float angle)
{
	t_matrix	*matrix;
	float	x[3] = {cos(angle), 0.0f, sin(angle)};
	float	y[3] = {0.0f, 1.0f, 0.0f};
	float	z[3] = {-sin(angle), 0.0f, cos(angle)};

	matrix = prep_matrix(4,4);
	matrix->m[0] = x;
	matrix->m[1] = y;
	matrix->m[2] = z;
	return (matrix);
}

t_matrix	*prep_matrix(int x_max, int y_max)
{
	int		x;
	float	*temp;
	t_matrix *matrix;

	matrix = malloc(sizeof(matrix));
	matrix->m = (float **)ft_calloc(y_max, sizeof(float *));
	matrix->pool = (float *)ft_calloc(y_max * x_max, sizeof(float *));
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

t_matrix	*prep_projection_matrix(void)
{
	float	fNear = 0.1f;
	float	fFar = 1000.0f;
	float	fFov = 90.0f;
	float	fAspectRatio = (float)WINDOW_HEIGHT / (float)WINDOW_WIDTH;
	float	fFovRad = 1.0f / tan(fFov * 0.5f / 180.0f * 3.14159f);
	t_matrix	*mat_proj;

	mat_proj = prep_matrix(4,4);
	mat_proj->m[0][0] = fAspectRatio * fFovRad;
	mat_proj->m[1][1] = fFovRad;
	mat_proj->m[2][2] = fFar / (fFar - fNear);
	mat_proj->m[2][3] = (-fFar * fNear) / (fFar - fNear);
	mat_proj->m[3][2] = 1.0f;
	mat_proj->m[3][3] = 0.0f;
	return (mat_proj);
}

t_vector	*mult_matrix_vec(t_vector *src, t_vector *dst, t_matrix *m)
{
	dst->x = src->x * m->m[0][0] + src->y * m->m[0][1] + src->z * m->m[0][2] + m->m[0][3];
	dst->y = src->x * m->m[1][0] + src->y * m->m[1][1] + src->z * m->m[1][2] + m->m[1][3];
	dst->z = src->x * m->m[2][0] + src->y * m->m[2][1] + src->z * m->m[2][2] + m->m[2][3];
	float w = src->x * m->m[3][0] + src->y * m->m[3][1] + src->z * m->m[3][2] + m->m[3][3];
	 

	if (w != 0)
	{
		dst->x /= w;
		dst->y /= w;
		dst->z /= w;
	}
	return (dst);
}
