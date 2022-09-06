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

	num = 0.0f;
	if (str)
	{
		temp = ft_strsplit(str, '.');
		if (temp && *temp)
		{
			num = (float)ft_atoi(temp[1]) / powf(10.0f, (float)ft_strlen(temp[1]));
			num += (float)ft_atoi(temp[0]);
		}
	}
	return (num);
}

int	get_vector(t_vec3f *vector, char **words)
{
	printf("get vec %s\n", words[0]);
	vector->x = ft_atof(words[0]);
	printf("vec x = %f\n", vector->x);
	vector->y = ft_atof(words[1]);
	printf("vec y = %f\n", vector->y);
	vector->z = ft_atof(words[2]);
	printf("vec z = %f\n", vector->z);

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
	if (ft_strncmp(*words, "sphere", 6) == 0)
		obj->type = sphere;
	else if (ft_strncmp(*words, "plane", 5) == 0)
		obj->type = plane;
	else if (ft_strncmp(*words, "cylinder", 8) == 0)
		obj->type = cylinder;
	else if (ft_strncmp(*words, "cone", 54) == 0)
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

	if (ft_strncmp(*words, "object", 6) == 0)
	{
		*flags |= ft_bit(OBJECT);
		temp_obj = init_object(scene);
		if (ft_strncmp(*words, "name", 4) == 0)
			get_name(temp_obj->name, ++words);
		return (TRUE);
	}
	else
		temp_obj = get_current_obj(scene);
	if (words[0][0] == '}')
		*flags &= ~(ft_bit(OBJECT));
	else if (ft_strncmp(*words, "type", 10) == 0)
		get_type(temp_obj, ++words);
	else if (ft_strncmp(*words, "radius", 6) == 0)
		get_float(&temp_obj->radius, ++words);
	else if (ft_strncmp(*words, "height", 10) == 0)
		get_float(&temp_obj->height, ++words);
	else if (ft_strncmp(*words, "origin", 6) == 0)
		get_vector(&temp_obj->pos, ++words);
	else if (ft_strncmp(*words, "direction", 9) == 0)
		get_vector(&temp_obj->dir, ++words);
	else if (ft_strncmp(*words, "color", 10) == 0)
		get_color(&temp_obj->color, ++words);
	return (TRUE);
}

int	get_camera(t_scene *scene, char **words, int *flags)
{
	printf("	CAMERA\n");
	if (words[0][0] == '}')
		*flags &= ~(ft_bit(CAMERA));
//	else if (ft_strncmp(*words, "}", 1))
//		*flags &= ~(ft_bit(CAMERA));
	else if (ft_strncmp(*words, "camera", 6) == 0)
		*flags |= ft_bit(CAMERA);
	else if (ft_strncmp(*words, "origin", 6) == 0)
		get_vector(&scene->camera.pos, ++words);
	else if (ft_strncmp(*words, "direction", 9) == 0)
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
	printf("	LIGHT\n");
	if (words[0][0] == '}')
		*flags &= ~(ft_bit(LIGHT));
	else if (ft_strncmp(*words, "light", 6) == 0)
		*flags |= ft_bit(LIGHT);
	else if (ft_strncmp(*words, "origin", 6) == 0)
		get_vector(&scene->light->pos, words + 1);
	else if (ft_strncmp(*words, "color", 5) == 0)
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
	while ((ft_strncmp(words[pos], "name", 4)))
		pos++;
	if (ft_strncmp(words[pos], "name", 4) == 0)
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
		if (words == NULL || words[0] == NULL || !**words)
		{
			printf("		EMPTY LINE\n");
			flags |= ft_bit(SCENE);
			free(line);
			ft_arrfree(words);
			continue;
		}
		if (ft_strncmp(words[0], "scene", 5) == 0 && flags == 0)
			init_scene(scene, words, &flags);
		else if (ft_strncmp(words[0], "camera", 6) == 0 || flags & ft_bit(CAMERA)) //check state and flags?
			get_camera(scene, words, &flags);
		else if (ft_strncmp(words[0], "light", 5) == 0 || flags & ft_bit(LIGHT)) //check state and flags?
		{
			//if (!(flags & ft_bit(LIGHT)))
			if (ft_strncmp(words[0], "light", 5))
				init_light(scene);
			get_light(scene, words, &flags);
		}
		else if (ft_strncmp(words[0], "object", 6) == 0|| flags & ft_bit(OBJECT)) //check state and flags?
		{
/*			if (!(flags & ft_bit(OBJECT)))
				init_object(scene);
*/			get_object(scene, words, &flags);
		}
		else if (words[0][0] == '}')
			flags = 0;
			//flags &= ~(ft_bit(SCENE));
		free(line);
		ft_arrfree(words);
	}
	//free (line);
	if (flags == 0)
		return (TRUE);
	return (FALSE);
}

