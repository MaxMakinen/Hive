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

int	open_file(int *fd, const char *filename)
{
	*fd = open(filename, O_RDONLY);
	if (*fd == -1)
	{
		ft_putendl("ERROR: failed to open file.");
		exit(0);
	}
	return (TRUE);
}

int	close_file(int fd)
{
	if (close(fd) == -1)
	{
		ft_putendl("ERROR: failed to close file");
		exit(0);
	}
	return (TRUE);
}

float	ft_atof(char *str)
{
	float	num;
	char	**temp;

	temp = ft_strsplit(str, '.');
	num = (float)ft_atoi(temp[1]) / powf(10.0f, (float)ft_strlen(temp[1]));
	num += (float)ft_atoi(temp[0]);
	return (num);
}

int	get_vector(t_vec3f *vector, char **words)
{
	words++;
	vector->x = ft_atof(words[0]);
	vector->y = ft_atof(words[1]);
	vector->z = ft_atof(words[2]);
	return (TRUE);
}

int get_float(float *num, char **words)
{
	*num = (float)atof(words[1]);
	return (TRUE);
}

int get_name(char *name, char **words)
{
	name = ft_memcpy(name, *words, ft_strlen(*words));
	return (TRUE);
}

int	get_color(t_rgb *color, char **words)
{
	color->color = ft_atoi(*words);
	return (TRUE);
}

int	get_type(t_obj *obj, char **words)
{	
	if (ft_strncmp(*words, "sphere", 6))
		obj->type = sphere;
	else if (ft_strncmp(*words, "plane", 5))
		obj->type = plane;
	else if (ft_strncmp(*words, "cylinder", 8))
		obj->type = cylinder;
	else if (ft_strncmp(*words, "cone", 54))
		obj->type = cone;
	return (TRUE);
}

t_obj	*get_current_obj(t_scene *scene)
{
	t_obj	*temp;

	temp = scene->obj;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

t_obj	*init_object(t_scene *scene)
{
	t_obj	*temp;

	if (scene->obj == NULL)
		temp = scene->obj;
	else
		temp = get_current_obj(scene);
	temp = ft_calloc(sizeof(t_obj), 1);
	return (temp);
}

int	get_object(t_scene *scene, char **words, int *flags)
{
	t_obj	*temp_obj;

	if (ft_strncmp(*words, "object", 6))
	{
		*flags |= ft_bit(OBJECT);
		temp_obj = init_object(scene);
		if (ft_strncmp(*words, "name", 4))
			get_name(temp_obj->name, ++words);
		return (TRUE);
	}
	else
		temp_obj = get_current_obj(scene);
	if (words[0][0] == '}')
		*flags &= ~(ft_bit(OBJECT));
	else if (ft_strncmp(*words, "type", 10))
		get_type(temp_obj, ++words);
	else if (ft_strncmp(*words, "radius", 6))
		get_float(&temp_obj->radius, ++words);
	else if (ft_strncmp(*words, "height", 10))
		get_float(&temp_obj->height, ++words);
	else if (ft_strncmp(*words, "origin", 6))
		get_vector(&temp_obj->pos, ++words);
	else if (ft_strncmp(*words, "direction", 9))
		get_vector(&temp_obj->dir, ++words);
	else if (ft_strncmp(*words, "color", 10))
		get_color(&temp_obj->color, ++words);
	return (TRUE);
}

int	get_camera(t_scene *scene, char **words, int *flags)
{
	if (words[0][0] == '}')
		*flags &= ~(ft_bit(CAMERA));
	else if (ft_strncmp(*words, "camera", 6))
		*flags |= ft_bit(CAMERA);
	else if (ft_strncmp(*words, "origin", 6))
		get_vector(&scene->camera.pos, ++words);
	else if (ft_strncmp(*words, "direction", 9))
		get_vector(&scene->camera.dir, ++words);
	return (TRUE);
}

int	init_light(t_scene *scene)
{
	if (scene->light == NULL)
	{
		scene->light = ft_calloc(sizeof(t_light), 1);
	}
	return (TRUE);
}

int	get_light(t_scene *scene, char **words, int *flags)
{
	if (words[0][0] == '}')
		*flags &= ~(ft_bit(LIGHT));
	else if (ft_strncmp(*words, "light", 6))
		*flags |= ft_bit(LIGHT);
	else if (ft_strncmp(*words, "origin", 6))
		get_vector(&scene->light->pos, words + 1);
	else if (ft_strncmp(*words, "color", 5))
		get_color(&scene->light->color, words + 1);
	return (TRUE);
}

int	init_scene(t_scene *scene, char **words, int *flags)
{
	char	*name;
	char	*temp;
	int		pos;

	name = NULL;
	pos = 0;
	while (!(ft_strncmp(words[pos], "name", 4)))
		pos++;
	if (ft_strncmp(words[pos], "name", 4))
	{
		pos += 2;
		while (words[pos][0] != '}')
		{
			temp = name;
			name = ft_strjoin(name, words[pos]);
			if (temp)
				free(temp);
			temp = name;
			if (words[pos - 1][0] != '{')
			{
				name = ft_strjoin(name, " ");
				if (temp)
					free(temp);
			}
			pos++;
		}
	}
	else
		name = ft_strcpy(ft_strnew(7), "Default");
	scene->name = name;
	scene->camera.pos = (t_vec3f){0.0, 0.0, 0.0};
	scene->camera.dir = (t_vec3f){0.0, 0.0, -1.0};
	scene->light = NULL;
	scene->obj = NULL;
	*flags |= ft_bit(SCENE);
	return(TRUE);
}

int	parse_file(t_scene *scene, int fd)
{
	char	*line;
	char	**words;
	int		flags;

	flags = 0;
	while (get_next_line(fd, &line))
	{
		words = ft_strsplit(line, ' ');
		if (words == NULL || words[0] == NULL)
			continue;
		if (ft_strncmp(words[0], "scene", 5) && flags == 0)
			init_scene(scene, words, &flags);
		else if (ft_strncmp(words[0], "camera", 6) || flags & ft_bit(CAMERA)) //check state and flags?
			get_camera(scene, words, &flags);
		else if (ft_strncmp(words[0], "light", 5) || flags & ft_bit(LIGHT)) //check state and flags?
		{
			if (!(flags & ft_bit(LIGHT)))
				init_light(scene);
			get_light(scene, words, &flags);
		}
		else if (ft_strncmp(words[0], "object", 6) || flags & ft_bit(OBJECT)) //check state and flags?
		{
/*			if (!(flags & ft_bit(OBJECT)))
				init_object(scene);
*/			get_object(scene, words, &flags);
		}
		else if (words[0][0] == '}')
			flags &= ~(ft_bit(SCENE));
		free(line);
		ft_arrfree(words);
	}
	//free (line);
	if (flags == 0)
		return (TRUE);
	return (FALSE);
}

int	read_input(t_scene *scene, const char *file_name)
{
	int fd;

	open_file(&fd, file_name);
	parse_file(scene, fd);
	close_file(fd);
	return (TRUE);
}
