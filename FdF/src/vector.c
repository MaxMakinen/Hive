/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:35:16 by mmakinen          #+#    #+#             */
/*   Updated: 2022/04/20 15:46:20 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


t_vector	*prep_vector(t_vector *vector)
{
	vector->x = 0;
	vector->y = 0;
	vector->z = 0;
	vector->w = 1;
	return (vector);
}

t_vector vect_mult(t_vector vect, int num)
{
	vect.x *= num;
	vect.y *= num;
	vect.z *= num;
	return (vect);
}

t_vector *vect_add(t_vector *vect, int num)
{
	vect->x += num;
	vect->y += num;
	//vect->z += num;
	return (vect);
}

t_vector *vect_subt(t_vector *vect, int num)
{
	vect->x -= num;
	vect->y -= num;
	vect->z -= num;
	return (vect);
}

t_vector *vect_div(t_vector *vect, int num)
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
