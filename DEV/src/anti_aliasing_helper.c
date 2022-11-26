/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_aliasing_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:49:21 by jjuntune          #+#    #+#             */
/*   Updated: 2022/11/13 16:15:58 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

void	add_hit_color(t_main *main, t_ray *shadow)
{
	double	angle;
	//static t_perlin perlin_t;
	//double	perlin;

	//if (load_perlin_data(&perlin_t) == 0)
	//{
	//	ft_putendl("there was error opening perlin noice table\n");
	//	perlin = 1;
	//}
	//else
	//	perlin = perlin_noice(&main->ray.hit.hit_loc, &perlin_t);
	//if (vector_dot(main->ray.dir, shadow->hit.normal) > 0)
	//	shadow->hit.normal = tuple_scalar_mult(shadow->hit.normal, -1.0);
	angle = 1; //vector_dot(shadow->dir, shadow->hit.normal);
	
	if (angle >= 0)
	{
		
		main->ray.hit.color.s_rgb.r
			+= (main->obj[shadow->hit.clo_obj_id].color.s_rgb.r * angle);
		
		main->ray.hit.color.s_rgb.g
			+= (main->obj[shadow->hit.clo_obj_id].color.s_rgb.g * angle);
		main->ray.hit.color.s_rgb.b
			+= (main->obj[shadow->hit.clo_obj_id].color.s_rgb.b * angle);
		
	}

	
}

void	fix_aliasing_color(t_main *main, int sub_pixel_count)
{
	main->ray.hit.color.s_rgb.r /= sub_pixel_count;
	main->ray.hit.color.s_rgb.g /= sub_pixel_count;
	main->ray.hit.color.s_rgb.b /= sub_pixel_count;
}