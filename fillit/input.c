/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 10:49:00 by mmakinen          #+#    #+#             */
/*   Updated: 2022/01/19 10:24:42 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
function to append target to queue.

Example tetro : ##
				 #
				 #						    |	 |
								        ->	v	 v
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
How thew temp->queue works
how many targets have been found
 |
 v
[4][12][13][18][19]
    ^   ^   ^   ^
	index positions of targets 1, 2,3 and 4
##
 ##
*/

/*
function for identifying tetromino and traversing grid after finding first '#' in grid
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
		append_queue(temp, 1, index - 5);
	if (index - 1 > 0 && grid[index - 1] == '#')
		append_queue(temp, 2, index - 1);
	if ((index + 1) < 21 && grid[index + 1] == '#')
		append_queue(temp, 4, index + 1);
	if ((index + 5) < 21 && grid[index + 5] == '#')
		append_queue(temp, 8, index + 5);
	if (temp->shape_id == 0)
		return (NULL);
	temp->blocks++; 
	if (temp->blocks < 4 && temp->queue[temp->blocks + 1])
		recursive_finder(grid, temp, temp->queue[temp->blocks + 1]);
	return (temp);
}

/*
Function to identify tetromino in grid and create a node in the linked list, or return NULL in vase of error.
*/

t_tetro	*find_tetro(char *grid, t_tetro *head)
{
	short index;
	t_tetro *temp;

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
	{
		ft_putendl("blocks error");
		return(NULL);
	}
	return (head);
}

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
	t_tetro *new;
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

/*
function checks to see if there are any other characters in line other than '.', '#' or '\n'
*/

int	check_line(char *line)
{
	char	*temp;

	temp = line;
	while (*temp)
	{
		if (*temp != '.' && *temp != '#' && *temp != '\n')
			return (0);
		temp++;
	}
	return (1);
}

/*
Function that takes the filename as input and opens and reads through the file, identifying tetrominos and placing them into a linked list.
Returns pointer to head of linked list.
In case of error, return NULL pointer.
*/

t_tetro *input(int fd)
{
	int			row;
	char		*line;
	char		grid[21];
	t_tetro		*head;
	int			hash = 0;

	head = new_tetro('A'); 
	if (!head)
		return (NULL);
	ft_bzero(grid, 21);
	row = 1;
	while (get_next_line(fd, &line))
	{
		if (row > 129)
			return (NULL);
		if(ft_strlen(line) != 4 && (row % 5))
			return (NULL);
		if((row % 5) == 0 && *line)
			return (NULL);
		if (row % 5) 
		{
			if (!check_line(line))
				return (NULL);
			hash += ft_strccount(line, '#');
			if (hash > 4)
				return (NULL);
			ft_strlcat(grid, line, 21);
			ft_strlcat(grid, "\n", 21);
		}
		else if ((row % 5) == 0) 
		{
			if (!find_tetro(grid, head)) 
				return (NULL);
			if (!append_tetro(head))
				return (NULL);
			ft_bzero(grid, 21); 
			hash = 0;
		}
		row++;
	}
	if (!find_tetro(grid, head)) 
		return (NULL);
	return (head);
}

