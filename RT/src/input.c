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

	index = 0;
	while (*str != '\0')
	{
		while (ft_isspace(*str))
			str++;
		if (!str)
			break;
		tuple->a[index] = ft_atof(str);
		while(ft_isalnum(*str))
			str++;
		if (!str)
			break;
		index++;
	}
}

int	get_material(t_xml_node *node, t_object *obj)
{
	t_xml_attr	*attr;
	int			index;

	index = 0;
	if (node->attributes.size == 0)
		return (FALSE);
	while (index < node->attributes.size)
	{
		attr = &node->attributes.list[index];
		if (!ft_strcmp(attr->key, "pattern") && !ft_strcmp(attr->key, "grid"))
		{
			obj->material.pattern.pattern_id = GRID;
		}
		else if (!ft_strcmp(attr->key, "perlin") && !ft_strcmp(attr->key, "false"))
		{
			obj->material.pattern.pattern_id = FALSE;
		}
		index++;
	}
	get_tuple(&obj->material.color, node->data);
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
		if (!ft_strcmp(attr->key, "type") && !ft_strcmp(attr->key, "sphere"))
		{
			*obj = object_new(SPHERE);
			break;
		}
		if (!ft_strcmp(attr->key, "type") && !ft_strcmp(attr->key, "cylinder"))
		{
			*obj = object_new(CYLINDER);
			break;
		}
		if (!ft_strcmp(attr->key, "type") && !ft_strcmp(attr->key, "plane"))
		{
			*obj = object_new(PLANE);
			break;
		}
		if (!ft_strcmp(attr->key, "type") && !ft_strcmp(attr->key, "cone"))
		{
			*obj = object_new(CONE);
			break;
		}
		if (!ft_strcmp(attr->key, "type") && !ft_strcmp(attr->key, "sun"))
		{
			*obj = object_new(SUN);
			break;
		}
		if (!ft_strcmp(attr->key, "type") && !ft_strcmp(attr->key, "point"))
		{
			*obj = object_new(POINT);
			break;
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
		else if (!ft_strcmp(temp->tag, "size"))
		{
			obj->size = ft_atof(temp->data);
		}
		else if (!ft_strcmp(temp->tag, "brightness"))
		{
			obj->brightness = ft_atof(temp->data);
		}
		index++;
	}
	return (TRUE);
}

int	read_xml(t_xml_doc *doc, t_main *main)
{
	t_xml_node	*node;
	int			index;
	int			obj_amount = 0;
	t_matrix	rotate;
	t_object	*obj;

	index = 0;
	node = doc->head;
	while (index < node->children.size)
	{
		if (!ft_strcmp(node->children.list[index]->tag, "object"))
		{
			obj = &main->obj[obj_amount];
			get_object(node, obj);
			obj->transform = matrix_translate(obj->loc.a[0], obj->loc.a[1], obj->loc.a[2]);
			rotate = matrix_rotate_x(obj->rot.s_xyzw.x);
			obj->transform = matrix_multiply(&obj->transform, &rotate);
			rotate = matrix_rotate_y(obj->rot.s_xyzw.y);
			obj->transform = matrix_multiply(&obj->transform, &rotate);
			rotate = matrix_rotate_z(obj->rot.s_xyzw.z);
			obj->transform = matrix_multiply(&obj->transform, &rotate);
			obj_amount++;
		}
		index++;
	}
	main->obj_count = obj_amount;
	return (TRUE);
}

void	print_main(t_main *main)
{
	int			index;
	t_object	*obj;

	index = 0;
	while (index < main->obj_count)
	{
		obj = &main->obj[index];
		printf("OBJECT type = %d\nLOC = %f, %f, %f, %f\n", obj->type, obj->loc.a[0], obj->loc.a[1], obj->loc.a[2], obj->loc.a[3]);
		printf("coi = %f, %f, %f, %f\n", obj->coi.a[0], obj->coi.a[1], obj->coi.a[2], obj->coi.a[3]);
		printf("rot = %f, %f, %f, %f\n", obj->rot.a[0], obj->rot.a[1], obj->rot.a[2], obj->rot.a[3]);
		printf("\n");
		index++;
	}
}
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