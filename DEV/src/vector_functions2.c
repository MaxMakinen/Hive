/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:54:54 by jjuntune          #+#    #+#             */
/*   Updated: 2022/10/12 12:54:57 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

t_vec3	multiply_vect_float(t_vec3 a, double b)
{
	t_vec3	new;

	new.x = (a.x * b);
	new.y = (a.y * b);
	new.z = (a.z * b);
	return (new);
}

t_vec3	div_vect_float(t_vec3 a, double b)
{
	t_vec3	new;

	if (a.x == 0.0 && b == 0.0)
		new.x = 0;
	else
		new.x = a.x / b;
	if (a.y == 0.0 && b == 0.0)
		new.y = 0;
	else
		new.y = a.y / b;
	if (a.z == 0.0 && b == 0.0)
		new.z = 0;
	else
		new.z = a.z / b;
	return (new);
}

t_vec3	add_vect_float(t_vec3 a, double b)
{
	t_vec3	new;

	new.x = (a.x + b);
	new.y = (a.y + b);
	new.z = (a.z + b);
	return (new);
}

t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	t_vec3	new;

	new.x = ((a.y * b.z) - (a.z * b.y));
	new.y = ((a.z * b.x) - (a.x * b.z));
	new.z = ((a.x * b.y) - (a.y * b.x));
	return (new);
}

double	vec3_sqr(t_vec3 a)
{
	t_vec3	new;

	new.x = (a.x * a.x);
	new.y = (a.y * a.y);
	new.z = (a.z * a.z);
	return (new.x + new.y + new.z);
}
