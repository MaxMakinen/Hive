/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 14:58:57 by mmakinen          #+#    #+#             */
/*   Updated: 2022/08/26 17:10:31 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	identify_obj(t_obj *temp, char **words)
{
	if (ft_strcmp(words[0], "camera") == 0)
	{
		temp->type = e_camera;
		temp->vfov = VFOV;
	}
	else if (ft_strcmp(words[0], "light") == 0)
		temp->type = e_light;
	else if (ft_strcmp(words[0], "sphere") == 0)
		temp->type = e_sphere;
	else if (ft_strcmp(words[0], "plane") == 0)
		temp->type = e_plane;
	else if (ft_strcmp(words[0], "cylinder") == 0)
		temp->type = e_cylinder;
	else if (ft_strcmp(words[0], "cone") == 0)
		temp->type = e_cone;
	else
		return (FALSE);
	return (TRUE);
}

void	populate_obj(t_obj *temp, char **words)
{
	if (ft_strcmp(words[1], "pos") == 0)
		temp->pos = get_vector(temp->pos, &words[2]);
	else if (ft_strcmp(words[1], "translate") == 0)
		temp->pos = vec_plus(temp->pos, get_vector(temp->pos, &words[2]));
	else if (ft_strcmp(words[1], "up") == 0)
		temp->up = get_vector(temp->up, &words[2]);
	else if (ft_strcmp(words[1], "dir") == 0)
	{
		temp->dir = get_vector(temp->dir, &words[2]);
		if (temp->type != e_camera)
			temp->dir = normalize(temp->dir);
	}
	else if (ft_strcmp(words[1], "vfov") == 0)
		temp->vfov = ft_atoi(words[2]);
	else if (ft_strcmp(words[1], "radius") == 0)
	{
		temp->radius = ft_atod(words[2]);
		temp->radius2 = temp->radius * temp->radius;
	}
	else if (ft_strcmp(words[1], "height") == 0)
		temp->height = ft_atod(words[2]);
	get_description(temp, words);
}

int	parse_line(char *line, t_obj *temp)
{
	char	**words;

	words = ft_strsplit(line, ' ');
	if (words && words[0][0] != '-')
	{
		if (identify_obj(temp, words))
		{
			ft_arrfree(words);
			return (FALSE);
		}
	}
	if (*words && temp)
	{
		if (words[0][0] != '-')
		{
			ft_arrfree(words);
			return (FALSE);
		}
		populate_obj(temp, words);
	}
	ft_arrfree(words);
	return (TRUE);
}

void	parse(t_data *data, const int fd)
{
	char	*line;
	char	**words;
	t_obj	*obj;
	t_obj	*temp;
	int		empty;

	empty = 0;
	data->scene->obj = init_obj(data);
	while (get_next_line(fd, &line))
	{
		temp = get_last(data->scene->obj);
		if (line && line[0] == '#')
			;
		else if (*line == 0 && empty == 0)
		{
			temp->next = init_obj(data);
			empty = 1;
		}
		else if (line && *line)
		{
			parse_line(line, temp);
			empty = 0;
		}
		free(line);
	}
}

int	read_input(t_data *data, const char *file_name)
{
	int	fd;

	open_file(&fd, file_name);
	parse(data, fd);
	close_file(fd);
	return (TRUE);
}
