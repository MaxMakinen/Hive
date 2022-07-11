/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:13:23 by mmakinen          #+#    #+#             */
/*   Updated: 2022/07/11 14:53:42 by mmakinen         ###   ########.fr       */
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

void	init_data(t_data *data)
{
	data->img = (t_img *)ft_calloc(sizeof(t_img), 1);
	data->world = (t_coord *)ft_calloc(sizeof(t_coord), 1);
	data->offset = (t_coord *)ft_calloc(sizeof(t_coord), 1);
	data->screen = (t_screen *)ft_calloc(sizeof(t_screen), 1);
	zero_coord(data->world);
	zero_coord(data->offset);
	zero_screen(data->screen);
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

