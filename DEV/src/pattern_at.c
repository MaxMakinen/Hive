/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_at.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:26:22 by jjuntune          #+#    #+#             */
/*   Updated: 2022/11/16 21:28:36 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

void	pattern_at(t_object *obj,t_point hit_loc, t_color *hit_color, t_perlin *perlin)
{
	double perlin_out;

	perlin_out = 0;
	if (obj->material.pattern.pattern_perlin == TRUE)
		perlin_out = perlin_noice(hit_loc, perlin);
	if (obj->material.pattern.pattern_id == GRID)
			pattern_grid(hit_loc, hit_color,obj->material.pattern.pattern_dif, perlin_out);
	if (obj->material.pattern.pattern_id == STRIPED)
	{
		if (pattern_striped(hit_loc.s_xyzw.x + perlin_out) == 1)
			*hit_color = tuple_scalar_mult(*hit_color, obj->material.pattern.pattern_dif);

	}
}