void	parse(t_scene *scene, const int fd)
{
	char	*line;
	char	**words;
	int		flags;
	t_light	*light;
	t_obj	*obj;

	flags = 0;
	scene->light = NULL;
	scene->obj = NULL;
	while (get_next_line(fd, &line))
	{
		if (*line == 0)
		{
			flags = 0;
			continue;
		}
		if (line && *line)
		{
			printf("%s\n", line);
			words = ft_strsplit(line, ' ');
			if (words)
			{
				if (ft_strncmp(words[0], "camera", 6) == 0)
				{
					printf("word = %s\n", words[0]);
					printf("flags = %d\n", flags);
					flags |= ft_bit(CAMERA);
					printf("flags camera = %d\n", flags);
					continue;
				}
				else if (ft_strncmp(words[0], "light", 4) == 0)
				{
					flags |= ft_bit(LIGHT);
					printf("word = %s\n", words[0]);
					light = scene->light;
/*					if (light != NULL)
					{
						while (light->next != NULL)
						light = scene->light;
					}
					else
					{
						while 
					}*/
					scene->light = ft_calloc(sizeof(t_light), 1);
					printf("flags light = %d\n", flags);
					continue;
				}
				else if (ft_strncmp(words[0], "sphere", 6) == 0)
				{
					flags |= ft_bit(SPHERE);
					scene->obj = ft_calloc(sizeof(t_obj), 1);
					scene->obj->type = sphere;
					scene->obj->next = NULL;
					printf("flags sphere= %d\n", flags);
					continue;
				}
				else if (ft_strncmp(words[0], "plane", 6) == 0)
				{
					flags |= ft_bit(PLANE);
					scene->obj = ft_calloc(sizeof(t_obj), 1);
					scene->obj->type = plane;
					printf("flags plane= %d\n", flags);
					continue;
				}
			}
			if (*words && (flags & ft_bit(CAMERA)))
			{
				if (words[0][0] != '-')
				{
					free(line);
					ft_arrfree(words);
					flags = 0;
					continue;
				}
				if (ft_strncmp(words[1], "pos", 3) == 0)
				{
					get_vector(&scene->camera.pos, &words[2]);
				}
				else if (ft_strncmp(words[1], "dir", 3) == 0)
				{
					get_vector(&scene->camera.dir, &words[2]);
				}
			}
			if (*words && (flags & ft_bit(LIGHT)))
			{
				if (words[0][0] != '-')
				{
					free(line);
					ft_arrfree(words);
					flags = 0;
					continue;
				}
				if (ft_strncmp(words[1], "pos", 3) == 0)
				{
					get_vector(&scene->light->pos, &words[2]);
				}
				else if (ft_strncmp(words[1], "color", 5) == 0)
				{
					scene->light->color.color = ft_atoi(words[2]);
				}
			}
			if (*words && (flags & ft_bit(SPHERE)))
			{
				if (words[0][0] != '-')
				{
					free(line);
					ft_arrfree(words);
					flags = 0;
					continue;
				}
				if (ft_strncmp(words[1], "pos", 3) == 0)
				{
					get_vector(&scene->obj->pos, &words[2]);
				}
				else if (ft_strncmp(words[1], "dir", 3) == 0)
				{
					get_vector(&scene->obj->dir, &words[2]);
				}
				else if (ft_strncmp(words[1], "color", 5) == 0)
				{
					scene->obj->color.color = ft_atoi(words[2]);
				}
				else if (ft_strncmp(words[1], "radius", 6) == 0)
				{
					scene->obj->radius = ft_atoi(words[2]);
				}
			}
/*			if (*words && (flags & ft_bit(PLANE)))
			{
				if (words[0][0] != '-')
				{
					free(line);
					ft_arrfree(words);
					flags = 0;
					continue;
				}
				if (ft_strncmp(words[1], "pos", 3) == 0)
				{
					get_vector(&scene->light->pos, &words[2]);
				}
				else if (ft_strncmp(words[1], "color", 3) == 0)
				{
					scene->light->color.color = ft_atoi(words[2]);
				}
			}*/
			ft_arrfree(words);
		}
		free(line);
	}
}

int	read_input(t_scene *scene, const char *file_name)
{
	int fd;

	open_file(&fd, file_name);
//	parse_file(scene, fd);
	parse(scene, fd);
	close_file(fd);
	return (TRUE);
}
