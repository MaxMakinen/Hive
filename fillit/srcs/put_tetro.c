/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_tetro.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <dmalesev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 10:37:12 by dmalesev          #+#    #+#             */
/*   Updated: 2022/02/21 16:31:07 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
function to make grid in required size to place tetros
*/

char	*make_grid(size_t size)
{
	char	*grid;
	char	*write;

	grid = ft_strnew((size * size) + size);
	write = grid;
	while ((size_t)(write - grid) < (size * size) + size)
	{
		ft_memset(write, '.', size);
		write = write + size;
		ft_memset(write, '\n', 1);
		write++;
	}
	return (grid);
}

/*
function to attempt to place tetro in grid, and delete any changes if it
encounters an issue
*/

int	put_tetro(t_tetro *t, t_utils *u)
{
	int		piece;
	size_t	check;

	piece = 1;
	while (piece > 0 && piece < 5)
	{
		check = u->pos + t->queue[piece] + ((u->g_size + 1) * (t->nl[piece]));
		if (check < u->maxlen && u->grid[check] == '.')
		{
			u->grid[check] = t->letter;
			piece++;
		}
		else if (check >= u->maxlen)
			piece--;
		else if (u->grid[check] != '.')
		{
			if (u->grid[check] == t->letter)
				u->grid[check] = '.';
			piece--;
		}
	}
	if (piece == 5)
		return (place(t, u));
	return (0);
}

/*
function to find next unplaced tetro in list
*/

t_tetro	*next_free(t_tetro *temp)
{
	while (temp)
	{
		if (temp->placed == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

/*
function to remove a placed tetro from grid and reset nevigation values of
tetro
*/

int	del_tetro(t_tetro *t, t_utils *u)
{
	int	piece;
	int	g;
	int	pos;

	g = u->g_size + 1;
	piece = 4;
	t->placed = 0;
	pos = t->nl[0];
	while (u->grid && piece > 0)
	{
		if (u->grid[pos + t->queue[piece] + (g * (t->nl[piece]))] == t->letter)
			u->grid[pos + t->queue[piece] + (g * (t->nl[piece]))] = '.';
		piece--;
	}
	t->nl[0] = 0;
	return (1);
}
