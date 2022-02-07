/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_tetro.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <dmalesev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 10:37:12 by dmalesev          #+#    #+#             */
/*   Updated: 2022/02/01 12:40:19 by dmalesev         ###   ########.fr       */
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

void	nl_mem_2(t_tetro *tetro)
{
	int		piece;
	int		pos;

	pos = 4;
	while (pos > 1)
	{
		piece = tetro->queue[pos] - tetro->queue[1];
		if (tetro->queue[pos] - 1 == tetro->queue[pos - 1])
			piece--;
		if (tetro->queue[pos] + 1 == tetro->queue[pos - 1])
			piece++;
		while (piece > 2)
		{
			tetro->nl[pos] += 1;
			piece -= 5;
		}
		tetro->queue[pos] -= tetro->queue[1];
		tetro->queue[pos] -= 5 * (tetro->nl[pos]);
		pos--;
	}
	tetro->queue[1] -= tetro->queue[1];
}

int	put_tetro(t_tetro *tetro, t_utils utils, size_t g_size)
{
	int	piece;

	piece = 1;
	while (utils.grid && piece > 0 && piece < 5)
	{
		if (utils.grid[utils.pos + tetro->queue[piece] + (g_size * (tetro->nl[piece]))] == '.')
		{
			utils.grid[utils.pos + tetro->queue[piece] + (g_size * (tetro->nl[piece]))] = tetro->letter;
			piece++;
		}
		else if (utils.grid[utils.pos + tetro->queue[piece] + (g_size * (tetro->nl[piece]))] != '.')
		{
			if (utils.grid[utils.pos + tetro->queue[piece] + (g_size * (tetro->nl[piece]))] == tetro->letter)
				utils.grid[utils.pos + tetro->queue[piece] + (g_size * (tetro->nl[piece]))] = '.';
			piece--;
		}
	}
	if (piece == 5)
		return (1);
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
/*
int	recursive_tree(t_tetro *tetro, t_utils utils, t_tetro *read)
{
	//TRIES TO SET PIECES IN GRID UNTIL NO POS LEFT
	while (utils.grid[utils.pos])
	{
		while (read && read->placed == 1)
			read = read->next;
		if (read == NULL)
			return (1);
		printf("POS:[%ld]\n", utils.pos);
		if (put_tetro(read, utils, utils.g_size + 1) == 1)
		{
			printf("PLACED \'%c\' PIECE!\n", read->letter);
			printf("GRID:\n%s\n", utils.grid);
			read->placed = 1;
			if (recursive_tree(tetro, utils, tetro) == 1)
				return (1);
			else
				read->placed = 0;
		}
		else
		{
			utils.pos++;
			printf("FAILED TO PLACE \'%c\' PIECE!\n", read->letter);
		}
	}
	if (utils.grid[utils.pos] && utils.empty > 0)
	{
		printf("PLACED EMPTY POS:[%ld]\n", utils.pos);
		utils.empty--;
		printf("EMPTY SQUARES LEFT:[%ld]\n", utils.empty);
		utils.pos++;
		if (recursive_tree(tetro, utils, tetro) == 1)
			return (1);
		else
		{
			utils.empty++;
			utils.pos--;
		}
	}
	return (0);
}*/

/*
function that finds next unplaced tetro in list.
*/

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
function to delete tetro.
*/

int	del_tetro(t_tetro *tetro, t_utils utils)
{
	int	piece;
	int	g_size;
	int	pos;

	g_size = utils.g_size + 1;
	piece = 4;
	tetro->placed = 0;
	pos = tetro->nl[0];
	while (utils.grid && piece > 0)
	{
		if (utils.grid[pos + tetro->queue[piece] + (g_size * (tetro->nl[piece]))] == tetro->letter)
			utils.grid[pos + tetro->queue[piece] + (g_size * (tetro->nl[piece]))] = '.';
		piece--;
	}
	tetro->nl[0] = 0;
	return (1);
}

int	rec_del_tetro(t_tetro *tetro, t_utils utils)
{
	int	piece;
	int	g_size;

	g_size = utils.g_size + 1;
	piece = 4;
	tetro->placed = 0;
	while (utils.grid && piece > 0)
	{
		if (utils.grid[utils.pos + tetro->queue[piece] + (g_size * (tetro->nl[piece]))] == tetro->letter)
			utils.grid[utils.pos + tetro->queue[piece] + (g_size * (tetro->nl[piece]))] = '.';
		piece--;
	}
	tetro->nl[0] = 0;
	return (1);
}

/*
Crazy ideas that will propably not work.
 */

int	iterative_tree(t_tetro *tetro, t_utils utils, t_tetro *read)
{
	t_tetro *solution[tetro->blocks];
	t_tetro *temp;
	int		list;
	size_t	counter;
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
	//printf("list_len = %d\n",tetro->blocks);
	//printf("empty = %ld\n", utils.empty);
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
				//printf("	Placed\nlist = %d\n%s\n", list, utils.grid);
				break;
			}
			if (utils.grid[utils.pos] == '.')
				counter++;
			utils.pos++;
			if (counter > utils.empty)
			{
				//printf("Backtrack empty\ntetro shape =%d\nlist = %d\n%s\n", read->shape_id, list , utils.grid);
				read = next_free(read->next);
				if (!read)
				{
					//printf("	Blem\n");
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
			//printf("Backtrack\nlist = %d\n%s\n",list , utils.grid);
			if (!read)
				continue;
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
		nl_mem_2(read);
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
		nl_mem_2(read);
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
/*
int	main(void)
{
	t_tetro		*tetro;
	t_tetro		*tetro2;

	tetro = (t_tetro *)malloc(sizeof(*tetro));
	tetro->letter = 'A';
	tetro->queue[1] = 10;
	tetro->queue[2] = 11;
	tetro->queue[3] = 15;
	tetro->queue[4] = 20;

	tetro2 = (t_tetro *)malloc(sizeof(*tetro2));
	tetro2->letter = 'B';
	tetro2->queue[1] = 10;
	tetro2->queue[2] = 11;
	tetro2->queue[3] = 15;
	tetro2->queue[4] = 20;
	tetro->next = tetro2;
	printf("FINAL GRID:\n%s\n", solver(tetro));
	return (0);
}*/
