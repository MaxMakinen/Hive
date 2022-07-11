/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 09:47:35 by mmakinen          #+#    #+#             */
/*   Updated: 2022/07/11 13:51:51 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	clean_exit(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img->mlx_img);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	exit(0);
}

int	destroy(void	*param)
{
	clean_exit(param);
	return (1);
}


void	exit_error(char *str)
{
	ft_putendl(str);
	exit(1);
}

int main(int ac, char **av)
{
	t_data	data;

	(void)av;
	if (ac != 1)
		exit_error("Usage: STILL IN TESTING");
	init_data(&data);
	create_img(&data, "Rumplestiltskin");
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img->mlx_img, 0, 0);
	render(&data);
//	mlx_loop_hook(data.mlx_ptr, &rotate, &data);								
//	mlx_hook(data.win_ptr, 4, 1L << 2, mouse_press, &data);					 
	mlx_hook(data.win_ptr, 2, 1L << 0, handle_keypress, &data);				 
	mlx_hook(data.win_ptr, 17, 0, destroy, &data);							  
//	mlx_hook(data.win_ptr, 12, 0, render, &data);								 
	mlx_loop(data.mlx_ptr);													 
	free(data.mlx_ptr); 
}
