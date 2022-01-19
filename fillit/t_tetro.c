/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_tetro.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 18:52:28 by mmakinen          #+#    #+#             */
/*   Updated: 2022/01/19 18:55:19 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
function to make new t_tetro node.
*/

t_tetro	*new_tetro(char letter)
{
	t_tetro	*newnode;

	newnode = (t_tetro *)malloc(sizeof(t_tetro));
	if (!newnode)
		return (NULL);
	newnode->shape_id = 0;
	newnode->blocks = 0;
	while (newnode->blocks < 5)
		newnode->queue[newnode->blocks++] = 0;
	newnode->blocks = 0;
	newnode->letter = letter;
	newnode->next = NULL;
	return (newnode);
}

/*
function to add new t_tetro node to end of list
*/

t_tetro	*append_tetro(t_tetro *head)
{
	t_tetro	*temp;
	t_tetro	*new;
	short	letter;

	letter = 1;
	temp = head;
	while (temp->next)
	{
		temp = temp->next;
		letter++;
	}
	new = new_tetro('A' + letter);
	if (!new)
		return (NULL);
	temp->next = new;
	return (head);
}
