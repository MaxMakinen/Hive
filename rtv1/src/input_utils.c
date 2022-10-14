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

int	get_vector(t_vec3f *vector, char **words)
{
	vector->x = ft_atod(words[0]);
	vector->y = ft_atod(words[1]);
	vector->z = ft_atod(words[2]);
	return (TRUE);
}

t_obj	*init_obj(void)
{
	t_obj	*new;

	new = ft_calloc(sizeof(t_obj), 1);
	if (new)
	{
		new->next = NULL;
		new->color.color = WHITE;
		new->dir = (t_vec3f){0.0, 1.0, 0.0};
	}
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
