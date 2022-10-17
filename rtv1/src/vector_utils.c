/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 13:36:33 by mmakinen          #+#    #+#             */
/*   Updated: 2022/10/15 13:36:35 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec3f	vec_times(t_vec3f vec1, t_vec3f vec2)
{
	vec1.x *= vec2.x;
	vec1.y *= vec2.y;
	vec1.z *= vec2.z;
	return (vec1);
}

t_vec3f	vec_invert(t_vec3f vec)
{
	vec.x = -vec.x;
	vec.y = -vec.y;
	vec.z = -vec.z;
	return (vec);
}

t_vec3f	reflect_ray(t_vec3f ray, t_vec3f normal)
{
	return (vec_minus(ray, vec_mult(normal, dot_product(ray, normal))));
}

t_vec3f	get_vector(t_vec3f vector, char **words)
{
	vector.x = ft_atod(words[0]);
	vector.y = ft_atod(words[1]);
	vector.z = ft_atod(words[2]);
	return (vector);
}
