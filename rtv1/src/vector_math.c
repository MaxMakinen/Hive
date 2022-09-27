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

double	dot_product(t_vec3f vec1, t_vec3f vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

double	vec_len(t_vec3f vec)
{
	return (sqrt(dot_product(vec, vec)));
}

int	vec_compare(t_vec3f vec1, t_vec3f vec2)
{
	return (vec1.x == vec2.x && vec1.y == vec2.y && vec1.z == vec2.z);
}

t_vec3f	unit_vec(t_vec3f vec)
{
	double	magnitude;

	magnitude = vec_len(vec);
	vec.x /= magnitude;
	vec.y /= magnitude;
	vec.z /= magnitude;
	return (vec);
}

t_vec3f	normalize(t_vec3f vec)
{
	double	magnitude;
	double	invert_len;

	magnitude = vec_len(vec);
	if (magnitude > 0)
	{
		invert_len = 1 / magnitude;
		vec.x *= invert_len;
		vec.y *= invert_len;
		vec.z *= invert_len;
	}
	return (vec);
}

t_vec3f	cross_product(t_vec3f vec1, t_vec3f vec2)
{
	t_vec3f	answer;

	answer.x = vec1.y * vec2.z - vec1.z * vec2.y;
	answer.y = vec1.z * vec2.x - vec1.x * vec2.z;
	answer.z = vec1.x * vec2.y - vec1.y * vec2.x;
	return (answer);
}

double	get_angle(t_vec3f vec1, t_vec3f vec2)
{
	return (acos(dot_product(vec1, vec2) / (vec_len(vec1) * vec_len(vec2))));
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

t_vec3f vec_div(t_vec3f vec, double div)
{
	return(vec_mult(vec, 1/div));
}