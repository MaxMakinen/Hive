/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 12:27:37 by dpalacio          #+#    #+#             */
/*   Updated: 2022/04/28 16:07:59 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//Exits the program in case of an error and prints a related message
void	error_print(char *e_string, t_data *data)
{
	ft_putendl(e_string);
	exit_fdf(53, data);
}

//Start of the program
int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		error_print("Usage: ./fdf <map_file>", &data);
	data.color_scheme = 0;
	read_file(argv[1], &data);
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "fdf");
	data.img = mlx_new_image(data.mlx, WIN_WIDTH, WIN_HEIGHT);
	data.img_addr = mlx_get_data_addr(data.img, &data.px_bits,
			&data.line_bytes, &data.endian);
	offset_draw(&data);
	draw(&data);
	controls(&data);
	mlx_loop(data.mlx);
}
