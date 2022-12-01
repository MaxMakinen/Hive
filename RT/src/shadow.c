/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 20:44:38 by jjuntune          #+#    #+#             */
/*   Updated: 2022/11/09 15:43:37 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

void	ofset_dir(t_ray *shadow)
{
	double	ofset_dist;

	ofset_dist = 0.001;
	shadow->orig.s_xyzw.x += (shadow->hit.normal.s_xyzw.x * ofset_dist);
	shadow->orig.s_xyzw.y += (shadow->hit.normal.s_xyzw.y * ofset_dist);
	shadow->orig.s_xyzw.z += (shadow->hit.normal.s_xyzw.z * ofset_dist);
}

void	ofset_plane_dir(t_ray *shadow)
{
	double	ofset_dist;

	ofset_dist = 0.001;
	shadow->orig.s_xyzw.x -= (shadow->hit.normal.s_xyzw.x * ofset_dist);
	shadow->orig.s_xyzw.y -= (shadow->hit.normal.s_xyzw.y * ofset_dist);
	shadow->orig.s_xyzw.z -= (shadow->hit.normal.s_xyzw.z * ofset_dist);
}

/*
** declear swhadow ray so we can check if the shape is in the shadow
*/

void	offset_and_declare_shadow_ray(t_main *main, t_ray *ray, t_ray *shadow)
{
	shadow->orig = ray->hit.hit_loc;
	shadow->dir = tuple_sub(main->light.pos, shadow->orig);
	shadow->hit = ray->hit;
	shadow->hit.hit_dist = tuple_mag(shadow->dir);
	shadow->dir = tuple_unit(shadow->dir);
	if (main->obj[ray->hit.clo_obj_id].type == 2)
		ofset_plane_dir(shadow);
	else
		ofset_dir(shadow);
}

int	check_shadow(t_main *main, t_ray *ray)
{
	double	ret;
	int		count;

	count = 0;
	ret = -1;
	offset_and_declare_shadow_ray(main, ray, &main->shadow);
	while (count < main->obj_count && ret < 0.000000)
	{
		ret = get_shape_intersections(&main->shadow, &main->obj[count]);
		count++;
		if (ret >= main->shadow.hit.hit_dist || ret < 0)
			ret = -1.0;
	}
	if (ret < 0.0)
		return (0);
	return (1);
}
