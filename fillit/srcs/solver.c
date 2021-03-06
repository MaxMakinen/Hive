/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <dmalesev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 09:03:06 by dmalesev          #+#    #+#             */
/*   Updated: 2022/02/21 16:19:14 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	newlines(t_tetro *tetro)
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
	prep_tetros(tetro);
	tetro_size = tetro->blocks * 4;
	while (utils.g_size * utils.g_size < tetro_size)
		utils.g_size++;
	utils = initialise(utils);
	while (recursive_tree(tetro, &utils, tetro) == 0)
	{
		unplace(tetro);
		utils.g_size++;
		free(utils.grid);
		utils = initialise(utils);
	}
	return (utils);
}
