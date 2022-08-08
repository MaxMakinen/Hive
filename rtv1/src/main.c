/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 09:47:35 by mmakinen          #+#    #+#             */
/*   Updated: 2022/08/08 11:22:37 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	clean_exit(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img->mlx_img);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	free(data->img);
	free(data->map.pool);
	free(data->map.ptr);
	data->img = NULL;
	data->map.pool = NULL;
	data->map.ptr = NULL;
	exit(0);
}

int	destroy(void	*param)
{
	clean_exit(param);
	return (1);
}

void	exit_error(char *str)
{
	ft_putendl(str);
	exit(1);
}

void	draw(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			img_pix_put(data->img, x, y, data->map.ptr[y][x]);
			x++;
		}
		y++;
	}
}

int	build_scene(t_scene *scene)
{
	t_obj	*temp_obj;

	scene->camera.x = 0.0f;
	scene->camera.y = 3.0f;
	scene->camera.z = 30.0f;
	scene->light.x = -10.0f;
	scene->light.y = 10.0f;
	scene->light.z = 10.0f;
	scene->light_dir.x = 1.0f;
	scene->light_dir.y = -1.0f;
	scene->light_dir.z = 1.0f;

	temp_obj = (t_obj *)ft_calloc(sizeof(t_obj), 1);
	if (temp_obj == NULL)
		return (FALSE);
	scene->head = temp_obj;

	temp_obj->position.x = 5.0f;
	temp_obj->position.y = 4.0f;
	temp_obj->position.z = 0.0f;
	temp_obj->normal.x = 0.0f;
	temp_obj->normal.y = 0.0f;
	temp_obj->normal.z = 0.0f;
	temp_obj->color.color = 0xffff00ff;
	temp_obj->radius = 5.0f;
	temp_obj->radius2 = scene->head->radius * scene->head->radius;
	temp_obj->func = &sphere_intersect;
	temp_obj->next = (t_obj *)ft_calloc(sizeof(t_obj), 1);
	if (temp_obj == NULL)
		return (FALSE);

	temp_obj = temp_obj->next;

	temp_obj->position.x = 0.0f;
	temp_obj->position.y = 0.0f;
	temp_obj->position.z = 0.0f;
	temp_obj->normal.x = 0.0f;
	temp_obj->normal.y = 1.0f;
	temp_obj->normal.z = 0.0f;
	temp_obj->color.color = 0xff00ffff;
	temp_obj->radius = 0.0f;
	temp_obj->radius2 = scene->head->radius * scene->head->radius;
	temp_obj->func = &plane_intersect;
	temp_obj->next = NULL;
	return(TRUE);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_map	map;
	t_scene	scene;

	if (ac != 1)
		exit_error("Usage: ./rtv1");
	if (!build_scene(&scene))
		exit_error("build scene error");
	init_data(&data, &scene);
	create_img(&data, "scene");
	make_image(&scene, &data);
	draw(&data);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, \
			data.img->mlx_img, 0, 0);
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, 2, 1L << 0, handle_keypress, &data);
	mlx_hook(data.win_ptr, 17, 0, destroy, &data);
	mlx_loop(data.mlx_ptr);
	free(data.mlx_ptr);
}
