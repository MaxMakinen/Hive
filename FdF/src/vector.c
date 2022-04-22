/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:35:16 by mmakinen          #+#    #+#             */
/*   Updated: 2022/04/22 10:49:43 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


t_vector	*prep_vector(t_vector *vector)
{
	vector = malloc(sizeof(vector));
	vector->x = 0;
	vector->y = 0;
	vector->z = 0;
	return (vector);
}

t_vector *vec_mult(t_vector *vect, float num)
{
	vect->x *= num;
	vect->y *= num;
	vect->z *= num;
	return (vect);
}

t_vector *vec_add(t_vector *vect, float num)
{
	vect->x += num;
	vect->y += num;
	vect->z += num;
	return (vect);
}

t_vector *vec_subt(t_vector *vect, float num)
{
	vect->x -= num;
	vect->y -= num;
	vect->z -= num;
	return (vect);
}

t_vector *vec_div(t_vector *vect, float num)
{
	if (num != 0)
	{
		vect->x /= num;
		vect->y /= num;
		vect->z /= num;
	}
	else 
		(write(1,"div 0 error\n", 12));
	return (vect);
}

t_vector *vec_adjust(t_vector *vec, int x, int y)
{
	vec->x += (float)x;
	vec->y += (float)y;
	return (vec);
}
