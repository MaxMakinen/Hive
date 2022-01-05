/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oairola <oairola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 14:04:53 by oairola           #+#    #+#             */
/*   Updated: 2021/11/22 09:39:24 by oairola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*temp;

	temp = (*alst);
	while (temp != NULL)
	{
		temp = temp->next;
		del((*alst)->content, (*alst)->content_size);
		(*alst)->next = NULL;
		free(*alst);
		*alst = temp;
	}
}
