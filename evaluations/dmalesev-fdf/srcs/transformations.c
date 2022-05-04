/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 12:24:32 by dmalesev          #+#    #+#             */
/*   Updated: 2022/05/03 12:25:22 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	matrix_multip(t_3d *in, t_3d *out, t_mat *matrix)
{
	float	temp;

	(*out).x = (*in).x * ((*matrix).m[0][0]) + (*in).y * ((*matrix).m[1][0])
		+ (*in).z * ((*matrix).m[2][0]) + ((*matrix).m[3][0]);
	(*out).y = (*in).x * ((*matrix).m[0][1]) + (*in).y * ((*matrix).m[1][1])
		+ (*in).z * ((*matrix).m[2][1]) + ((*matrix).m[3][1]);
	(*out).z = (*in).x * ((*matrix).m[0][2]) + (*in).y * ((*matrix).m[1][2])
		+ (*in).z * ((*matrix).m[2][2]) + ((*matrix).m[3][2]);
	temp = (*in).x * ((*matrix).m[0][3]) + (*in).y * ((*matrix).m[1][3])
		+ (*in).z * ((*matrix).m[2][3]) + ((*matrix).m[3][3]);
	if (temp != 0)
	{
		(*out).x /= temp;
		(*out).y /= temp;
		(*out).z /= temp;
	}
}

void	scale_into_view(t_utils *utils, float *x, float *y)
{
	*x += 1;
	*y += 1;
	*x *= utils->img.max_x / 2;
	*y *= utils->img.max_y / 2;
	*x += utils->map_x;
	*y += utils->map_y;
}

void	scale_depth(t_utils *utils, float *z)
{
	*z -= utils->scale * 2000;
}
