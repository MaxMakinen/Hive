/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <dmalesev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 09:03:06 by dmalesev          #+#    #+#             */
/*   Updated: 2022/01/31 09:17:48 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	nl_mem(t_tetro *tetro)
{
	int		piece;
	int		pos;

	piece = 4;
	while (piece > 1)
	{
		pos = tetro->queue[1];
		while (tetro->queue[piece] > pos)
		{
			if ((pos + 1) % 5 == 0)
				(tetro->nl[piece])++;
			pos++;
		}
		tetro->queue[piece] -= tetro->queue[1];
		tetro->queue[piece] -= 5 * (tetro->nl[piece]);
		piece--;
	}
	tetro->queue[1] -= tetro->queue[1];
}

int	iterative_tree(t_tetro *tetro, t_utils utils, t_tetro *read)
{
	t_tetro	*solution[tetro->blocks];
	t_tetro	*temp;
	int		list;
//	size_t	maxlen;
//	maxlen = (utils.g_size * utils.g_size) + utils.g_size - 3;
	list = 0;
	temp = tetro;
	while (temp && list < tetro->blocks)
	{
		solution[list++] = temp;
		temp = temp->next;
	}
	list = 0;
	//printf("list_len = %d",tetro->blocks);
	while (list < tetro->blocks)
	{
		//printf("list = %d", list);
		while (utils.grid[utils.pos] != '\0')
		{
			if (read && put_tetro(read, utils, utils.g_size + 1) == 1)
			{
				read->placed = 1;
				read->nl[0] = utils.pos;
				solution[list] = read;
				read = next_free(tetro);
				if (!read)
					return (1);
				list++;
				utils.pos = 0;
				//printf("	Placed\nlist = %d\n%s\n", list, utils.grid);
				break ;
			}
			utils.pos++;
		}
		if (solution[0]->next == NULL)
			return (0);
		while (utils.grid[utils.pos] == '\0')
		{
			list--;
			read = solution[list];
			solution[list] = tetro;
			del_tetro(read, utils);
			read = next_free(read->next);
			//printf("Backtrack\nlist = %d\n%s\n",list , utils.grid);
			if (!read)
				continue ;
			utils.pos = 0;
		}
	}
	return (1);
}

int	recursive_tree(t_tetro *tetro, t_utils utils, t_tetro *read)
{
	//size_t	pos;
	read = next_free(tetro);
	if (!read)
		return (1);
	utils.pos = 0;
	while (utils.grid[utils.pos] != '\0')
	{
		while (put_tetro(read, utils, utils.g_size + 1) == 1)
		{
			read->placed = 1;
		//	tetro->nl[0] += 1;
			read->nl[0] = utils.pos;
		//	pos = utils.pos;
			if (recursive_tree(tetro, utils, read->next) == 1)
				return (1);
			else
			{
				read->placed = 0;
		//		tetro->nl[0] -= 1;
				//utils.pos = pos;
		//		pos *=1;
	//			printf("tetro->nl[0] = %d\n",tetro->nl[0]);
				utils.pos = read->nl[0];
	//			printf("Bactrack1\n%s\n", utils.grid);
				del_tetro(read, utils);
	//			printf("Bactrack\n%s\n", utils.grid);
				utils.pos = 0;
				read = next_free(read->next);
				if (!read)
					return (0);
			}
		}
		utils.pos++;
	}
	return (0);
}

t_utils	solver(t_tetro *tetro)
{
	t_tetro	*read;
	t_utils	utils;
	size_t	tetro_size;

	utils.pos = 0;
	read = tetro;
	utils.g_size = 2;
	tetro->blocks = lst_size(tetro);
	tetro_size = tetro->blocks * 4;
	while (utils.g_size * utils.g_size < tetro_size)
		utils.g_size++;
	utils.grid = make_grid(utils.g_size);
	utils.empty = (utils.g_size * utils.g_size) - tetro_size;
	while (read)
	{
		nl_mem(read);
		read = read->next;
	}
	while (read)
	{
		read->placed = 0;
		read = read->next;
	}
	while (recursive_tree(tetro, utils, tetro) == 0)
//	while (iterative_tree(tetro, utils, tetro) == 0)
	{
		read = tetro;
		while (read)
		{
			read->placed = 0;
			read = read->next;
		}
		utils.g_size++;
		//free(utils.grid);
		utils.grid = make_grid(utils.g_size);
		utils.empty = (utils.g_size * utils.g_size) - tetro_size;
	}
	return (utils);
}

t_utils	solver_iterative(t_tetro *tetro)
{
	t_tetro	*read;
	t_utils	utils;
	size_t	tetro_size;

	utils.pos = 0;
	read = tetro;
	utils.g_size = 2;
	tetro->blocks = lst_size(tetro);
	tetro_size = tetro->blocks * 4;
	while (utils.g_size * utils.g_size < tetro_size)
		utils.g_size++;
	utils.grid = make_grid(utils.g_size);
	utils.empty = (utils.g_size * utils.g_size) - tetro_size;
	while (read)
	{
		nl_mem(read);
		read = read->next;
	}
//	while (recursive_tree(tetro, utils, tetro) == 0)
	while (iterative_tree(tetro, utils, tetro) == 0)
	{
		read = tetro;
		while (read)
		{
			read->placed = 0;
			read = read->next;
		}
		utils.g_size++;
		free(utils.grid);
		utils.grid = make_grid(utils.g_size);
		utils.empty = (utils.g_size * utils.g_size) - tetro_size;
	}
	return (utils);
}
