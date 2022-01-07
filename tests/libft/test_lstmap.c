/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lstmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 12:33:23 by mmakinen          #+#    #+#             */
/*   Updated: 2022/01/07 09:43:19 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*lstupper(t_list *elem)
{
	char	*temp;
	char	*tomp;
	t_list	*newlst;

	temp = elem->content;
	tomp = malloc(ft_strlen(temp) + 1);
	newlst->content = tomp;
	while (*temp != 0)
	{
		*tomp++ = ft_toupper(*temp++);
	}
	newlst->content_size = elem->content_size * 2;
	return (newlst);
}

void	lstprinter(t_list *lst)
{
	char	*temp;
	size_t		num;
	while (lst)
	{
		temp = lst->content;
		num = lst->content_size;
		ft_putstr(temp);
		ft_putchar(' ');
		ft_putnbr(num);
		ft_putchar('\n');
		lst = lst->next;
	}
}

int	main(void)
{
	t_list	*head;
	t_list	*new;
	t_list	*maphead;
//	char	*q;
	char	*p = "pop";

	maphead = malloc(sizeof(t_list));
	new = ft_lstnew(p, 4);
	head = new;
	new->next = ft_lstnew(p, 4);
	new->next->next = ft_lstnew(p, 4);
	lstupper(new->next->next);
	maphead = ft_lstmap(head, lstupper);
	lstprinter(head);
	ft_putendl("-:-\n");
	lstprinter(maphead);
	return (0);
}
