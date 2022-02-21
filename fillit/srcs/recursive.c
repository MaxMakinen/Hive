/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 09:39:45 by mmakinen          #+#    #+#             */
/*   Updated: 2022/02/21 15:45:24 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
function to reset placement information in tetro and move utils.pos to correct
starting position for new attempt
*/

void	backtrack(t_tetro *read, t_utils *utils)
{
	read->placed = 0;
	utils->pos = read->nl[0];
	del_tetro(read, utils);
	utils->pos++;
}

/*
function to mark tetro as placed and remember position of first,
most top left, part of tetromino
*/

int	place(t_tetro *read, t_utils *utils)
{
	read->placed = 1;
	read->nl[0] = utils->pos;
	return (1);
}

/*
Recursive solver for the fillit assignment. Finds smallest possible square that
fits given set of fixed tetrominos.
*/

int	recursive_tree(t_tetro *tetro, t_utils *u, t_tetro *read)
{
	read = next_free(tetro);
	if (!read)
		return (1);
	u->pos = 0;
	while (u->grid[u->pos] != '\0')
	{
		while ((put_tetro(read, u)) && u->grid[u->pos] != '\0')
		{
			if (recursive_tree(tetro, u, tetro) == 1)
				return (1);
			backtrack(read, u);
		}
		u->pos++;
	}
	return (0);
}
