/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_screen_shot.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 13:45:06 by jjuntune          #+#    #+#             */
/*   Updated: 2022/12/07 14:13:09 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

int	add_to_line_str(char ***temp_str, char ***image_str, int color, int i)
{
	char	*c_color;

	c_color = ft_itoa(color);
	if (c_color == NULL)
		return (-1);
	**temp_str = ft_strjoin(**image_str, c_color);
	ft_strdel(*image_str);
	ft_strdel(&c_color);
	if (i == 0)
	{
		**image_str = ft_strjoin(**temp_str, " ");
		ft_strdel(*temp_str);
	}
	return (0);
}

int	fill_image_str(char **temp_str, char **image_str, t_color color, int x)
{
	if (add_to_line_str(&temp_str, &image_str, (int)color.s_rgb.r, 0) == -1)
		return (-1);
	if (add_to_line_str(&temp_str, &image_str, (int)color.s_rgb.g, 0) == -1)
		return (-1);
	if (add_to_line_str(&temp_str, &image_str, (int)color.s_rgb.b, 1) == -1)
		return (-1);
	if (x < (WIN_W - 1))
		*image_str = ft_strjoin(*temp_str, " ");
	else
		*image_str = ft_strjoin(*temp_str, "\n");
	if (*image_str == NULL)
		return (-1);
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
			int_to_rgb((image[((y * WIN_W) + x)]), &color);
			if (image_str == NULL)
				return (-1);
			if (fill_image_str(&temp_str, &image_str, color, x++) == -1)
				return (-1);
			ft_putstr_fd(image_str, s_s.fd);
			ft_strdel(&temp_str);
			ft_strdel(&image_str);
		}
		y++;
	}
	return (0);
}

char	*increment_image_name(void)
{
	static int	image_nbr;
	char		*image_name;
	int			fd;

	fd = 1;
	while (fd > 0)
	{
		image_name = create_screen_shot_name(image_name, image_nbr++);
		fd = open(image_name, O_RDONLY);
		if (fd > 0)
		{
			ft_strdel(&image_name);
			close(fd);
		}
	}
	return (image_name);
}

void	creat_screen_shot(int *image)
{
	char			*image_name;
	t_screen_shot	s_s;

	image_name = increment_image_name();
	if (image_name != NULL)
	{
		s_s.fp = fopen(image_name, "wr+");
		if (s_s.fp != NULL)
		{
			fclose(s_s.fp);
			s_s.fd = open(image_name, O_WRONLY);
			ft_strdel(&image_name);
			ft_putstr_fd("P3\n", s_s.fd);
			ft_putnbr_fd(WIN_W, s_s.fd);
			ft_putchar_fd(' ', s_s.fd);
			ft_putnbr_fd(WIN_H, s_s.fd);
			ft_putchar_fd('\n', s_s.fd);
			ft_putstr_fd("255\n", s_s.fd);
			if (write_file_line(s_s, image) == -1)
				ft_putendl_fd("screen shot failed.", 2);
			close(s_s.fd);
		}
	}
	else
		ft_putendl_fd("screen shot failed.", 2);
}
