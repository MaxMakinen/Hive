/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:43:43 by mmakinen          #+#    #+#             */
/*   Updated: 2022/04/28 13:41:30 by mmakinen         ###   ########.fr       */
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
	int x = 0;
	if (keysym == 65307)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	if(keysym == 113)
	{
		data->map.anglez -= 0.1f;
	}
	if(keysym == 119)
	{
		data->map.anglex -= 0.1f;
	}
	if(keysym == 101)
	{
		data->map.anglez += 0.1f;
	}
	if(keysym == 115)
	{
		data->map.anglex += 0.1f;
	}
	if(keysym == 97)
	{
		data->map.angley += 0.1f;
	}
	if(keysym == 100)
	{
		data->map.angley -= 0.1f;
	}
	if(keysym == 105)
	{
		data->map.zoom -= 1;
	}
	if(keysym == 107)
	{
		data->map.zoom += 1;
	}
	if(keysym == 108)
	{
		data->map.zoom -= 10;
	}
	if(keysym == 111)
	{
		data->map.zoom += 10;
	}
	if(keysym == 110)
	{
		data->map.fpov -= 10.0f;
		if (data->map.fpov <= 0)
			data->map.fpov = 1.0f;
		free(data->proj);
		data->proj = prep_projection_matrix(&data->map);
	}
	if(keysym == 109)
	{
		data->map.fpov += 10.0f;
		if ((int)data->map.fpov % 10 != 0)
			data->map.fpov = 10.0f;
		free(data->proj);
		data->proj = prep_projection_matrix(&data->map);
	}
	if(keysym == 114)
	{
		while (x < 1000)
		{
			data->map.anglex += 0.001f;
			data->map.angley += 0.002f;
			project(&data->map, data->proj);
			render(data);
			x++;
		}
	}
	project(&data->map, data->proj);
	render(data);
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

