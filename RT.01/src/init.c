/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:13:23 by mmakinen          #+#    #+#             */
/*   Updated: 2022/08/26 14:23:57 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	init_map(t_map *map)
{
	int	*itemp;
	int	x;

	map->pool = (int *)ft_calloc(WINDOW_WIDTH * WINDOW_HEIGHT, sizeof(int));
	map->ptr = (int **)ft_calloc(WINDOW_HEIGHT, sizeof(int *));
	if (map->pool == NULL || map->ptr == NULL)
		return (FALSE);
	itemp = map->pool;
	x = 0;
	while (x < WINDOW_HEIGHT)
	{
		map->ptr[x] = itemp;
		itemp += WINDOW_WIDTH;
		x++;
	}
	return (TRUE);
}

void	get_view(t_scene *scene, t_data *data, t_obj *temp)
{
	if (temp->up.x == 0.0 && temp->up.y == 0.0 && temp->up.z == 0.0)
		temp->up = (t_vec3f){0.0, 1.0, 0.0};
	scene->view_height = 2 * tan(deg_to_rad(scene->cam->vfov) * 0.5);
	scene->view_width = data->aspect_ratio * scene->view_height;
}

void	orient_camera(t_scene *scene, t_obj *temp)
{
	t_vec3f	w;
	t_vec3f	u;
	t_vec3f	v;

	w = normalize(vec_minus(temp->pos, temp->dir));
	if (vec_compare(w, temp->up))
		w.z += 0.0000001;
	u = normalize(cross_product(temp->up, w));
	v = cross_product(w, u);
	scene->horizontal = (vec_mult(u, scene->view_width));
	scene->vertical = (vec_mult(v, scene->view_height));
	scene->lower_left = (vec_minus(vec_minus(vec_minus(temp->pos, \
	vec_mult(scene->horizontal, 0.5)), vec_mult(scene->vertical, 0.5)), w));
}

int	init_camera(t_scene *scene, t_data *data)
{
	t_obj	*temp;

	temp = scene->obj;
	while (temp && temp->type != e_camera)
	{
		if (temp->next == NULL)
			return (FALSE);
		temp = temp->next;
	}
	scene->cam = temp;
	get_view(scene, data, temp);
	orient_camera(scene, temp);
	return (TRUE);
}

void	init_data(t_data *data, t_scene *scene)
{
	t_obj	*camera;
	double	vert_temp;

	data->img = (t_img *)ft_calloc(sizeof(t_img), 1);
	if (data->img == NULL)
		exit_error("img init failed");
	data->aspect_ratio = (double)WINDOW_WIDTH / (double)WINDOW_HEIGHT;
	data->screen_min.x = 0;
	data->screen_min.y = 0;
	data->screen_min.z = 0;
	data->screen_max.x = WINDOW_WIDTH;
	data->screen_max.y = WINDOW_HEIGHT;
	data->screen_max.z = 0;
	if (!(init_camera(scene, data)))
		exit_error("camera init failed");
	if (!init_map(&data->map))
	{
		ft_putendl("init map failed");
		clean_exit(data);
	}
}
