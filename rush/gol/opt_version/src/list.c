/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leotran <leotran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 12:12:00 by mmakinen          #+#    #+#             */
/*   Updated: 2022/06/23 17:24:11 by leotran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gol.h"

t_list	*new_list(int row, int col)
{
	t_list	*list;

	list = (t_list *)malloc(sizeof(t_list));
	list->row = row;
	list->col = col;
	list->next = NULL;
	list->prev = NULL;
	return (list);
}

t_list	*stack_add(t_list *list, int row, int col)
{
	t_list	*n_list;

	n_list = new_list(row, col);
	list->next = (struct s_list *)n_list;
	n_list->prev = (struct s_list *)list;
	return (n_list);
}

t_list	*stack_pop(t_list *list)
{
	t_list	*temp;

	if (list == NULL)
		return (NULL);
	temp = list;
	list = list->prev;
	free(temp);
	if (list == NULL)
		return (NULL);
	else
		list->next = NULL;
	return (list);
}

t_list	*get_stack_end(t_list *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

void	print_list(t_list *head)
{
	while (head)
	{
		// printf("row = %d col = %d list = %p\n", head->col, head->row, head);
		head = head->next;
	}
}
