/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 10:02:43 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/26 14:32:55 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list			*newnode;
	unsigned char	*newcont;

	newnode = malloc(sizeof(t_list));
	if (newnode == 0)
		return (NULL);
	if (content == 0)
	{
		newnode->content = NULL;
		newnode->content_size = 0;
	}
	else
	{
		newcont = malloc(sizeof(*newcont) * (content_size));
		if (newcont == 0)
		{
			free(newnode);
			return (NULL);
		}
		newcont = ft_memcpy(newcont, content, content_size);
		newnode->content = newcont;
		newnode->content_size = content_size;
		newnode->next = NULL;
	}
	return (newnode);
}
