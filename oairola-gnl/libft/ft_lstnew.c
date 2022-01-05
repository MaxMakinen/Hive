/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oairola <oairola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 14:04:53 by oairola           #+#    #+#             */
/*   Updated: 2021/12/13 09:39:56 by oairola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t	content_size)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (new_node == NULL)
		return (NULL);
	if (content != NULL)
	{
		new_node->content = malloc(content_size);
		if (new_node == NULL)
		{
			free(new_node);
			return (NULL);
		}
		ft_memcpy(new_node->content, content, content_size);
		new_node->content_size = content_size;
		new_node->next = NULL;
	}
	else
	{
		new_node->content = NULL;
		new_node->content_size = 0;
		new_node->next = NULL;
	}
	return (new_node);
}
