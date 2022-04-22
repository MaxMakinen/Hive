/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:43:43 by mmakinen          #+#    #+#             */
/*   Updated: 2022/04/21 19:42:03 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_abs(int num)
{
	if (num < -2147483648)
		return (2147483647);
	if (num < 0)
		num = -num;
	return (num);
}

int handle_keypress(int keysym, t_data *data)
{
	if (keysym == 113)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	printf("Keypress: %d\n", keysym);
	return (0);
}
/*
int handle_keyrelease(int keysym, t_data *data)
{
	printf("Keyrelease: %d\n", keysym);
	return (0);
}
*/
t_matrix	*mat_mul(t_matrix *matrix, t_matrix *vector)
{
	int		rows;
	int		cols;
	int		index;
	int		len;
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

