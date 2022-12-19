/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 22:21:39 by jjuntune          #+#    #+#             */
/*   Updated: 2022/12/07 13:52:38 by jjuntune         ###   ########.fr       */
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
			fb->filter[((j * WIN_W) + i)] = color;
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
	while (j < WIN_H)
	{
		i = 0;
		while (i < WIN_W)
		{
			while (i < WIN_W && fb->mask[((j * WIN_W) + i)] == 0)
				i++;
			if (i == WIN_W)
				break ;
			fb->filter[((j * WIN_W) + i)] = 0x00000000;
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
	ft_memcpy(fb->filter, fb->data, (fb->data_len * sizeof(int)));
	while (j < WIN_H)
	{
		i = 0;
		while (i < WIN_W)
		{
			while (i < WIN_W && fb->mask[((j * WIN_W) + i)] == 0)
				i++;
			if (i == WIN_W)
				break ;
			fb->filter[((j * WIN_W) + i)] = 0x00000000;
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
			if (fb->mask[((j * WIN_W) + i)] == 0)
				fb->filter[((j * WIN_W) + i)] = 0x00000000;
			else
				fb->filter[((j * WIN_W) + i)] = 0xffffff00;
			i++;
		}
		j++;
	}
}

void	creat_filters(t_frame_buffer *fb, int filter_type)
{
	if (filter_type == B_W_CARTOON || filter_type == BLACK_AND_WHITE)
	{
		create_black_and_white(fb);
		if (filter_type == B_W_CARTOON)
			create_black_and_white_cartoon(fb);
	}
	else if (filter_type == CARTOON)
		create_cartoon(fb);
	else if (filter_type == SEPIA)
		create_sepia(fb);
	else if (filter_type == EDGE)
		create_edge_map(fb);
}
