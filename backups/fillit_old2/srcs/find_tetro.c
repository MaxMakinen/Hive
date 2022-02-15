/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_tetro.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:06:57 by mmakinen          #+#    #+#             */
/*   Updated: 2022/01/21 15:22:21 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
function to append target to queue.

Example tetro : ##
				 #
				 #						  |	|
										->  v	v
The shape_id for example tetro will be 0100 1000 1000 0000.
They only point forward to next square, never to already visited ones.
*/
void	append_queue(t_tetro *temp, short direction, short index)
{
	short	count;
	char	found;

	count = 1;
	found = 0;
	while (count < 5)
	{
		if (temp->queue[count++] == index)
			found = 1;
	}
	if (found == 0)
	{
		temp->queue[++temp->queue[0]] = index;
		temp->shape_id = temp->shape_id | direction;
	}
}

/*
function for identifying tetromino after finding first '#' in grid
*/

t_tetro	*recursive_finder(char *grid, t_tetro *temp, short index)
{
	if (temp->queue[0] == 0)
	{
		temp->queue[1] = index;
		temp->queue[0] += 1;
	}
	if (temp->shape_id > 0)
		temp->shape_id = temp->shape_id << 4;
	if (index > 5 && grid[index - 5] == '#')
		append_queue(temp, 8, index - 5);
	if (index - 1 > 0 && grid[index - 1] == '#')
		append_queue(temp, 4, index - 1);
	if ((index + 1) < 21 && grid[index + 1] == '#')
		append_queue(temp, 2, index + 1);
	if ((index + 5) < 21 && grid[index + 5] == '#')
		append_queue(temp, 1, index + 5);
	if (temp->shape_id == 0)
		return (NULL);
	temp->blocks++;
	if (temp->blocks < 4 && temp->queue[temp->blocks + 1])
		recursive_finder(grid, temp, temp->queue[temp->blocks + 1]);
	return (temp);
}

/*
Function to identify tetromino in grid and create a node in the linked list,
or return NULL in vase of error.
*/

t_tetro	*find_tetro(char *grid, t_tetro *head)
{
	short	index;
	t_tetro	*temp;

	temp = head;
	while (temp->next)
		temp = temp->next;
	index = 0;
	while (grid[index] && grid[index] != '#')
		index++;
	if (index > 16)
		return (NULL);
	recursive_finder(grid, temp, index);
	if (!temp || temp->blocks != 4)
		return (NULL);
	return (head);
}
