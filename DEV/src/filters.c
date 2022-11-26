/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 22:21:39 by jjuntune          #+#    #+#             */
/*   Updated: 2022/10/20 13:44:13 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

void	create_black_and_white(t_frame_buffer *fb)
{
	t_color	rgb;
	int		color;
	int		i;
	int		j;

	j = 0;
	while (j < WIN_H)
	{
		i = 0;
		while (i < WIN_W)
		{
			int_to_rgb(fb->data[((j * WIN_W) + i)], &rgb);
			color = rgb_to_white(&rgb);
			fb->b_w[((j * WIN_W) + i)] = color;
			i++;
		}
		j++;
	}
}

void	create_black_and_white_cartoon(t_frame_buffer *fb)
{
	int		i;
	int		j;

	j = 0;
	ft_memcpy(fb->b_w_cartoon, fb->b_w, (fb->data_len * sizeof(int)));
	while (j < WIN_H)
	{
		i = 0;
		while (i < WIN_W)
		{
			while (i < WIN_W && fb->mask[((j * WIN_W) + i)] == 0)
				i++;
			if (i == WIN_W)
				break ;
			fb->b_w_cartoon[((j * WIN_W) + i)] = 0x00000000;
			i++;
		}
		j++;
	}
}

void	create_cartoon(t_frame_buffer *fb)
{
	int		i;
	int		j;

	j = 0;
	ft_memcpy(fb->cartoon, fb->data, (fb->data_len * sizeof(int)));
	while (j < WIN_H)
	{
		i = 0;
		while (i < WIN_W)
		{
			while (i < WIN_W && fb->mask[((j * WIN_W) + i)] == 0)
				i++;
			if (i == WIN_W)
				break ;
			fb->cartoon[((j * WIN_W) + i)] = 0x00000000;
			i++;
		}
		j++;
	}
}

void	create_edge_map(t_frame_buffer *fb)
{
	int		i;
	int		j;

	j = 0;
	while (j < WIN_H)
	{
		i = 0;
		while (i < WIN_W)
		{
			while (i < WIN_W && fb->mask[((j * WIN_W) + i)] == 0)
				i++;
			if (i == WIN_W)
				break ;
			fb->edge_map[((j * WIN_W) + i)] = 0xffffff00;
			i++;
		}
		j++;
	}
}

void	creat_filters(t_frame_buffer *fb)
{
	create_black_and_white(fb);
	create_black_and_white_cartoon(fb);
	create_cartoon(fb);
	create_edge_map(fb);
}
