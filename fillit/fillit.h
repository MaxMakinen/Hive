/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 13:06:58 by mmakinen          #+#    #+#             */
/*   Updated: 2022/01/19 19:40:36 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include "libft/libft.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>

typedef struct s_tetro
{
	unsigned short	shape_id;
	unsigned short	queue[5];
	int				blocks;
	char			letter;
	struct s_tetro	*next;
}					t_tetro;

t_tetro	*recursive_finder(char *grid, t_tetro *head, short index);
t_tetro	*find_tetro(char *grid, t_tetro *head);
t_tetro	*new_tetro(char letter);
t_tetro	*append_tetro(t_tetro *head);
t_tetro	*input(int fd);
void	append_queue(t_tetro *temp, short direction, short index);
int		open_fd(char *filename, int *fd);
int		close_fd(int fd);
int		print_usage(void);
int		error(int err);
int		clean_grid(char *grid, t_tetro *head);
int		open_fd(char *filename, int *fd);
int		close_fd(int fd);
int		print_usage(void);
int		line_check(char *line, int row);
int		grow_grid(char *grid, char *line);

#endif
