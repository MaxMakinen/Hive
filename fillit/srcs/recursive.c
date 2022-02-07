/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 09:39:45 by mmakinen          #+#    #+#             */
/*   Updated: 2022/02/07 16:56:26 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
function to reset navigation values in utils
*/

t_utils	reset(t_utils utils)
{
	utils.counter = 0;
	utils.pos = 0;
	return (utils);
}

/*
function to reset placement information in tetro and move utils.pos to correct
starting position for new attempt
*/

t_utils	backtrack(t_tetro *read, t_utils utils)
{
	read->placed = 0;
	utils.pos = read->nl[0];
	del_tetro(read, utils);
	utils.pos = 0;
	return (utils);
}

/*
function to mark tetro as placed and remember position of first, top left, piece
*/

void	place(t_tetro *read, t_utils utils)
{
	read->placed = 1;
	read->nl[0] = utils.pos;
}

/*
Recursive solver for the fillit assignment. Finds dmallest possible square that
fits given set of fixed tetrominos.
*/

int	recursive_tree(t_tetro *tetro, t_utils utils, t_tetro *read)
{
	read = next_free(tetro);
	if (!read)
		return (1);
	utils = reset(utils);
	while (utils.grid[utils.pos] != '\0')
	{
		while (read && put_tetro(read, utils, utils.g_size + 1) == 1)
		{
			place(read, utils);
			if (recursive_tree(tetro, utils, read->next) == 1)
				return (1);
			utils = backtrack(read, utils);
			read = next_free(read->next);
		}
		if (utils.grid[utils.pos++] == '.')
			utils.counter++;
		if (read && utils.counter > utils.empty)
		{
			utils = reset(utils);
			read = next_free(read->next);
		}
		if (!read)
			return (0);
	}
	return (0);
}
