/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 09:26:41 by mmakinen          #+#    #+#             */
/*   Updated: 2022/08/04 16:10:09 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	render_background(t_img *img, int color)
{
	int	i;
	int	*pixel;
	int	size;

	pixel = (int *)img->addr;
	size = WINDOW_HEIGHT * WINDOW_WIDTH;
	i = 0;
	while (i < size)
	{
		pixel[i] = color;
		i++;
	}
}

void	create_img(t_data *data, char *name)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		exit_error("MLX ERROR: init");
	data->win_ptr = mlx_new_window(data->mlx_ptr, WINDOW_WIDTH, \
			WINDOW_HEIGHT, name);
	if (data->win_ptr == NULL)
	{
		free(data->win_ptr);
		exit_error("MLX ERROR: img");
	}
	data->img->mlx_img = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, \
			WINDOW_HEIGHT);
	data->img->addr = mlx_get_data_addr(data->img->mlx_img, \
			&data->img->bpp, &data->img->line_len, &data->img->endian);
	render_background(data->img, BLACK);
}

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}
