/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 19:53:19 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/26 14:11:58 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	eraser(t_list *lst)
{
	if (lst != 0)
	{
		eraser(lst->next);
		free(lst);
		lst = NULL;
	}
}

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*node;
	t_list	*new;
	t_list	*temp;
	t_list	*head;

	node = lst;
	new = malloc(sizeof(new));
	if (new == 0)
		return (NULL);
	head = new;
	while (node != 0)
	{
		new = f(node);
		temp = malloc(sizeof(temp));
		if (temp == 0)
		{
			eraser(head);
			return (NULL);
		}
		new->next = temp;
		new = new->next;
		node = node->next;
	}
	return (head);
}
