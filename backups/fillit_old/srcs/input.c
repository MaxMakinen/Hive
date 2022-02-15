/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 10:49:00 by mmakinen          #+#    #+#             */
/*   Updated: 2022/01/31 15:40:11 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
function checks to see if there are any other characters in *line
other than '.', '#' or '\n'
*/

int	check_chars(const char *line)
{
	const char	*temp;

	temp = line;
	while (*temp)
	{
		if (*temp != '.' && *temp != '#' && *temp != '\n')
			return (0);
		temp++;
	}
	return (1);
}

/*
function to call find_tetro, append_tetro and clean the grid
*/

int	clean_grid(char *grid, t_tetro *head)
{
	if (!find_tetro(grid, head))
		return (0);
	if (!append_tetro(head))
		return (0);
	ft_bzero(grid, 21);
	return (1);
}

/*
Function to check file for errors as we read it.
*/

int	line_check(char *line, int row)
{
	if (row > 129)
		return (0);
	if (ft_strlen(line) != 4 && (row % 5))
		return (0);
	if ((row % 5) == 0 && *line)
		return (0);
	return (1);
}

/*
function to add content of line and a newline to grid
*/

int	grow_grid(char *grid, char *line)
{
	if (!check_chars(line))
		return (0);
	ft_strlcat(grid, line, 21);
	ft_strlcat(grid, "\n", 21);
	return (1);
}

/*
Function that takes pointer to pointer to head and filename as input.
Then opens and reads through the file,
identifying tetrominos and placing them into a linked list.
Returns pointer to head of linked list.
In case of error, return NULL pointer.
*/

t_tetro	*input(int fd, t_tetro **head)
{
	int			row;
	char		*line;
	char		grid[21];

	if (!*head)
		return (NULL);
	ft_bzero(grid, 21);
	row = 1;
	line = NULL;
	while (get_next_line(fd, &line))
	{
		if (!line_check(line, row))
			return (free_all(*head, &line));
		if (row % 5 && !grow_grid(grid, line))
			return (free_all(*head, &line));
		if (row % 5 == 0 && !clean_grid(grid, *head))
			return (free_all(*head, &line));
		free_line(&line);
		row++;
	}
	if (row % 5)
		return (NULL);
	if (!find_tetro(grid, *head))
		return (free_all(*head, &line));
	return (*head);
}
