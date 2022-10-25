/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 13:54:01 by mmakinen          #+#    #+#             */
/*   Updated: 2022/08/17 13:57:02 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	vec_compare(t_vec3f vec1, t_vec3f vec2)
{
	return (vec1.x == vec2.x && vec1.y == vec2.y && vec1.z == vec2.z);
}

t_vec3f	vec_plus(t_vec3f vec1, t_vec3f vec2)
{
	vec1.x += vec2.x;
	vec1.y += vec2.y;
	vec1.z += vec2.z;
	return (vec1);
}

t_vec3f	vec_minus(t_vec3f vec1, t_vec3f vec2)
{
	vec1.x -= vec2.x;
	vec1.y -= vec2.y;
	vec1.z -= vec2.z;
	return (vec1);
}

t_vec3f	vec_mult(t_vec3f vec1, double mult)
{
	vec1.x *= mult;
	vec1.y *= mult;
	vec1.z *= mult;
	return (vec1);
}

t_vec3f	vec_div(t_vec3f vec, double div)
{
	return (vec_mult(vec, 1 / div));
}
