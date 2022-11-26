/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_screen_shot.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 13:45:06 by jjuntune          #+#    #+#             */
/*   Updated: 2022/11/06 15:59:46 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

void	write_ppm_info(int fd)
{
	ft_putstr_fd("P3\n", fd);
	ft_putnbr_fd(WIN_W, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(WIN_H, fd);
	ft_putchar_fd('\n', fd);
	ft_putstr_fd("255\n", fd);
}

int	add_to_line_str(char **temp_str, char **image_str, int color, int i)
{
	char	*c_color;

	c_color = ft_itoa(color);
	//malloc check
	*temp_str = ft_strjoin(*image_str, c_color);
	//malloc check
	ft_strdel(image_str);
	ft_strdel(&c_color);
	if (i == 0)
	{
		*image_str = ft_strjoin(*temp_str, " ");
		ft_strdel(temp_str);
	}
	return (0);
}

int	write_file_line(t_screen_shot s_s, int *image)
{
	int		y;
	int		x;
	t_color	color;
	char	*image_str;
	char	*temp_str;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			image_str = ft_strnew(0);
			//malloc check
			int_to_rgb((image[((y * WIN_W) + x)]), &color);
			add_to_line_str(&temp_str, &image_str, (int)color.s_rgb.r, 0);
			//malloc checks
			add_to_line_str(&temp_str, &image_str, (int)color.s_rgb.g, 0);
			//malloc checks
			add_to_line_str(&temp_str, &image_str, (int)color.s_rgb.b, 1);
			//malloc checks
			if (x < (WIN_W - 1))
				image_str = ft_strjoin(temp_str, " ");
			else
				image_str = ft_strjoin(temp_str, "\n");
			//malloc check
			ft_strdel(&temp_str);
			ft_putstr_fd(image_str, s_s.fd);
			ft_strdel(&image_str);
			x++;
		}
		y++;
	}
	return (0);
}

char	*increment_image_name(void)
{
	static int	image_nbr;
	char		*image_name;
	char		*temp;
	int			fd;

	fd = 1;
	while (fd > 0)
	{
		temp = "./Images/screen_shot_";
		image_name = ft_itoa(image_nbr);
		//malloc check
		temp = ft_strjoin(temp, image_name);
		//malloc check
		ft_strdel(&image_name);
		image_name = ft_strjoin(temp, ".ppm");
		//malloc check
		ft_strdel(&temp);
		fd = open(image_name, O_RDONLY);
		if (fd > 0)
			image_nbr++;
		close(fd);
	}
	return (image_name);
}

void	creat_screen_shot(int *image)
{
	char			*image_name;
	t_screen_shot	s_s;
	// int				y;

	// y = 0;
	image_name = increment_image_name();
	//malloc check
	s_s.fp = fopen(image_name, "wr+");
	if (s_s.fp != NULL)
	{
		fclose(s_s.fp);
		s_s.fd = open(image_name, O_WRONLY);
		ft_strdel(&image_name);
		write_ppm_info(s_s.fd);
		write_file_line(s_s, image);
		//malloc check
		close(s_s.fd);
	}
}
