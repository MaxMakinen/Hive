/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_pixel_put.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:28:19 by jsaarine          #+#    #+#             */
/*   Updated: 2022/11/12 19:28:51 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	img_pixel_put(t_frame_buffer *fb, unsigned int x,
	unsigned int y, t_color color)
{
	int			*dst;
	unsigned int	color_int;

	color_int = color_to_int(color);
	dst = fb->data + (y * WIN_W + x);
	*(unsigned int *)dst = color_int;
}
