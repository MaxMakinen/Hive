/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:05:22 by dmalesev          #+#    #+#             */
/*   Updated: 2022/05/03 14:08:49 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_pmatrix(t_utils *u)
{
	float	z_diff;

	z_diff = u->proj.z_far - u->proj.z_near;
	(u->pmatrix.m)[0][0] = (u->proj.asp_ratio) * (u->proj.fov_rad);
	(u->pmatrix.m)[1][1] = (u->proj.fov_rad);
	(u->pmatrix.m)[2][2] = (u->proj.z_far) / (z_diff);
	(u->pmatrix.m)[3][2] = (-(u->proj.z_far) * (u->proj.z_near)) / z_diff;
	(u->pmatrix.m)[2][3] = 1;
	(u->pmatrix.m)[3][3] = 0;
}

void	init_rmatrix_x(t_utils *utils)
{
	utils->rmatrix_x.m[0][0] = 1;
	utils->rmatrix_x.m[1][1] = cos(utils->rot.alpha / 180 * PI);
	utils->rmatrix_x.m[1][2] = sin(utils->rot.alpha / 180 * PI);
	utils->rmatrix_x.m[2][1] = -sin(utils->rot.alpha / 180 * PI);
	utils->rmatrix_x.m[2][2] = cos(utils->rot.alpha / 180 * PI);
	utils->rmatrix_x.m[3][3] = 1;
}

void	init_rmatrix_y(t_utils *utils)
{
	utils->rmatrix_y.m[0][0] = cos(utils->rot.beta / 180 * PI);
	utils->rmatrix_y.m[0][2] = -sin(utils->rot.beta / 180 * PI);
	utils->rmatrix_y.m[1][1] = 1;
	utils->rmatrix_y.m[2][0] = sin(utils->rot.beta / 180 * PI);
	utils->rmatrix_y.m[2][2] = cos(utils->rot.beta / 180 * PI);
	utils->rmatrix_y.m[3][3] = 1;
}

void	init_rmatrix_z(t_utils *utils)
{
	utils->rmatrix_z.m[0][0] = cos(utils->rot.gamma / 180 * PI);
	utils->rmatrix_z.m[0][1] = sin(utils->rot.gamma / 180 * PI);
	utils->rmatrix_z.m[1][0] = -sin(utils->rot.gamma / 180 * PI);
	utils->rmatrix_z.m[1][1] = cos(utils->rot.gamma / 180 * PI);
	utils->rmatrix_z.m[2][2] = 1;
	utils->rmatrix_z.m[3][3] = 1;
}

void	init_matrix(t_mat *matrix)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			((*matrix).m)[i][j] = 0;
			j++;
		}
		i++;
	}
}
