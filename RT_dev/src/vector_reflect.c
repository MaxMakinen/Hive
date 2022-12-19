/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_reflect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:45:59 by jsaarine          #+#    #+#             */
/*   Updated: 2022/12/12 14:27:48 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuple.h"

t_vector	vector_reflect(t_vector in, t_vector normal)
{
	return (tuple_sub(in,
			tuple_scalar_mult(normal, 2 * vector_dot(in, normal))));
}
