/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <dmalesev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 12:58:53 by dmalesev          #+#    #+#             */
/*   Updated: 2022/05/03 14:18:05 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	close_fdf(t_utils *utils, char *exit_msg, int exit_code)
{
	if (utils->win)
		mlx_destroy_window(utils->mlx, utils->win);
	if (utils->img.ptr)
		mlx_destroy_image(utils->mlx, utils->img.ptr);
	if (utils->img2.ptr)
		mlx_destroy_image(utils->mlx, utils->img2.ptr);
	ft_putendl(exit_msg);
	exit (exit_code);
}

void	open_screen(t_utils *u)
{
	u->mlx = mlx_init();
	if (!u->mlx)
		close_fdf(u, "Failed to connect software to display...", -1);
	u->win = mlx_new_window(u->mlx, u->screen_x, u->screen_y, "FDF");
	if (!u->win)
		close_fdf(u, "Failed to open window...", -1);
	u->img.max_x = u->screen_x / 5 * 4;
	u->img.max_y = u->screen_y;
	u->img.ptr = mlx_new_image(u->mlx, u->img.max_x, u->img.max_y);
	if (!u->img.ptr)
		close_fdf(u, "Failed to create image...", -1);
	u->img2.max_x = u->screen_x / 5;
	u->img2.max_y = u->screen_y;
	u->img2.ptr = mlx_new_image(u->mlx, u->img2.max_x, u->img2.max_y);
	if (!u->img2.ptr)
		close_fdf(u, "Failed to create image2...", -1);
	u->img.addr = mlx_get_data_addr(u->img.ptr, &u->img.bits_per_pixel,
			&u->img.line_length, &u->img.endian);
	u->img2.addr = mlx_get_data_addr(u->img2.ptr, &u->img2.bits_per_pixel,
			&u->img2.line_length, &u->img2.endian);
	init_hooks(u);
}

void	file_into_map(t_utils *utils, int fd, int fd2)
{
	utils->lines = count_lines(fd);
	get_map(fd2, utils);
	open_screen(utils);
	render_screen(utils);
}

int	main(int argc, char **argv)
{
	t_utils	utils;
	int		fd;
	int		fd2;

	init(&utils);
	if (argc == 2)
	{
		fd = open(argv[1], O_RDWR);
		if (fd == -1)
		{
			perror("ERROR");
			close_fdf(&utils, "Usage: <Filename>", -1);
		}
		fd2 = open(argv[1], O_RDWR);
		if (fd >= 0 && fd2 >= 0)
			file_into_map(&utils, fd, fd2);
	}
	else
		close_fdf(&utils, "Usage: <Filename>", -1);
	mlx_loop(utils.mlx);
	return (0);
}
