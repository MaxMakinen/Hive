/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 09:39:45 by mmakinen          #+#    #+#             */
/*   Updated: 2022/02/15 09:30:28 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
function to reset navigation values in utils
*/

t_utils	reset(t_utils utils, int check)
{
	utils.counter = 0;
	utils.pos = 0;
	if (check == 1)
	{
		while (utils.grid[utils.pos] != '.' && utils.grid[utils.pos] != '\0')
			utils.pos++;
	}
	return (utils);
}

/*
function to reset placement information in tetro and move utils.pos to correct
starting position for new attempt
*/

t_utils	backtrack(t_tetro **read, t_utils utils)
{
	(*read)->placed = 0;
	utils.pos = (*read)->nl[0];
	utils.counter = (*read)->queue[0];
	del_tetro(*read, utils);
	utils.pos += 1;
	return (utils);
}

/*
function to mark tetro as placed and remember position of first,
most top left, part of tetromino
*/

int	place(t_tetro *read, t_utils utils)
{
	read->placed = 1;
	read->nl[0] = utils.pos;
	read->queue[0] = utils.counter;
	return (1);
}

/*
function to mark a section of the grid as skipped, 
and restore it if backtracked to.
*/

int	mark_skip(t_utils utils, t_tetro *tetro)
{
	int	memory;

	while (utils.grid[utils.pos] != '.')
		utils.pos++;
	memory = utils.pos;
	utils.grid[memory] = 's';
	utils.skips++;
	if (recursive_tree(tetro, utils, tetro) == 1)
		return (1);
	utils.grid[memory] = '.';
	utils.skips--;
	return (0);
}

/*
Recursive solver for the fillit assignment. Finds smallest possible square that
fits given set of fixed tetrominos.
*/

int	recursive_tree(t_tetro *tetro, t_utils u, t_tetro *read)
{
	read = next_free(tetro);
	if (!read)
		return (1);
	u = reset(u, 0);
	while (u.grid[u.pos] != '\0')
	{
		while ((put_tetro(read, u)) && u.grid[u.pos] != '\0')
		{
			if (recursive_tree(tetro, u, tetro) == 1)
				return (1);
			u = backtrack(&read, u);
		}
		u.pos++;
	}
	return (0);
}
