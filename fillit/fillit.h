/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 13:06:58 by mmakinen          #+#    #+#             */
/*   Updated: 2022/01/21 15:43:15 by mmakinen         ###   ########.fr       */
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

/*function to read input and return linked list of found tetrominos*/
t_tetro	*input(int fd, t_tetro **head);
/*function to build grid for checking tetromino from lines from input file*/
int		grow_grid(char *grid, char *line);
/*functions to check that input follows the tasks conditions*/
int		check_chars(const char *line);
int		line_check(char *line, int row);
/*functions to make t_tetro node 
and to append a new node to the end of the linked list*/
t_tetro	*new_tetro(char letter);
t_tetro	*append_tetro(t_tetro *head);
/*functions to find tetromino in grid and add information to struct*/
t_tetro	*recursive_finder(char *grid, t_tetro *head, short index);
t_tetro	*find_tetro(char *grid, t_tetro *head);
void	append_queue(t_tetro *temp, short direction, short index);
int		clean_grid(char *grid, t_tetro *head);
/*functions to support main*/
int		error(int err);
int		open_fd(char *filename, int *fd);
int		close_fd(int fd);
int		print_usage(void);
/*functions to free malloce'd pointers*/
void	*free_list(t_tetro *head);
void	*free_all(t_tetro *head, char *line);

#endif
