/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <dmalesev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 17:18:30 by dmalesev          #+#    #+#             */
/*   Updated: 2022/05/03 12:07:02 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	line_length(char *line)
{
	int	spaces;

	spaces = 1;
	while (*line)
	{
		if (*line == ' ')
		{
			while (*line == ' ' && *line)
				line++;
			spaces++;
		}
		line++;
	}
	return (spaces);
}

void	line_to_map(t_utils *utils, char *line, int i)
{
	int	j;

	j = 1;
	while (line)
	{
		utils->map[i][j] = ft_atoi(line);
		if (utils->h_point < utils->map[i][j])
			utils->h_point = utils->map[i][j];
		if (utils->l_point > utils->map[i][j])
			utils->l_point = utils->map[i][j];
		utils->map_h = utils->h_point - utils->l_point;
		line = ft_strchr(line, ' ');
		while (line && *line == ' ')
			line++;
		j++;
	}
}

void	free_and_exit(t_utils *utils, char **line, int i)
{
	i--;
	while (i >= 0)
		free(utils->map[i--]);
	if (*line)
		free(*line);
	free(utils->map);
	close_fdf(utils, "Failed to malloc for map...", -1);
}

void	get_map(int fd, t_utils *utils)
{
	char	*line;
	int		i;

	line = NULL;
	i = 0;
	utils->map = (int **)malloc(sizeof(int *) * utils->lines);
	if (!utils->map)
		close_fdf(utils, "Failed to malloc for map...", -1);
	while (utils->lines > i)
	{
		if (get_next_line(fd, &line) == -1)
			free_and_exit(utils, &line, i);
		utils->map[i] = (int *)malloc(sizeof(int) * (line_length(line) + 1));
		if (utils->map[i] == NULL)
			free_and_exit(utils, &line, i);
		utils->map[i][0] = line_length(line);
		if (utils->longest_line < utils->map[i][0])
			utils->longest_line = utils->map[i][0];
		line_to_map(utils, line, i);
		free(line);
		i++;
	}
}

int	count_lines(int fd)
{
	int		lines;
	char	buffer;

	lines = 0;
	while (read(fd, &buffer, 1))
	{
		if (buffer == '\n')
			lines++;
	}
	return (lines);
}
