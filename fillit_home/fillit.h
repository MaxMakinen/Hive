/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 13:06:58 by mmakinen          #+#    #+#             */
/*   Updated: 2022/01/18 12:36:33 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include "libft/libft.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

typedef struct	s_tetro
{
	unsigned short	shape_id;
	unsigned short	queue[5];
	int				blocks;
	char			letter;
	struct s_tetro	*next;
}					t_tetro;

t_tetro *recursive_finder(char *grid, t_tetro *head, short index, short *queue);
t_tetro *find_tetro(char *grid, t_tetro *head);
t_tetro *new_tetro(char letter);
t_tetro	*append_tetro(t_tetro *head);
t_tetro *input(int fd);
int		check_file(int fd);
void	append_queue(short *queue, t_tetro *temp, short direction, short index);

#endif
