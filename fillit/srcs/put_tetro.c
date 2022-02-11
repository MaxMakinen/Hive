/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_tetro.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <dmalesev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 10:37:12 by dmalesev          #+#    #+#             */
/*   Updated: 2022/02/10 12:11:05 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>

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
