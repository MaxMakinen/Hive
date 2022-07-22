/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 09:47:35 by mmakinen          #+#    #+#             */
/*   Updated: 2022/07/22 14:08:43 by mmakinen         ###   ########.fr       */
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

void	check_input(t_data *data, char *str)
{
	if (!ft_strncmp(str, "mandelbrot", sizeof(str)))
		data->function = 0;
	if (!ft_strncmp(str, "julia", sizeof(str)))
		data->function = 1;
	if (!ft_strncmp(str, "multibrot", sizeof(str)))
		data->function = 2;
	if (!ft_strncmp(str, "sierpinsky", sizeof(str)))
		data->function = 3;
	if (data->function < 0)
		exit_error("Invalid fractal");
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		exit_error("Usage: <fractal> [mandelbrot] [julia] [multibrot] [sierpinsky]");
	init_data(&data);
	check_input(&data, av[1]);
	create_img(&data, av[1]);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img->mlx_img, 0, 0);
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, 4, 1L << 2, mouse_press, &data);
	mlx_hook(data.win_ptr, 6, 1L << 6, mouse_move, &data);
	mlx_hook(data.win_ptr, 5, 1L << 3, mouse_release, &data);
	mlx_hook(data.win_ptr, 2, 1L << 0, handle_keypress, &data);
	mlx_hook(data.win_ptr, 17, 0, destroy, &data);
	mlx_hook(data.win_ptr, 12, 0, render, &data);
	mlx_loop(data.mlx_ptr);
	free(data.mlx_ptr);
}
