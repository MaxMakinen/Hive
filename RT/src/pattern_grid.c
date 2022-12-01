/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_grid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:07:31 by jjuntune          #+#    #+#             */
/*   Updated: 2022/11/16 21:39:19 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

void	pattern_grid(t_point hit_loc, t_color *hit_color, double pattern_dif, double perlin)
{
	if (pattern_striped(hit_loc.s_xyzw.x + perlin) == 1)
		*hit_color = tuple_scalar_mult(*hit_color, pattern_dif);
	if (pattern_striped(hit_loc.s_xyzw.y + perlin) == 1)
		*hit_color = tuple_scalar_mult(*hit_color, pattern_dif);
	if (pattern_striped(hit_loc.s_xyzw.z + perlin) == 1)
		*hit_color = tuple_scalar_mult(*hit_color, pattern_dif);
}