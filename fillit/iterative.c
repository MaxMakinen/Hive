/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterative.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 15:51:12 by mmakinen          #+#    #+#             */
/*   Updated: 2022/02/01 16:19:44 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
function to count amount of tetros in list
*/
/*
int	list_count(t_tetro *tetro)
{
	t_tetro *temp;
	int		list;

	temp = tetro;
	list = 0;
	while (temp && list < tetro->blocks)
	{
		list++;
		temp = temp->next;
	}
	return (list);
}*/
/*
function to solve the puzzle iteratively
*/

int iterative_tree(t_tetro *tetro, t_utils utils, t_tetro *read)
{
	t_tetro *solution[tetro->blocks];
	t_tetro *temp;
	int	 list;
	size_t  counter;
//  size_t  maxlen;

//  maxlen = (utils.g_size * utils.g_size) + utils.g_size - 3;
	//list = list_count;
	temp = tetro;
/*	while (temp && list < tetro->blocks)
	{
		list++;
		//solution[list++] = temp;
		temp = temp->next;
	}
*/	list = 0;
	while (list < tetro->blocks)
	{
		counter = 0;
		utils.pos = 0;
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
				break;
			}
			if (utils.grid[utils.pos] == '.')
				counter++;
			utils.pos++;
			if (counter > utils.empty)
			{
				read = next_free(read->next);
				if (!read)
				{
					list--;
					if (list < 0)
						return(0);
					read = solution[list];
					solution[list] = tetro;
					del_tetro(read, utils);
					read = next_free(read->next);
					break;
				}
				counter = 0;
				utils.pos = 0;
			}
		}
		if (solution[0]->next == NULL)
			return (0);
		while (utils.grid[utils.pos] == '\0' || !read)
		{
			list--;
			read = solution[list];
			solution[list] = tetro;
			del_tetro(read, utils);
			read = next_free(read->next);
			if (!read)
				continue;
			utils.pos = 0;
		}
	}
	return (1);
}
