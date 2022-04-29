/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:43:43 by mmakinen          #+#    #+#             */
/*   Updated: 2022/04/29 16:06:28 by mmakinen         ###   ########.fr       */
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
	if (keysym == 65307 || keysym == 53)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
		exit(0);
	}
	if(keysym == 65429)
	{
		data->map.anglez -= 0.05f;
		data->map.anglex -= 0.05f;
	}
	if(keysym == 65434)
	{
		data->map.anglez += 0.05f;
		data->map.anglex -= 0.05f;
	}
	if(keysym == 65437 || keysym == 9)
	{
		data->map.anglex += 0.02f;
		data->map.angley += 0.04f;
		data->map.anglez += 0.04f;
	}
	if(keysym == 113 || keysym == 12)
	{
		data->map.anglez -= 0.1f;
	}
	if(keysym == 119 || keysym == 13)
	{
		data->map.anglex -= 0.1f;
	}
	if(keysym == 101 || keysym == 14)
	{
		data->map.anglez += 0.1f;
	}
	if(keysym == 115 || keysym == 1)
	{
		data->map.anglex += 0.1f;
	}
	if(keysym == 97 || keysym == 0)
	{
		data->map.angley += 0.1f;
	}
	if(keysym == 100 || keysym == 2)
	{
		data->map.angley -= 0.1f;
	}
	if(keysym == 105 || keysym == 15)
	{
		data->map.zoom -= 1;
	}
	if(keysym == 107 || keysym == 3)
	{
		data->map.zoom += 1;
	}
	if(keysym == 108)
	{
		data->map.zoom += 10;
	}
	if(keysym == 111)
	{
		data->map.zoom -= 10;
	}
	if(keysym == 110 || keysym == 5)
	{
		data->map.f_pov = 0.0f;
		data->map.zoom = 1000;
		if (data->map.zoom < 0)
			data->map.zoom = 0;
		if (data->map.f_pov <= 0)
			data->map.f_pov = 1.0f;
		data->map.proj = prep_projection_matrix(&data->map, data->map.proj);
	}
	if(keysym == 109 || keysym == 17)
	{
		data->map.f_pov = 90.0f;
		data->map.zoom = (data->map.x_max + data->map.y_max) / 2 + 5;
		if ((int)data->map.f_pov % 10 != 0)
			data->map.f_pov = 10.0f;
		data->map.proj = prep_projection_matrix(&data->map, data->map.proj);
	}
	if(keysym == 114 || keysym == 15)
	{
		data->map.anglex = 0.0f;
		data->map.angley = 0.0f;
		data->map.anglez = 0.0f;
	}
	project(&data->map, data->map.proj);
	render(data);
	printf("Keypress: %d\n", keysym);
	return (0);
}

int handle_keyrelease(int keysym, t_data *data)
{
	if (keysym == 120)
	{
		data->map.anglex = 0;
		data->map.angley = 0;
		data->map.anglez = 0;
	}
//	printf("Keyrelease: %d\n", keysym);
	return (0);
}

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

