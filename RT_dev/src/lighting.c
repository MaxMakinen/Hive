/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:12:38 by jsaarine          #+#    #+#             */
/*   Updated: 2022/12/14 18:55:51 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include <math.h>
#include "stdio.h"

// the material itself
// the point being illuminated
// light source
// the eye 
// normal_v vector from the Phong reflection model
t_color	lighting(t_material mat, t_light light, t_point point, t_vector to_eye, t_vector normal_v, int in_shadow)
{
	t_color		result;
	t_color		effective_color;
	t_vector	to_light_v;
	t_color		ambient;
	double		light_dot_normal;
	t_color		diffuse;
	t_color		specular;
	t_vector	reflection_v;
	double		reflection_dot_eye;
	double		factor;
	

	result = color_new(0,0,0);
	result.s_xyzw.w = 1;
	// # combine the surface color with the light's color/intensity
	effective_color = color_multiply(mat.color, light.intensity);

	// find the direction to the light source
	to_light_v = tuple_unit(tuple_sub(light.location, point)); 

	ambient = tuple_scalar_mult(effective_color, mat.ambient);

	// light_dot_normal_v represents the cosine of the angle between the 
	// light vector and the normal_v vector. A negative number means the 
	// light is on the other side of the surface.
	light_dot_normal = vector_dot(to_light_v, normal_v);

	if (light_dot_normal < 0 || in_shadow == 1)
	{
		diffuse = color_new(0, 0, 0);
		specular = color_new(0, 0, 0);
	}
	else
	{
		// compute the diffuse contribution
		diffuse = tuple_scalar_mult(effective_color, mat.diffuse * light_dot_normal);

		// reflect_dot_eye represents the cosine of the angle between the
		// reflection vector and the eye vector. A negative number means the 
		// light reflects away from the eye.
		reflection_v = vector_reflect(tuple_neg(to_light_v), normal_v);
		reflection_dot_eye = vector_dot(reflection_v, to_eye);
		if (reflection_dot_eye <= 0)
			specular = color_new(0, 0, 0);
		else
		{
			// compute the specular contribution

			factor = pow(reflection_dot_eye, mat.shininess);
			specular = tuple_scalar_mult(light.intensity, mat.specular * factor);
		}
	}
	result = tuple_add(diffuse, specular);
	result = tuple_add(result, ambient);
	result.s_xyzw.w = 0;
	return (result);
}