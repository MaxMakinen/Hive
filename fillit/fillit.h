/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 13:06:58 by mmakinen          #+#    #+#             */
/*   Updated: 2022/01/26 19:08:16 by mmakinen         ###   ########.fr       */
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
	int				queue[5];
	int				nl[5];
	int				blocks;
	int				placed;
	char			letter;
	struct s_tetro	*next;
}					t_tetro;

typedef struct s_utils
{
	char	*grid;
	size_t	g_size;
	size_t	empty;
	int		pos;
}			t_utils;

/*function to read input and return linked list of found tetrominos*/
t_tetro	*input(int fd, t_tetro **head);
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
void	file_check(char *filename);
int		print_usage(void);
int		line_check(char *line, int row);
int		grow_grid(char *grid, char *line);
t_utils	solver(t_tetro *tetro);
t_utils	solver_iterative(t_tetro *tetro);
/*functions to free malloce'd pointers*/
void	*free_list(t_tetro *head);
void	*free_all(t_tetro *head, char *line);

#endif
