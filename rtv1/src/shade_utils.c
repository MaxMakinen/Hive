/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 10:20:32 by mmakinen          #+#    #+#             */
/*   Updated: 2022/10/14 10:20:33 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec3f	gamma_correct(t_vec3f color)
{
	t_vec3f	temp;

	color.x = ft_clamp(color.x, 0, 255);
	color.y = ft_clamp(color.y, 0, 255);
	color.z = ft_clamp(color.z, 0, 255);
	temp.x = pow(color.x, (1 / GAMMA));
	temp.y = pow(color.y, (1 / GAMMA));
	temp.z = pow(color.z, (1 / GAMMA));
	return (temp);
}
