/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:40:58 by mmakinen          #+#    #+#             */
/*   Updated: 2022/10/11 12:41:00 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_obj	*init_obj(t_data *data)
{
	t_obj	*new;

	new = ft_calloc(sizeof(t_obj), 1);
	if (new)
	{
		new->next = NULL;
		new->color.color = WHITE;
		new->col = (t_vec3f){1.0, 1.0, 1.0};
		new->n = 10;
		new->ks = 0.2;
		new->kd = 0.8;
		new->brightness = 1000;
		new->dir = (t_vec3f){0.0, 1.0, 0.0};
	}
	else
		clean_exit(data);
	return (new);
}

t_obj	*get_last(t_obj *head)
{
	t_obj	*temp;

	temp = head;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

void	get_color(t_obj *temp, int col)
{
	temp->color.color = col;
	temp->col.x = ft_norm((double)temp->color.rgb[0], 0.0, 255.0);
	temp->col.y = ft_norm((double)temp->color.rgb[1], 0.0, 255.0);
	temp->col.z = ft_norm((double)temp->color.rgb[2], 0.0, 255.0);
}

void	get_description(t_obj *temp, char **words)
{	
	if (ft_strcmp(words[1], "brightness") == 0)
		temp->brightness = ft_atod(words[2]);
	else if (ft_strcmp(words[1], "pattern") == 0)
		temp->pattern = ft_atoi(words[2]);
	else if (ft_strcmp(words[1], "shiny") == 0)
		temp->shiny = ft_atoi(words[2]);
	else if (ft_strcmp(words[1], "n") == 0)
		temp->n = ft_atod(words[2]);
	else if (ft_strcmp(words[1], "kd") == 0)
		temp->kd = ft_atod(words[2]);
	else if (ft_strcmp(words[1], "ks") == 0)
		temp->ks = ft_atod(words[2]);
	else if (ft_strcmp(words[1], "color") == 0)
		get_color(temp, ft_atoi(words[2]));
}
