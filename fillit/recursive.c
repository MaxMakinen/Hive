/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 09:39:45 by mmakinen          #+#    #+#             */
/*   Updated: 2022/02/02 10:43:22 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int recursive_tree(t_tetro *tetro, t_utils utils, t_tetro *read)
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
}
