/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:23:34 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/26 14:43:24 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*node;

	if (alst != 0)
	{
		node = *alst;
		del(node->content, node->content_size);
		node->content_size = 0;
		if (node->next != NULL)
		{
			*alst = node->next;
			ft_lstdel(alst, del);
			node->next = NULL;
		}
		free(node);
		node = NULL;
		alst = NULL;
	}
}
