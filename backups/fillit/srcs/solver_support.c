/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver_support.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 13:20:01 by mmakinen          #+#    #+#             */
/*   Updated: 2022/02/10 13:30:38 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_utils	initialise(t_utils utils, size_t tetro_size)
{
	utils.pos = 0;
	utils.skips = 0;
	utils.grid = make_grid(utils.g_size);
	utils.empty = (utils.g_size * utils.g_size) - tetro_size;
	utils.maxlen = (utils.g_size * utils.g_size) + utils.g_size;
	return (utils);
}

void	unplace(t_tetro *tetro)
{
	while (tetro)
	{
		tetro->placed = 0;
		tetro = tetro->next;
	}
}

void	prep_tetros(t_tetro *tetro)
{
	unplace(tetro);
	while (tetro)
	{
		nl_mem(tetro);
		tetro = tetro->next;
	}
}

t_utils	finalise(t_utils utils)
{
	int	count;

	count = 0;
	while (utils.grid[count] != '\0')
	{
		if (utils.grid[count] == 'e' || utils.grid[count] == 's')
			utils.grid[count] = '.';
		count++;
	}
	return (utils);
}
