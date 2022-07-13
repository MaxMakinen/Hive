/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:13:23 by mmakinen          #+#    #+#             */
/*   Updated: 2022/07/13 12:11:59 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	zero_coord(t_coord *coord)
{
	coord->x = 0.0;
	coord->y = 0.0;
}

void	zero_screen(t_screen *screen)
{
	screen->x = 0;
	screen->y = 0;
}

void	reset_scale(t_data *data)
{
	data->scale.x = (double)WINDOW_HEIGHT / 3.00;
	data->scale.y = (double)WINDOW_HEIGHT / 3.00;
}

void	init_data(t_data *data)
{
	data->img = (t_img *)ft_calloc(sizeof(t_img), 1);
	zero_coord(&data->world_min);
	zero_coord(&data->world_max);
	zero_screen(&data->screen_min);
	zero_screen(&data->screen_max);
	zero_coord(&data->offset);
	zero_coord(&data->julia);
	reset_scale(data);
	data->julia_stop = 0;
	data->mandel = 0;
	data->zoom.x = 1.1;
	data->zoom.y = 0.9;
	data->offset.x = -3.0;
	data->offset.y = -1.5;
	data->max_iterations = 200;
	data->multi = 2.0;
}

void    render_background(t_img *img, int color)                                
{                                                                               
    int i;                                                                      
    int *pixel;                                                                 
    int size;                                                                   
                                                                                
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
	render_background(data->img, PURPLE_PIXEL);
}

