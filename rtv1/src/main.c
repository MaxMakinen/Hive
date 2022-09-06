/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 09:47:35 by mmakinen          #+#    #+#             */
/*   Updated: 2022/08/26 14:24:44 by mmakinen         ###   ########.fr       */
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
/*
int	build_scene(t_scene *scene)
{
	t_obj	*temp_obj;
	scene->camera.pos = (t_vec3f){0.0, 3.0, 30.0};
	scene->camera.dir = (t_vec3f){0.0, 0.0, -1.0};
	scene->camera_to_world = (t_mat44f){{1.0,0.0,0.0,0.0},{0.0,1.0,0.0,0.0},{0.0,0.0,1.0,0.0},{0.0,3.0,20.0,1.0}};
	scene->light.x = -40.0f;
	scene->light.y = 10.0f;
	scene->light.z = -10.0f;
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
*/
/*
	char		*name;
	t_camera	camera;
	t_mat44f	camera_to_world;
	t_light		*light;
	t_object	object;
	t_obj		*obj;
	int			max_objects;
typedef struct s_obj
{
	char			*name;
	enum e_type		type;
	t_vec3f			pos;
	t_vec3f			dir;
	t_rgb			color;
	float			radius;
	float			radius2;
	float			height;
	struct s_obj	*next;
}	t_obj;
	*/
void	print_vec(t_vec3f *vec)
{
	printf("vec.x = %f\n",vec->x);
	printf("vec.y = %f\n",vec->y);
	printf("vec.z = %f\n",vec->z);
}

void	print_scene(t_scene *scene)
{
	ft_putstr("\nname : ");
	ft_putendl(scene->name);
	ft_putstr("camera pos : \n");
	print_vec(&scene->camera.pos);
	ft_putstr("camera dir : \n");
	print_vec(&scene->camera.dir);
	ft_putstr("\nlight pos : \n");
	if (scene->light)
	{
		print_vec(&scene->light->pos);
		printf("color = %d\n", scene->light->color.color);
		printf("brightness = %f\n", scene->light->brightness);
	}
	else
		printf("no light\n");
	if (scene->obj == NULL)
		printf("\nno obj\n");
	while (scene->obj != NULL)
	{
	//	printf("name = %s\n", scene->obj->name);
//		ft_putstr("name : ");
//		if (scene->obj->name != 0 || scene->obj->name[0] != 0)
//			ft_putendl(scene->obj->name);
		printf("\ntype = %d\n", scene->obj->type);
		ft_putstr("pos : \n");
		print_vec(&scene->obj->pos);
		ft_putstr("dir : \n");
		print_vec(&scene->obj->dir);
		printf("color = %d\n", scene->obj->color.color);
		printf("radius = %f\n", scene->obj->radius);
		printf("radius2 = %f\n", scene->obj->radius2);
		printf("height = %f\n", scene->obj->height);
		if (scene->obj->next && scene->obj->next != NULL)
			scene->obj = scene->obj->next;
		else
			break;
	}
}

int	main(int ac, char **av)
{
	t_data	data;
	t_map	map;
	t_scene	scene;

	if (ac != 2)
		exit_error("Usage: ./rtv1 <input file>");
//	if (!build_scene(&scene))
//		exit_error("build scene error");
	scene.name = "default";
	read_input(&scene, av[1]);
	init_data(&data, &scene);
	create_img(&data, "scene");
	make_image(&scene, &data);
	draw(&data);
	print_scene(&scene);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, \
			data.img->mlx_img, 0, 0);
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, 2, 1L << 0, handle_keypress, &data);
	mlx_hook(data.win_ptr, 17, 0, destroy, &data);
	mlx_loop(data.mlx_ptr);
	free(data.mlx_ptr);
}
