/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:32:00 by jsaarine          #+#    #+#             */
/*   Updated: 2022/11/15 18:29:26 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_material	material_new()
{
	t_material	m;

 	m.ambient = 0.1;
 	m.diffuse = 0.9;
 	m.color = color_new(1, 1, 1);
	m.shininess = 200.0;
 	m.specular = 0.9;
	m.pattern.pattern_dif = 0.9;
	return (m);
}