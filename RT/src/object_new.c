/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:35:17 by jjuntune          #+#    #+#             */
/*   Updated: 2022/11/13 16:47:16 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

t_object	object_new(int shape_type)
{
	static size_t	id;
	t_object		new_object;

	new_object.transform = matrix_new_identity(4);
	new_object.id = id;
	id++;
	new_object.loc = point_new(0, 0, 0);
	new_object.size = 1.0;
	new_object.type = shape_type;
	new_object.material = material_new();
	return (new_object);
}
