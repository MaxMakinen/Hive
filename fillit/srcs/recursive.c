/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 09:39:45 by mmakinen          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/02/09 18:23:10 by dmalesev         ###   ########.fr       */
=======
/*   Updated: 2022/02/10 13:38:15 by mmakinen         ###   ########.fr       */
>>>>>>> mmakinen
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>
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

<<<<<<< HEAD
void	del_empty(t_utils utils)
{
	while (utils.grid[utils.pos] != '\0')
	{
		if (utils.grid[utils.pos] == '+')
			utils.grid[utils.pos] = '.';
		utils.pos++;
	}
}

t_utils	backtrack(t_tetro *read, t_utils utils)
{
	read->placed = 0;
	utils.pos = read->nl[0];
	del_tetro(read, utils);
	del_empty(utils);
	utils.pos = 0;
	if (utils.counter)
		utils.counter--;
=======
t_utils	backtrack(t_tetro **read, t_utils utils)
{
	(*read)->placed = 0;
	utils.pos = (*read)->nl[0];
	del_tetro(*read, utils);
	*read = next_free((*read)->next);
>>>>>>> mmakinen
	return (utils);
}

/*
function to mark tetro as placed and remember position of first,
most top left, part of tetromino
*/

void	place(t_tetro *read, t_utils utils)
{
	read->placed = 1;
	read->nl[0] = utils.pos;
}

/*
function to mark a section of the grid as skipped, 
and restore it if backtracked to.
*/
int	mark_skip(t_utils utils, t_tetro *tetro)
{
	int	memory;

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
Recursive solver for the fillit assignment. Finds dmallest possible square that
fits given set of fixed tetrominos.
*/

<<<<<<< HEAD
t_utils	put_empty(t_utils utils)
{
	while (utils.grid[utils.pos] != '\0')
	{
		if (utils.grid[utils.pos] == '.')
		{
			utils.grid[utils.pos] = '+';
			return (utils);
		}
		utils.pos++;
	}
	return (utils);
}

int	recursive_tree(t_tetro *tetro, t_utils utils, t_tetro *read)
=======
int	recursive_tree(t_tetro *tetro, t_utils u, t_tetro *read)
>>>>>>> mmakinen
{
	read = next_free(tetro);
	if (!read)
		return (1);
	u = reset(u, 1);
	while (read && u.grid[u.pos] != '\0')
	{
		while (read && put_tetro(read, u, u.g_size + 1) == 1)
		{
<<<<<<< HEAD
			printf("POS: [%d]\n", utils.pos);
			printf("COUNTER: %ld\n", utils.counter);
			printf("GRID:\n%s\n\n", utils.grid);
			place(read, utils);
			if (recursive_tree(tetro, utils, tetro) == 1)
				return (1);
			utils = backtrack(read, utils);
			read = next_free(read->next);
			printf("POS: [%d]\n", utils.pos);
			printf("COUNTER: %ld\n", utils.counter);
			printf("BACKTRACK:\n%s\n\n", utils.grid);
			if (!read && utils.counter < utils.empty)
			{
				utils = reset(utils);
				utils = put_empty(utils);
				utils.counter++;
				printf("POS: [%d]\n", utils.pos);
				printf("COUNTER: %ld\n", utils.counter);
				printf("*** READ IS NULL ***\n");
				printf("*** PLACE EMPTY ***:\n%s\n\n", utils.grid);
				if (recursive_tree(tetro, utils, read) == 1)
					return (1);
			}
		}
		if (utils.grid[utils.pos] == '.' || utils.grid[utils.pos] == '+')
		{
			utils.counter++;
		}
		utils.pos++;
		if (read && utils.counter > utils.empty)
=======
			if (recursive_tree(tetro, u, read->next) == 1)
				return (1);
			u = backtrack(&read, u);
			if (!read && (u.skips + u.counter) < u.empty)
				return (mark_skip(u, tetro));
			u = reset(u, 0);
		}
		if (u.grid[u.pos] == '.' && read && (u.skips + ++u.counter) > u.empty)
>>>>>>> mmakinen
		{
			read = next_free(read->next);
			continue ;
		}
		u.pos++;
	}
	return (0);
}
