/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_prepare.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 13:26:33 by mmakinen          #+#    #+#             */
/*   Updated: 2022/12/13 13:35:59 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/input.h"

int	prepare_objects(t_xml_nodelist *list, t_vec *objects)
{
	t_matrix	rotate;
	t_object	obj;
	int			index;

	index = 0;
	if (list->size == 0)
	{
		ft_putendl_fd("Error: no objects in input", 2);
		return (FALSE);
	}
	while (index < list->size)
	{
		if (!get_object(xml_nodelist_at(list, index), &obj))
			return (FALSE);
		obj.transform = matrix_translate_2(obj.loc);
		rotate = matrix_rotate_x(obj.rot.a[0]);
		obj.transform = matrix_multiply(&obj.transform, &rotate);
		rotate = matrix_rotate_y(obj.rot.a[1]);
		obj.transform = matrix_multiply(&obj.transform, &rotate);
		rotate = matrix_rotate_z(obj.rot.a[2]);
		obj.transform = matrix_multiply(&obj.transform, &rotate);
		rotate = matrix_scale(obj.scale.a[0], obj.scale.a[1], obj.scale.a[2]);
		obj.transform = matrix_multiply(&obj.transform, &rotate);
		printf("objects = %p\nobj = %p\n", objects, &obj);
		vec_push(objects, &obj);
		index++;
	}
	return (TRUE);

}

int	prepare_camera(t_xml_nodelist *list, t_cam *cam)
{

	if (list->size != 1)
	{
		if (list->size < 1)
			ft_putendl_fd("Error: no camera in input", 2);
		if (list->size > 1)
			ft_putendl_fd("Error: too many cameras in input", 2);
		return (FALSE);
	}
	cam->coi = point_new(0.0, 0.0, 0.0);
	get_camera(list->list[0], cam);
	cam->coi_transform = matrix_translate_2(cam->coi);
	cam->motion = motion_new(FALSE, 5.0, tuple_unit(vector_new(1, 0, 0)));
	cam->coi_motion = motion_new(FALSE, 5.0, tuple_unit(vector_new(1, 0, 0)));
	initialize_camera(cam, matrix_translate_2(cam->pos));
	return (TRUE);
}

/*TODO needs improvement, the type while loop could overwrite itself, needs error check*/
int	prepare_lights(t_xml_nodelist *list, t_vec *lights)
{
	int			index;
	t_light		light;
	t_xml_node	*node;
	char		*value;

	index = 0;
	if (list->size == 0)
	{
		ft_putendl_fd("Error: no lights in input", 2);
		return (FALSE);
	}
	while (index < list->size)
	{
		node = xml_nodelist_at(list, index);
		value = xml_node_attr_value(node, "type");
		if (!ft_strcmp(value, "sun"))
			light.type = SUN;
		else
			light.type = POINT;
		get_light(node, &light);
		vec_push(lights, &light);
	}
	return (TRUE);
}
