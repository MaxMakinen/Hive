/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_new.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 14:44:03 by jsaarine          #+#    #+#             */
/*   Updated: 2022/11/09 14:36:30 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"

t_intersection	intersection_new(double time, t_object *o)
{
	t_intersection	xs;

	xs.t = time;
	xs.object = o;
	return (xs);
}
