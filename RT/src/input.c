/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 13:26:33 by mmakinen          #+#    #+#             */
/*   Updated: 2022/11/30 13:26:34 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/yaxml.h"
#include "../include/rt.h"

void	get_tuple(t_tuple *tuple, char *str)
{
	int	index;
	int	index_t = 0;

	index = 0;
	while (str[index] != '\0')
	{
		if (str[index] == ' ' && str[index + 1] != '\0')
		{
			tuple->a[index_t++] = ft_atof(&str[index + 1]);
		}
		index++;
	}
}

int	get_material(t_xml_node *node, t_material *mat)
{
	t_xml_attr	*attr;
	int			index;
	t_tuple		col;

	index = 0;
	if (node->attributes.size == 0)
		return (FALSE);
	while (index < node->attributes.size)
	{
		attr = &node->attributes.list[index];
		if (!ft_strcmp(attr->key, "pattern") && !ft_strcmp(attr->value, "grid"))
		{
			mat->pattern.pattern_id = GRID;
		}
		if (!ft_strcmp(attr->key, "pattern") && !ft_strcmp(attr->value, "none"))
		{
			mat->pattern.pattern_id = NONE;
		}
		else if (!ft_strcmp(attr->key, "perlin") && !ft_strcmp(attr->value, "true"))
		{
			mat->pattern.pattern_perlin = TRUE;
		}
		else if (!ft_strcmp(attr->key, "perlin") && !ft_strcmp(attr->value, "false"))
		{
			mat->pattern.pattern_perlin = FALSE;
		}
		index++;
	}
	get_tuple(&col, node->data);
	mat->color = color_new(col.a[0], col.a[1], col.a[2]);
	return (TRUE);
}

int	get_light(t_xml_node *node, t_light *light)
{
	t_xml_node	*temp;
	int			index;

	index = 0;
	while (index < node->children.size)
	{
		temp = node->children.list[index];
		if (!ft_strcmp(temp->tag, "pos"))
		{
			get_tuple(&light->location, temp->data);
		}
		else if (!ft_strcmp(temp->tag, "brightness") || !ft_strcmp(temp->tag, "color"))
		{
			get_tuple(&light->intensity, temp->data);
		}
		index++;
	}
	return (TRUE);
}

int	get_camera(t_xml_node *node, t_cam *cam)
{
	t_xml_node	*temp;
	int			index;

	index = 0;
	while (index < node->children.size)
	{
		temp = node->children.list[index];
		if (!ft_strcmp(temp->tag, "pos"))
		{
			get_tuple(&cam->pos, temp->data);
		}
		else if (!ft_strcmp(temp->tag, "coi"))
		{
			get_tuple(&cam->coi, temp->data);
		}
		else if (!ft_strcmp(temp->tag, "v_up"))
		{
			get_tuple(&cam->v_up, temp->data);
		}
		else if (!ft_strcmp(temp->tag, "rot"))
		{
			get_tuple(&cam->rot, temp->data);
		}
		index++;
	}
	return (TRUE);
}

int	get_object(t_xml_node *node, t_object *obj)
{
	t_xml_attr	*attr;
	t_xml_node	*temp;
	int			index;

	index = 0;
	if (node->attributes.size == 0)
		return (FALSE);
	while (index < node->attributes.size)
	{
		attr = &node->attributes.list[index];
		if (!ft_strcmp(attr->key, "type") && !ft_strcmp(attr->value, "sphere"))
		{
			*obj = object_new(SPHERE);
			break;
		}
		else if (!ft_strcmp(attr->key, "type") && !ft_strcmp(attr->value, "cylinder"))
		{
			*obj = object_new(CYLINDER);
			break;
		}
		else if (!ft_strcmp(attr->key, "type") && !ft_strcmp(attr->value, "plane"))
		{
			*obj = object_new(PLANE);
			break;
		}
		else if (!ft_strcmp(attr->key, "type") && !ft_strcmp(attr->value, "cone"))
		{
			*obj = object_new(CONE);
			break;
		}
		else if (!ft_strcmp(attr->key, "type") && !ft_strcmp(attr->value, "sun"))
		{
			*obj = object_new(SUN);
			break;
		}
		else if (!ft_strcmp(attr->key, "type") && !ft_strcmp(attr->value, "point"))
		{
			*obj = object_new(POINT);
			break;
		}
		else if (!ft_strcmp(attr->key, "negative") && !ft_strcmp(attr->value, "true"))
		{
			obj->negative = TRUE;
		}
		else if (!ft_strcmp(attr->key, "negative") && !ft_strcmp(attr->value, "false"))
		{
			obj->negative = FALSE;
		}
		index++;
	}
	index = 0;
	while (index < node->children.size)
	{
		temp = node->children.list[index];
		if (!ft_strcmp(temp->tag, "loc"))
		{
			get_tuple(&obj->loc, temp->data);
		}
		else if (!ft_strcmp(temp->tag, "coi"))
		{
			get_tuple(&obj->coi, temp->data);
		}
		else if (!ft_strcmp(temp->tag, "up"))
		{
			get_tuple(&obj->up, temp->data);
		}
		else if (!ft_strcmp(temp->tag, "rot"))
		{
			get_tuple(&obj->rot, temp->data);
		}
		else if (!ft_strcmp(temp->tag, "color"))
		{
			get_tuple(&obj->color, temp->data);
		}
		else if (!ft_strcmp(temp->tag, "scale"))
		{
			get_tuple(&obj->scale, temp->data);
		}
		else if (!ft_strcmp(temp->tag, "size"))
		{
			obj->size = ft_atof(temp->data);
		}
		else if (!ft_strcmp(temp->tag, "brightness"))
		{
			obj->brightness = ft_atof(temp->data);
		}
		else if (!ft_strcmp(temp->tag, "material"))
		{
			if(!get_material(temp, &obj->material))
			{
				ft_putendl_fd("ERROR: Failed to get material info", 2);
				return (FALSE);
			}
		}
		index++;
	}
	return (TRUE);
}

int	read_xml(t_xml_doc *doc, t_main *main)
{
	t_xml_node	*node;
	int			index;
	t_matrix	rotate;
	t_object	*obj;
	int			obj_count = 0;

	index = 0;
	node = doc->head;
	while (index < node->children.size)
	{
		if (!ft_strcmp(node->children.list[index]->tag, "object"))
		{
			printf("BEEP\n");
			obj = &main->obj[obj_count];
			get_object(node->children.list[index], obj);
			obj->transform = matrix_translate(obj->loc.a[0], obj->loc.a[1], obj->loc.a[2]);
			rotate = matrix_rotate_x(obj->rot.a[0]);
			obj->transform = matrix_multiply(&obj->transform, &rotate);
			rotate = matrix_rotate_y(obj->rot.a[1]);
			obj->transform = matrix_multiply(&obj->transform, &rotate);
			rotate = matrix_rotate_z(obj->rot.a[2]);
			obj->transform = matrix_multiply(&obj->transform, &rotate);
			rotate = matrix_scale(obj->scale.a[0], obj->scale.a[1], obj->scale.a[2]);
			obj->transform = matrix_multiply(&obj->transform, &rotate);
			obj_count++;
		}
		else if (!ft_strcmp(node->children.list[index]->tag, "camera"))
		{
			main->cam.coi = point_new(0.0, 0.0, 0.0);
			get_camera(node->children.list[index], &main->cam);
			initialize_camera(&main->cam, matrix_translate(main->cam.pos.a[0], main->cam.pos.a[1], main->cam.pos.a[2]));
		}
		else if (!ft_strcmp(node->children.list[index]->tag, "light"))
		{
			main->light.location.a[3] = 1.0;
			get_light(node->children.list[index], &main->light);

//			main->light = point_light_new(point_new(main->light.location.a[0], main->light.location.a[1], main->light.location.a[2]),\
//			color_new(main->light.intensity.a[0], main->light.intensity.a[1], main->light.intensity.a[2]));
		}
		index++;
	}
	main->obj_count = obj_count;
	return (TRUE);
}


//void	print_main(t_main *main)
//{
//	int			index;
//	t_object	*obj;
//
//	index = 0;
//	while (index < main->obj_count)
//	{
//		obj = &main->obj[index];
//		printf("OBJECT type = %d\nLOC = %f, %f, %f, %f\n", obj->type, obj->loc.a[0], obj->loc.a[1], obj->loc.a[2], obj->loc.a[3]);
//		printf("coi = %f, %f, %f, %f\n", obj->coi.a[0], obj->coi.a[1], obj->coi.a[2], obj->coi.a[3]);
//		printf("rot = %f, %f, %f, %f\n", obj->rot.a[0], obj->rot.a[1], obj->rot.a[2], obj->rot.a[3]);
//		printf("\n");
//		index++;
//	}
//}
/*
int	main(int ac, char **av)
{
	t_xml_doc	doc;
	t_main		main;

	if (ac != 2)
	{
		printf("Give .xml input file\n");
		return (0);
	}
	if (xml_doc_load(&doc, av[1]))
	{
		printf("XML Document (version=%s, encoding=%s)\n\n", doc.version, doc.encoding);
		read_xml(&doc, &main);
		print_main(&main);
	}
	else
		printf("couldn't load file");
	return (0);
}
*/