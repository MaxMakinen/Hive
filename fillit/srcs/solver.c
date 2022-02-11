/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <dmalesev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 09:03:06 by dmalesev          #+#    #+#             */
/*   Updated: 2022/02/10 13:26:42 by mmakinen         ###   ########.fr       */
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

t_utils	solver(t_tetro *tetro)
{
	t_utils	utils;
	size_t	tetro_size;

	utils.g_size = 2;
	tetro->blocks = lst_size(tetro);
	tetro_size = tetro->blocks * 4;
	while (utils.g_size * utils.g_size < tetro_size)
		utils.g_size++;
	utils = initialise(utils, tetro_size);
	prep_tetros(tetro);
	while (recursive_tree(tetro, utils, tetro) == 0)
	{
		unplace(tetro);
		utils.g_size++;
		free(utils.grid);
		utils = initialise(utils, tetro_size);
	}
	utils = finalise(utils);
	return (utils);
}
