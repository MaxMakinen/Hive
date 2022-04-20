/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:32:59 by mmakinen          #+#    #+#             */
/*   Updated: 2022/04/20 13:37:00 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


t_matrix *vec_to_matrix(t_vector *vector)
{
	t_matrix	*matrix;

	matrix = prep_matrix(matrix);
	matrix->matrix[0][0] = vector->x;
	matrix->matrix[1][0] = vector->y;
	matrix->matrix[2][0] = vector->z;
	return (matrix);
}

t_vector	*matrix_to_vec(t_matrix *matrix)
{
	t_vector	*vector;

	vector = malloc(sizeof(t_vector));
	prep_vector(vector);
	vector->x = matrix->matrix[0][0];
	vector->y = matrix->matrix[1][0];
	vector->z = matrix->matrix[2][0];
	return (vector);
}

t_matrix	*rotate_z(int angle)
{
	t_matrix	*matrix;
	int x[3] = {cos(angle), -sin(angle), 0};
	int y[3] = {sin(angle), cos(angle), 0};
	int z[3] = {0, 0, 1};

	prep_matrix(matrix);
	matrix->matrix[0] = x;
	matrix->matrix[1] = y;
	matrix->matrix[2] = z;
	return (matrix);
}

t_matrix	*rotate_x(int angle)
{
	t_matrix	*matrix;
	int x[3] = {1,0,0};
	int y[3] = {0, cos(angle), -sin(angle)};
	int z[3] = {0, sin(angle), cos(angle)};

	matrix = prep_matrix(matrix);
	matrix->matrix[0] = x;
	matrix->matrix[1] = y;
	matrix->matrix[2] = z;
	return (matrix);
}

t_matrix	*rotate_y(int angle)
{
	t_matrix	*matrix;
	int	x[3] = {cos(angle), 0, sin(angle)};
	int	y[3] = {0, 1, 0};
	int	z[3] = {-sin(angle), 0, cos(angle)};

	prep_matrix(matrix);
	matrix->matrix[0] = x;
	matrix->matrix[1] = y;
	matrix->matrix[2] = z;
	return (matrix);
}

t_matrix	*prep_matrix(t_matrix *matrix)
{
	int	x;
	int *temp;

	matrix->matrix = (int **)ft_calloc(4, sizeof(int *));
	matrix->pool = (int *)ft_calloc(16, sizeof(int));
	temp = matrix->pool;
	x = 0;
	while (x < 4)
	{
		*(matrix->matrix + x) = temp;
		temp += 4;
		x++;
	}
	return (matrix);
}

