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

#define SCENE 1
#define CAMERA 2
#define LIGHT 3
#define OBJECT 4
#define SPHERE 5
#define PLANE 6
#define CYLINDER 7
#define CONE 8

int	identify_obj(t_obj *temp, char **words)
{
	if (ft_strncmp(words[0], "camera", 6) == 0)
	{
		temp->type = e_camera;
		temp->vfov = VFOV;
	}
	else if (ft_strncmp(words[0], "light", 4) == 0)
		temp->type = e_light;
	else if (ft_strncmp(words[0], "sphere", 6) == 0)
		temp->type = e_sphere;
	else if (ft_strncmp(words[0], "plane", 5) == 0)
		temp->type = e_plane;
	else if (ft_strncmp(words[0], "cylinder", 8) == 0)
		temp->type = e_cylinder;
	else if (ft_strncmp(words[0], "cone", 4) == 0)
		temp->type = e_cone;
	else
		return (FALSE);
	return (TRUE);
}

void	populate_obj(t_obj *temp, char **words)
{
	if (ft_strncmp(words[1], "pos", 3) == 0)
		get_vector(&temp->pos, &words[2]);
	else if (ft_strncmp(words[1], "up", 3) == 0)
		get_vector(&temp->up, &words[2]);
	else if (ft_strncmp(words[1], "dir", 3) == 0)
	{
		get_vector(&temp->dir, &words[2]);
		temp->dir = normalize(temp->dir);
	}
	else if (ft_strncmp(words[1], "color", 5) == 0)
		temp->color.color = ft_atoi(words[2]);
	else if (ft_strncmp(words[1], "vfov", 5) == 0)
		temp->vfov = ft_atoi(words[2]);
	else if (ft_strncmp(words[1], "radius", 6) == 0)
	{
		temp->radius = ft_atod(words[2]);
		temp->radius2 = temp->radius * temp->radius;
	}
	else if (ft_strncmp(words[1], "height", 6) == 0)
		temp->height = ft_atod(words[2]);
	else if (ft_strncmp(words[1], "brightness", 6) == 0)
		temp->brightness = ft_atod(words[2]);
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

void	parse(t_scene *scene, const int fd)
{
	char	*line;
	char	**words;
	t_obj	*obj;
	t_obj	*temp;
	int		empty;

	empty = 0;
	scene->obj = init_obj();
	while (get_next_line(fd, &line))
	{
		temp = get_last(scene->obj);
		if (line && line[0] == '#')
			;
		else if (*line == 0 && empty == 0)
		{
			temp->next = init_obj();
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

int	read_input(t_scene *scene, const char *file_name)
{
	int	fd;

	open_file(&fd, file_name);
	parse(scene, fd);
	close_file(fd);
	return (TRUE);
}
