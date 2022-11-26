/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin_noice.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:43:24 by jjuntune          #+#    #+#             */
/*   Updated: 2022/11/15 20:05:40 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

double	fade(double t)
{
	return (t * t * t * (t * (t * 6 - 15) + 10));
}

double	lerp(double t, double a, double b)
{
	return (a + t * (b - a));
}

double	grad(int hash, double x, double y, double z)
{
	int		h;
	double	u;
	double	v;

	h = hash & 15;
	if (h < 8)
		u = x;
	else
		u = y;
	if (h < 4)
		v = y;
	else if (h == 12 || h == 14)
		v = z;
	else
		v = x;
	if ((h & 1) == 0)
	{
		if ((h & 2) == 0)
			return (u + v);
		return (u + -v);
	}
	if ((h & 2) == 0)
		return (-u + v);
	return (-u + -v);
}

int	load_perlin_data(t_perlin *perlin)
{
	FILE	*fp;
	int		permutation[256];
	int		i;
//fscanf???????
	if (!(perlin->is_data_writen))
	{
		i = 0;
		fp = fopen("include/perlindata.txt", "r");
		if (fp == NULL)
			return (0);
		while (i < 256)
			fscanf(fp, "%d", &permutation[i++]);
		fclose(fp);
		i = 0;
		while (i < 256)
		{
			perlin->p[i] = permutation[i];
			perlin->p[256 + i] = permutation[i];
			i++;
		}
	}
	return (1);
}

double	calculate_return(t_tuple point, t_perlin *perlin)
{
	double	temp;
	double	temp_a;
	double	temp_b;
	double	temp_c;

	temp = lerp(perlin->u, grad(perlin->p[perlin->ab + 1],
				point.s_xyzw.x, point.s_xyzw.y - 1, point.s_xyzw.z - 1),
			grad(perlin->p[perlin->bb + 1], point.s_xyzw.x - 1,
				point.s_xyzw.y - 1, point.s_xyzw.z - 1));
	temp_a = lerp(perlin->v, lerp(perlin->u,
				grad(perlin->p[perlin->aa + 1], point.s_xyzw.x, point.s_xyzw.y,
					point.s_xyzw.z - 1), grad(perlin->p[perlin->ba + 1],
					point.s_xyzw.x - 1, point.s_xyzw.y, point.s_xyzw.z - 1)), temp);
	temp_b = lerp(perlin->u, grad(perlin->p[perlin->ab], point.s_xyzw.x,
				point.s_xyzw.y - 1, point.s_xyzw.z), grad(perlin->p[perlin->bb],
				point.s_xyzw.x - 1, point.s_xyzw.y - 1, point.s_xyzw.z));
	temp_c = lerp(perlin->w, lerp(perlin->v, lerp(perlin->u,
					grad(perlin->p[perlin->aa], point.s_xyzw.x, point.s_xyzw.y, point.s_xyzw.z),
					grad(perlin->p[perlin->ba], point.s_xyzw.x - 1,
						point.s_xyzw.y, point.s_xyzw.z)), temp_b), temp_a);
	return (temp_c);
}

double	perlin_noice(t_tuple point, t_perlin *perlin)
{
	perlin->x_i = (int)floor(point.s_xyzw.x) & 255;
	perlin->y_i = (int)floor(point.s_xyzw.y) & 255;
	perlin->z_i = (int)floor(point.s_xyzw.z) & 255;
	point.s_xyzw.x -= floor(point.s_xyzw.x);
	point.s_xyzw.y -= floor(point.s_xyzw.y);
	point.s_xyzw.z -= floor(point.s_xyzw.z);
	perlin->u = fade(point.s_xyzw.x);
	perlin->v = fade(point.s_xyzw.y);
	perlin->w = fade(point.s_xyzw.z);
	perlin->a = perlin->p[perlin->x_i] + perlin->y_i;
	perlin->aa = perlin->p[perlin->a] + perlin->z_i;
	perlin->ab = perlin->p[perlin->a + 1] + perlin->z_i;
	perlin->b = perlin->p[perlin->x_i + 1] + perlin->y_i;
	perlin->ba = perlin->p[perlin->b] + perlin->z_i;
	perlin->bb = perlin->p[perlin->b + 1] + perlin->z_i;
	return (calculate_return(point, perlin));
}
