/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion_set_all.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:43:31 by jjuntune          #+#    #+#             */
/*   Updated: 2022/12/07 11:36:32 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

static int	set_camera_motions(t_cam *cam)
{
	int	motions_done;

	motions_done = 0;
	if (cam->motion.on_off == TRUE
		&& cam->motion.speed_iteration < cam->motion.speed)
	{
		cam->transform = motion_move(cam->transform, &cam->motion);
		motions_done++;
	}
	if (cam->coi_motion.on_off == TRUE
		&& cam->coi_motion.speed_iteration < cam->coi_motion.speed)
	{
		motion_move(cam->coi_transform, &cam->coi_motion);
		motions_done++;
	}
	return (motions_done);
}

int	motion_set_all(t_main *main)
{
	int	i;
	int	motions_done;

	i = 0;
	motions_done = 0;
	while (i < main->obj_count)
	{
		if (main->obj[i].motion.on_off == TRUE
			&& main->obj[i].motion.speed_iteration < main->obj[i].motion.speed)
		{
				main->obj[i].transform = motion_move(main->obj[i].transform,
					&main->obj[i].motion);
			motions_done++;
		}
		i++;
	}
	motions_done += set_camera_motions(&main->cam);
	return (motions_done);
}
