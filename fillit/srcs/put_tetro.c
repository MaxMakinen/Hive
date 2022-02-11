/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_tetro.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <dmalesev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 10:37:12 by dmalesev          #+#    #+#             */
/*   Updated: 2022/02/11 09:28:33 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>

/*
function to reset navigation values in utils
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
function to reset placement information in tetro and move utils.pos to correct
starting position for new attempt
*/

int	put_tetro(t_tetro *t, t_utils u, size_t g)
{
	int	p;

	p = 1;
	while (u.grid && p > 0 && p < 5)
	{
		if (u.grid[u.pos + t->queue[p] + (g * (t->nl[p]))] == '.')
		{
			u.grid[u.pos + t->queue[p] + (g * (t->nl[p]))] = t->letter;
			p++;
		}
		else if (u.grid[u.pos + t->queue[p] + (g * (t->nl[p]))] != '.')
		{
			if (u.grid[u.pos + t->queue[p] + (g * (t->nl[p]))] == t->letter)
				u.grid[u.pos + t->queue[p] + (g * (t->nl[p]))] = '.';
			p--;
		}
	}
	if (p == 5)
	{
		place(t, u);
		return (1);
	}
	return (-1);
}

/*
function to mark tetro as placed and remember position of first,
most top left, part of tetromino
*/

int	lst_size(t_tetro *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
	lst = lst->next;
		size++;
	}
	return (size);
}

t_tetro	*next_free(t_tetro *head)
{
	t_tetro	*temp;

	temp = head;
	while (temp)
	{
		if (temp->placed == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

/*
function to mark a section of the grid as skipped,
and restore it if backtracked to.
*/

int	del_tetro(t_tetro *t, t_utils u)
{
	int	piece;
	int	g;
	int	pos;

	g = u.g_size + 1;
	piece = 4;
	t->placed = 0;
	pos = t->nl[0];
	while (u.grid && piece > 0)
	{
		if (u.grid[pos + t->queue[piece] + (g * (t->nl[piece]))] == t->letter)
			u.grid[pos + t->queue[piece] + (g * (t->nl[piece]))] = '.';
		piece--;
	}
	t->nl[0] = 0;
	return (1);
}
