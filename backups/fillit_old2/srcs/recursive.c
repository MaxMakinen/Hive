/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 09:39:45 by mmakinen          #+#    #+#             */
/*   Updated: 2022/02/14 14:43:57 by mmakinen         ###   ########.fr       */
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
//	*read = next_free((*read)->next);
//	utils = reset(utils, 0);
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

size_t check_neighbours(t_utils u, size_t meep)
{
	int test;

	test = 0;
	if (u.grid[u.pos] == '.')
	{
		if (u.grid[u.pos + 1] != '.')
			test++;
		if (u.pos == 0 || u.grid[u.pos - 1] != '.')
			test++;
		if ((u.pos < (int)(u.maxlen - u.g_size)) || u.grid[u.pos + u.g_size] != '.')
			test++;
		if ((u.pos > (int)u.g_size) || u.grid[u.pos - u.g_size] != '.')
			test++;
		if (test == 4)
			meep++;
	}
	return (meep);
}

/*
Recursive solver for the fillit assignment. Finds smallest possible square that
fits given set of fixed tetrominos.
*/

int	recursive_tree(t_tetro *tetro, t_utils u, t_tetro *read)
{
	size_t meep = 0;
	read = next_free(tetro);
	if (!read)
		return (1);
	u = reset(u, 0);
	while (read && u.grid[u.pos] != '\0')
	{
		meep = check_neighbours(u, meep);
		while (read && (put_tetro(read, u)) && u.grid[u.pos] != '\0')
		{
//			if (read->letter == 'K')
//			{
//				ft_putendl("	K Placed");//DELETE
//				ft_putendl(u.grid);//DELETE
//			}

//			ft_putendl("	Placed");//DELETE
//			ft_putendl(u.grid);//DELETE
			if (recursive_tree(tetro, u, tetro) == 1)
				return (1);
			u = backtrack(&read, u);
			meep = check_neighbours(u, meep);
//			ft_putendl("	Backtrack");//DELETE
//			ft_putendl(u.grid);//DELETE
		}
		if (read != tetro && (meep > (u.empty)))
		{
//			ft_putnbr((int)u.pos);
//			ft_putendl("	Meeped");//DELETE
//			ft_putendl(u.grid);//DELETE
			read = next_free(read->next);
			u = reset(u, 0);
			meep = 0;
			continue ;
//			return (0);
		}
//		if (u.grid[u.pos] == '.' && ++u.counter > (u.empty + u.g_size) && read)
//		{
//			read = next_free(read->next);
//			u = reset(u, 0);
//			continue ;
//		}
//		if (!read && u.skips < u.empty)
//			return (mark_skip(u, tetro));
//		else if (u.skips > u.empty)
//			return (0);
		u.pos++;
	}
//	ft_putendl("	Fail");//DELETE
//	ft_putendl(u.grid);//DELETE
	return (0);
}
