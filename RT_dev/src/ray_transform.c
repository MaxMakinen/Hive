/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_transform.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 14:44:03 by jsaarine          #+#    #+#             */
/*   Updated: 2022/11/11 17:14:15 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_ray	ray_transform(t_ray *source, t_matrix *transform)
{
	t_point		p;
	t_vector	v;
	t_ray		result;

	p = matrix_tuple_multiply(transform, &source->orig);
	v = matrix_tuple_multiply(transform, &source->dir);
	result = ray_new_no_malloc(p, v);
	result.hit = source->hit;
	result.xs = source->xs;
	return (result);
}
