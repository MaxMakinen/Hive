/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_tetro.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 18:52:28 by mmakinen          #+#    #+#             */
/*   Updated: 2022/01/31 15:15:44 by mmakinen         ###   ########.fr       */
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
	while (newnode->blocks < 5)
		newnode->nl[newnode->blocks++] = 0;
	newnode->blocks = 0;
	newnode->placed = 0;
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
	short	letter;

	letter = 1;
	temp = head;
	while (temp->next)
	{
		temp = temp->next;
		letter++;
	}
	temp->next = new_tetro('A' + letter);
	if (!temp->next)
		return (NULL);
	return (head);
}

/*
function to free *line and point it towrds NULL
*/

void	free_line(char **line)
{
	if (*line)
		free(*line);
	*line = NULL;
}

/*
function to free *line and call function to free linked list.
*/

void	*free_all(t_tetro *head, char **line)
{	
	free_line(line);
	return (free_list(head));
}

/*
function to free struct linked list.
*/

void	*free_list(t_tetro *head)
{	
	t_tetro	*temp;

	temp = head->next;
	while (temp)
	{	
		head->next = NULL;
		free(head);
		head = temp;
		temp = head->next;
	}
	free(head);
	head = NULL;
	return (NULL);
}
