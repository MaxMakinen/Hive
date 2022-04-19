/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:43:43 by mmakinen          #+#    #+#             */
/*   Updated: 2022/04/19 12:54:29 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "fdf.h"
#include "libft.h"

#include <mlx.h>
#ifdef LINUX
	#include <X11/keysym.h>
	#include <X11/X.h>
#endif

#define MLX_ERROR 1

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define OFFSET 18
#define RED_PIXEL 0xFF0000
#define GREEN_PIXEL 0xFF00
#define BLUE_PIXEL 0xFF
#define WHITE_PIXEL 0xFFFFFF
#define BLACK_PIXEL 0x000000

int	ft_abs(int num)
{
	if (num < 0)
		num = -num;
	return (num);
}

int handle_keypress(int keysym, t_data *data)
{
	/*
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	*/
	printf("Keypress: %d\n", keysym);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	data->win_ptr = NULL;
	return (0);
}
/*
int handle_keyrelease(int keysym, t_data *data)
{
	printf("Keyrelease: %d\n", keysym);
	return (0);
}
*/

void img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	float	temp;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

		/* img versions */

void render_background(t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
			img_pix_put(img , j++, i, color);
		i++;
	}
}

int render_rect(t_img *img, t_rect rect)
{
	int	i;
	int	j;

	i = rect.y;
		while (i < rect.y + rect.height)
		{
			j = rect.x;
			while (j < rect.x + rect.width)
				img_pix_put(img, j++, i, rect.color);
			i++;
		}
		return (0);
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

t_vector	*prep_vector(t_vector *vector)
{
	vector->x = 0;
	vector->y = 0;
	vector->z = 0;
	vector->w = 1;
	return (vector);
}

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

t_matrix	*mat_mul(t_matrix *matrix, t_matrix *vector)
{
	int		rows;
	int		cols;
	int		index;
	int		len;
	int		sum;
	t_matrix	*result;

	rows = 0;
	len = 3;
	prep_matrix(result);
	while (rows < len)
	{
		cols = 0;
		while (cols < len)
		{
			index = 0;
			sum = 0;
			while (index < len)
			{
				sum += matrix->matrix[rows][index] * vector->matrix[index][cols];
				index++;
			}
			result->matrix[rows][cols] += sum;
			cols++;
		}
		rows++;
	}
	return (result);
}

t_vector vect_mult(t_vector vect, int num)
{
	vect.x *= num;
	vect.y *= num;
	vect.z *= num;
	return (vect);
}

t_vector *vect_add(t_vector *vect, int num)
{
	vect->x += num;
	vect->y += num;
	//vect->z += num;
	return (vect);
}

t_vector *vect_subt(t_vector *vect, int num)
{
	vect->x -= num;
	vect->y -= num;
	vect->z -= num;
	return (vect);
}

t_vector *vect_div(t_vector *vect, int num)
{
	vect->x /= num;
	vect->y /= num;
	vect->z /= num;
	return (vect);
}

int	check_color(t_vector coord)
{
	if (coord.z > 0)
		return (GREEN_PIXEL);
	return (RED_PIXEL);
}

int	render_line(t_img *img, t_vector start, t_vector end)
{
	int	x;
	int	y;
	int	m;
	int	delta_x;
	int	delta_y;
	int delta;
	int	adjust;
	int	offset;
	int	threshold;
	int	threshold_inc;
	int color;

	delta_x = start.x - end.x;
	delta_y = start.y - end.y;
	color = RED_PIXEL;
	if (delta_x == 0)
	{
		if (end.y < start.y)
			ft_swapint(&start.y, &end.y);
		while (start.y <= end.y)
			img_pix_put(img, start.x, start.y++, check_color(start));
	}
	else
	{
		m = (float)delta_y / delta_x;
		offset = 0;
		adjust = 1;
		if (m < 0)
			adjust = -1;
		if (m <= 1 && m >= -1)
		{
			delta = ft_abs(delta_y) * 2;
			threshold = ft_abs(delta_x);
			threshold_inc = ft_abs(delta_x) * 2;
			y = start.y;
			if (end.x < start.x)
			{
				ft_swapint(&start.x, &end.x);
				y = end.y;
			}
			while (start.x <= end.x)
			{
				img_pix_put(img, start.x++, y, check_color(start));
				offset += delta;
				if (offset >= threshold)
				{
					y += adjust;
					threshold +=threshold_inc;
				}
			}
		}
		else
		{
			delta= ft_abs(delta_x) * 2;
			threshold = ft_abs(delta_y);
			threshold_inc = ft_abs(delta_y) * 2;
			x = start.x;
			if (end.y < start.y)
			{
				ft_swapint(&start.y, &end.y);
				x = end.x;
			}
			while (start.y < end.y)
			{
				img_pix_put(img, x, start.y++, check_color(start));
				offset += delta;
				if (offset >= threshold)
				{
					x += adjust;
					threshold += threshold_inc;
				}
			}
		}
	}
	return (0);
}

int render(t_data *data)
{
	int	x;
	int	y;
	int	placement;

	y = 0;
	if (data->win_ptr == NULL)
		return (1);
	render_background(&data->img, BLACK_PIXEL);
	while (y < data->map.y_max)
	{
		x = 0;
		while (x < data->map.x_max)
		{
			if((x + 1) < data->map.x_max)
				render_line(&data->img, vect_mult(data->map.coords[y][x].vect, OFFSET), vect_mult(data->map.coords[y][x + 1].vect, OFFSET));
			if((y + 1) < data->map.y_max)
				render_line(&data->img, vect_mult(data->map.coords[y][x].vect, OFFSET), vect_mult(data->map.coords[y + 1][x].vect, OFFSET));
			//data->map.coords[y][x].vect = matrix_to_vec(matmul(rotate_x(1),vec_to_matrix(&data->map.coords[x][y].vect)));
			x++;
		}
		y++;
	}
	
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	return (0);
}



int main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		ft_putendl("Usage: fdf <input file>");
		return(1);
	}
	data.map = input(argv[1], &data.map);

	data.mlx_ptr = mlx_init();
	/* Create the image */
	if (data.mlx_ptr == NULL)
		return(MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "My window");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr)	;
		return (MLX_ERROR);
	}

	int y = 0;
	int x;
	while (y < data.map.y_max)
	{
		x = 0;
		while (x < data.map.x_max)
		{
			data.map.coords[y][x].vect.x += data.map.x_max / 2;
			data.map.coords[y][x].vect.y += data.map.y_max / 2;
			x++;
		}
		y++;
	}
//	printf("vect x : %i\nvect y : %i\nvect z : %i\n",data.map.coords[1][1].vect.x, data.map.coords[1][1].vect.y, data.map.coords[1][1].vect.z);
//	data.map.coords[1][1].vect = *matrix_to_vec(mat_mul(rotate_x(1), vec_to_matrix(&data.map.coords[1][1].vect)));
//	printf("vect x : %i\nvect y : %i\nvect z : %i\n",data.map.coords[1][1].vect.x, data.map.coords[1][1].vect.y, data.map.coords[1][1].vect.z);

	/* setup hooks */
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp, &data.img.line_len, &data.img.endian);

	mlx_loop_hook(data.mlx_ptr, &render, &data);
	//CHANGE INTO MLX_KEY_HOOK OR WHATEVER
	mlx_key_hook(data.win_ptr, &handle_keypress, &data);
//	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
//	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease, &data);

	mlx_loop(data.mlx_ptr);

	/* we will exit the loop if there's no window left, and execute this code */
	mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	return (0);
}

