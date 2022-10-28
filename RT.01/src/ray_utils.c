/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:26:21 by mmakinen          #+#    #+#             */
/*   Updated: 2022/10/11 15:26:34 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec3f	get_intersect(t_vec3f origin, t_vec3f direction, double distance)
{
	t_vec3f	intersect;

	intersect.x = origin.x + direction.x * distance;
	intersect.y = origin.y + direction.y * distance;
	intersect.z = origin.z + direction.z * distance;
	return (intersect);
}

int	check_intersect(t_obj *obj, t_ray *ray, t_hit *hit)
{
	double	intersect;
	double	t1;
	int		check;

	intersect = INFINITY;
	check = FALSE;
	if (obj->type == e_sphere)
		check = sphere_intersect(ray, obj, &intersect, &t1);
	else if (obj->type == e_plane)
		check = plane_intersect(ray, obj, &intersect, &t1);
	else if (obj->type == e_cylinder)
		check = cylinder_intersect(ray, obj, &intersect, &t1);
	else if (obj->type == e_cone)
		check = cone_intersect(ray, obj, &intersect, &t1);
	else if (obj->type == e_disc)
		check = disc_intersect(ray, obj, &intersect, &t1);
	else if (obj->type == e_box)
		check = aabb_intersect(ray, obj, &intersect, &t1);
	else if (obj->type == e_triangle)
		check = triangle_intersect(ray, obj, &intersect, &t1);
	if (check == TRUE && intersect < hit->dist)
	{
		hit->dist = intersect;
		hit->obj = obj;
		return (TRUE);
	}
	return (FALSE);
}

t_vec3f	get_direction(t_data *data, double x, double y, t_scene *scene)
{
	t_vec3f	direction;

	x /= (data->screen_max.x - 1.0);
	y /= (data->screen_max.y - 1.0);
	direction = vec_minus(vec_plus(vec_plus(scene->lower_left, \
	vec_mult(scene->horizontal, x)), \
	vec_mult(scene->vertical, y)), scene->cam->pos);
	return (direction);
}

t_obj	*get_obj(t_obj *head, enum e_type type)
{
	while (head && head->next != NULL && head->type != type)
		head = head->next;
	if (head->type != type)
		return (NULL);
	else
		return (head);
}
