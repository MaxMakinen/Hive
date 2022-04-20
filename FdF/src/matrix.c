/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:32:59 by mmakinen          #+#    #+#             */
/*   Updated: 2022/04/20 16:49:57 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


t_matrix *vec_to_matrix(t_vector *vector)
{
	t_matrix	*matrix;

	matrix = prep_matrix();
	matrix->matrix[0][0] = (float)vector->x;
	matrix->matrix[1][0] = (float)vector->y;
	matrix->matrix[2][0] = (float)vector->z;
	return (matrix);
}

t_vector	*matrix_to_vec(t_matrix *matrix)
{
	t_vector	*vector;

	vector = malloc(sizeof(t_vector));
	prep_vector(vector);
	vector->x = (int)matrix->matrix[0][0];
	vector->y = (int)matrix->matrix[1][0];
	vector->z = (int)matrix->matrix[2][0];
	free(matrix->matrix);
	free(matrix->pool);
	free(matrix);
	return (vector);
}

t_matrix	*rotate_z(float angle)
{
	t_matrix	*matrix;
	float x[3] = {cos(angle), -sin(angle), 0.0f};
	float y[3] = {sin(angle), cos(angle), 0.0f};
	float z[3] = {0.0f, 0.0f, 1.0f};

	matrix = prep_matrix();
	matrix->matrix[0] = x;
	matrix->matrix[1] = y;
	matrix->matrix[2] = z;
	return (matrix);
}

t_matrix	*rotate_x(float angle)
{
	t_matrix	*matrix;
	float x[3] = {1.0f,0.0f,0.0f};
	float y[3] = {0.0f, cos(angle), -sin(angle)};
	float z[3] = {0.0f, sin(angle), cos(angle)};

	matrix = prep_matrix();
	matrix->matrix[0] = x;
	matrix->matrix[1] = y;
	matrix->matrix[2] = z;
	return (matrix);
}

t_matrix	*rotate_y(float angle)
{
	t_matrix	*matrix;
	float	x[3] = {cos(angle), 0.0f, sin(angle)};
	float	y[3] = {0.0f, 1.0f, 0.0f};
	float	z[3] = {-sin(angle), 0.0f, cos(angle)};

	matrix = prep_matrix();
	matrix->matrix[0] = x;
	matrix->matrix[1] = y;
	matrix->matrix[2] = z;
	return (matrix);
}

t_matrix	*prep_matrix(void)
{
	int		x;
	int		y;
	float	*temp;
	t_matrix *matrix;

	matrix = malloc(sizeof(matrix));
	matrix->matrix = (float **)ft_calloc(4, sizeof(float *));
	temp = matrix->pool;
	x = 0;
	while (x < 4)
	{
//		*(matrix->matrix + x) = temp;
//		temp += 4;
		matrix->matrix[x] = (float *)ft_calloc(4, sizeof(float));
		y = 0;
		while (y < 4)
		{
			matrix->matrix[x][y] = 0.0f;
			y++;
		}
		x++;
	}
	return (matrix);
}

t_matrix	*projection_matrix(void)
{
	float	fNear = 0.1f;
	float	fFar = 1000.0f;
	float	fFov = 90.0f;
	float	fAspectRatio = (float)WINDOW_HEIGHT / (float)WINDOW_WIDTH;
	float	fFovRad = 1.0f / tan(fFov * 0.5f / 180.0f * 3.14159f);
	t_matrix	*mat_proj;

	mat_proj = prep_matrix();
	mat_proj->matrix[0][0] = fAspectRatio * fFovRad;
	mat_proj->matrix[1][1] = fFovRad;
	mat_proj->matrix[2][2] = fFar / (fFar - fNear);
	mat_proj->matrix[3][2] = (-fFar *fNear) / (fFar - fNear);
	mat_proj->matrix[2][3] = 1.0f;
	mat_proj->matrix[3][3] = 0.0f;
	return (mat_proj);
}
