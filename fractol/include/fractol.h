/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 09:57:49 by mmakinen          #+#    #+#             */
/*   Updated: 2022/07/11 13:51:00 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FRACTOL_H
# define FRACTOL_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <string.h>

# include "mlx.h"
# include "libft.h"
# include "color.h"

# define TRUE 1
# define FALSE 0

# define WINDOW_WIDTH 1600
# define WINDOW_HEIGHT 900

# define KEY_ESC 65307

union u_color
{
	int	color;
	char rgb[4];
};

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	*img;
//	t_map	*map;
}	t_data;

void	exit_error(char *str);
int		handle_keypress(int keysym, t_data *data);
void	init_data(t_data *data);
void	create_img(t_data *data, char *name);
void	clean_exit(t_data *data);

void	img_pix_put(t_img *img, int x, int y, int color);
int	render(t_data *data);
int	get_color(int iteration);
int	mandel(int pixel_x, int pixel_y);

#endif
