/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:21:04 by mmakinen          #+#    #+#             */
/*   Updated: 2022/08/24 14:22:41 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	rotate(t_obj *object, t_hit *hit)
{
	t_vec3f	temp;
	t_vec3f	temp2;
	double	angle;
	t_vec3f	axis;
	t_quat	quat;

	ft_bzero(&quat, sizeof(quat));
	ft_bzero(&axis, sizeof(axis));
	temp2 = vec_minus(hit->pos, object->pos);
	temp = temp2;
	angle = get_angle(object->dir, (t_vec3f){0.0, 1.0, 0.0});
	if (angle > 0.0)
	{
		axis = normalize(cross_product(object->dir, (t_vec3f){0.0, 1.0, 0.0}));
		quat_from_axis_angle(&axis, angle, &quat);
		quat = quat_normalize(&quat);
		quat_rotate(&quat, &temp2, &temp);
	}
	hit->rotated = temp;
}

t_vec3f	rotate_xyz(t_obj *temp, double angle, t_vec3f axis)
{
	t_vec3f	temp_dir;
	t_quat	quat;

	ft_bzero(&quat, sizeof(quat));
	quat_from_axis_angle(&axis, angle, &quat);
	quat = quat_normalize(&quat);
	quat_rotate(&quat, &temp->dir, &temp_dir);
	return (temp_dir);
}

t_vec3f	rotation(t_obj *temp, char **words)
{
	double	angle;

	if (ft_isnumber(words[1], 10))
		angle = ft_atod(words[1]);
	else
		angle = 0;
	if (ft_strcmp(words[0], "x") == 0)
		return (rotate_xyz(temp, angle, (t_vec3f){1.0, 0.0, 0.0}));
	else if (ft_strcmp(words[0], "y") == 0)
		return (rotate_xyz(temp, angle, (t_vec3f){0.0, 1.0, 0.0}));
	else if (ft_strcmp(words[0], "z") == 0)
		return (rotate_xyz(temp, angle, (t_vec3f){0.0, 0.0, 1.0}));
	else
		return ((t_vec3f){0.0, 1.0, 0.0});
}
