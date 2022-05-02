/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_manipulation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:43:43 by mmakinen          #+#    #+#             */
/*   Updated: 2022/05/02 15:12:14 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"



t_matrix	*mat_mul(t_matrix *matrix, t_matrix *vector)
{
	int		rows;
	int		cols;
	int		index;
	float		sum;
	t_matrix	*result;

	rows = 0;
	if (matrix->y_max != vector->x_max)
	{
		printf("matmul error: rows != cols\n");
		exit(1);
	}
	result = prep_matrix(matrix->x_max, matrix->y_max);
	while (rows < matrix->y_max)
	{
		cols = 0;
		while (cols < vector->x_max)
		{
			index = 0;
			sum = 0;
			while (index < vector->x_max)
			{
				sum += matrix->m[rows][index] * vector->m[index][cols];
				index++;
			}
			result->m[rows][cols] += sum;
			cols++;
		}
		rows++;
	}
	return (result);
}

