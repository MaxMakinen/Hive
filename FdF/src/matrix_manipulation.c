/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_manipulation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:43:43 by mmakinen          #+#    #+#             */
/*   Updated: 2022/05/05 13:48:20 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	check_input(t_matrix *mat1, t_matrix *mat2)
{
	if (mat1->y_max != mat2->x_max)
		ft_error("matmul error: rows != cols\n");
}

t_matrix	*mat_mul(t_matrix *mat1, t_matrix *mat2, t_matrix *result)
{
	int			rows;
	int			cols;
	int			index;
	float		sum;

	check_input(mat1, mat2);
	rows = 0;
	while (rows < mat1->y_max)
	{
		cols = 0;
		while (cols < mat2->x_max)
		{
			index = 0;
			sum = 0;
			while (index < mat2->x_max)
			{
				sum += mat1->m[rows][index] * mat2->m[index][cols];
				index++;
			}
			result->m[rows][cols++] += sum;
		}
		rows++;
	}
	return (result);
}
