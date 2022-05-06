/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:06:27 by mmakinen          #+#    #+#             */
/*   Updated: 2022/05/06 10:02:44 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	show(t_data *data)
{
	project(data->map, data->map->proj);
	render(data);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		ft_error("Usage: fdf <input file>");
	init_data(&data);
	data.map = input(argv[1], data.map);
	center_coords(&data);
	create_img(&data, argv[1]);
	mlx_loop_hook(data.mlx_ptr, &rotate, &data);
	mlx_hook(data.win_ptr, 4, 1L << 2, mouse_press, &data);
	mlx_hook(data.win_ptr, 2, 1L << 0, handle_keypress, &data);
	mlx_hook(data.win_ptr, 17, 0, destroy, &data);
	mlx_hook(data.win_ptr, 12, 0, show, &data);
	mlx_loop(data.mlx_ptr);
	free(data.mlx_ptr);
	return (0);
}
