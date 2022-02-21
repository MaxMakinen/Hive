/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver_support.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 13:20:01 by mmakinen          #+#    #+#             */
/*   Updated: 2022/02/21 16:19:11 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_utils	initialise(t_utils utils)
{
	utils.pos = 0;
	utils.grid = make_grid(utils.g_size);
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
	t_tetro	*temp;

	temp = tetro;
	temp->blocks = 0;
	while (tetro)
	{
		newlines(tetro);
		temp->blocks++;
		tetro = tetro->next;
	}
}

int	count_hash(char *grid)
{
	int	count;

	count = 0;
	while (*grid)
	{
		if (*grid == '#')
			count++;
		grid++;
	}
	if (count != 4)
		return (0);
	return (1);
}
