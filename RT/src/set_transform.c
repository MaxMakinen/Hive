/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_transform.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:56:35 by jsaarine          #+#    #+#             */
/*   Updated: 2022/11/09 14:37:46 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

	// Do we want this to set the obj transform to the new one, like this
	//				vvvv
	// obj->transform = *transform;

	// Or add to it, like this vvvv?
void	set_transform(t_object *obj, t_matrix *transform)
{
	obj->transform = matrix_multiply(&obj->transform, transform);
}
