/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:55:52 by jjuntune          #+#    #+#             */
/*   Updated: 2022/11/28 17:53:06 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"
#include "../include/yaxml.h"

//Copys 1d arrey to texture and draws it.

void	draw_filter(t_sdl *sdl, int *filter_type, int i)
{
	if (i == 1)
	{
		if (sdl->event.key.keysym.sym == SDLK_DOWN && *filter_type > 0)
			*filter_type -= 1;
		else if (sdl->event.key.keysym.sym == SDLK_DOWN)
			*filter_type = EDGE;
		else if (sdl->event.key.keysym.sym == SDLK_UP && *filter_type < 6)
			*filter_type += 1;
		else if (sdl->event.key.keysym.sym == SDLK_UP)
			*filter_type = STEREOSCOPY;
	}
	if (*filter_type == STEREOSCOPY)
	{
		if (sdl->stereocopy == TRUE)
			draw_to_window(sdl, sdl->frame_buffer.stereocopy);
		else
			*filter_type += 1;
	}
	if (*filter_type == NORMAL)
		draw_to_window(sdl, sdl->frame_buffer.data);
	if (*filter_type == CARTOON)
		draw_to_window(sdl, sdl->frame_buffer.cartoon);
	if (*filter_type == BLACK_AND_WHITE)
		draw_to_window(sdl, sdl->frame_buffer.b_w);
	if (*filter_type == B_W_CARTOON)
		draw_to_window(sdl, sdl->frame_buffer.b_w_cartoon);
	if (*filter_type == SEPIA)
		draw_to_window(sdl, sdl->frame_buffer.sepia);
	if (*filter_type == EDGE)
		draw_to_window(sdl, sdl->frame_buffer.edge_map);
}

static void	free_buffers_and_sdl(t_sdl *sdl)
{
	SDL_DestroyTexture(sdl->texture);
	SDL_DestroyWindow(sdl->win);
	free(sdl->frame_buffer.data);
	free(sdl->frame_buffer.cartoon);
	free(sdl->frame_buffer.b_w);
	free(sdl->frame_buffer.b_w_cartoon);
	free(sdl->frame_buffer.edge_map);
	free(sdl->frame_buffer.sepia);
}

// Infinite loop to handle the window.

void	rt_loop_and_exit(t_sdl *sdl)
{
	int	quit;
	int	filter_type;

	quit = 0;
	filter_type = STEREOSCOPY;
	while (quit == 0)
	{
		if (SDL_PollEvent(&sdl->event) != 0)
			kay_hooks(sdl, &quit, &filter_type);
		draw_filter(sdl, &filter_type, 0);
	}
	free_buffers_and_sdl(sdl);
}

void	tests(t_main *main, int draw_debug); // unit tests

int	main(int ac, char **av)
{
	t_main		main;
	t_matrix	cam_transform;
	t_matrix	rotate;
	t_matrix	cam_scale;
	t_matrix	scale;
	double	x_r;
	double	y_r;
	double	z_r;
	t_xml_doc	doc;

//	if (ac != 2)
//	{
//		ft_putendl_fd("Usage: Give .xml file as input", 2);
//		return (1);
//	}
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return (1);
	if (initialize_window(&main) == 0)
		return (1);
		//FREE BUFFERS!!!!!!
	
	main.sdl.stereocopy = FALSE;
	cam_transform = matrix_translate(0.0, 0.0, -10.0);

	cam_scale = matrix_scale(1,1,1);
	cam_transform = matrix_multiply(&cam_transform, &cam_scale);
	main.cam.coi = point_new(0.0, 0.0, 0.0);

	main.light = point_light_new(point_new(0.0, 2.5, -10.0), color_new(1,1,1));
	//main.light.pos = point_new(10, 0, 0);
	if (ac == 2)
	{
		if (!xml_doc_load(&doc, av[1]))
		{
			ft_putendl_fd("couldn't read file!", 2);
			return (1);
		}
		read_xml(&doc, &main);
		xml_doc_free(&doc);
	}
	else
	{
		main.obj[0] = object_new(SPHERE);
		main.obj[0].transform = matrix_translate(0.2, 0.0, 10.0);
												x_r = 0.0;
												y_r = 0.0;
												z_r = 0.0;

		rotate = matrix_rotate_x(x_r);
		main.obj[0].transform = matrix_multiply(&main.obj[0].transform, &rotate);
		rotate = matrix_rotate_y(y_r);
		main.obj[0].transform = matrix_multiply(&main.obj[0].transform, &rotate);
		rotate = matrix_rotate_z(z_r);
		main.obj[0].transform = matrix_multiply(&main.obj[0].transform, &rotate);
		scale = matrix_scale(4,4,4);
		main.obj[0].transform = matrix_multiply(&main.obj[0].transform, &scale);
		main.obj[0].material.color = color_new(1, 0.3,0.1);
		main.obj[0].material.pattern.pattern_id = GRID;
		main.obj[0].material.pattern.pattern_perlin = TRUE;
		main.obj[0].negative = FALSE;

		main.obj[0] = object_new(CONE);
		main.obj[0].transform = matrix_translate(5.0, 2.0, 20.0);
												x_r = 0.0;
												y_r = 0.0;
												z_r = 0.0;

		rotate = matrix_rotate_x(x_r);
		main.obj[1].transform = matrix_multiply(&main.obj[1].transform, &rotate);
		rotate = matrix_rotate_y(y_r);
		main.obj[1].transform = matrix_multiply(&main.obj[1].transform, &rotate);
		rotate = matrix_rotate_z(z_r);
		main.obj[1].transform = matrix_multiply(&main.obj[1].transform, &rotate);
		scale = matrix_scale(0.5, 1, 1);
		main.obj[1].transform = matrix_multiply(&main.obj[1].transform, &scale);
		main.obj[1].material.color = color_new(1, 0.5, 0);
		main.obj[1].material.pattern.pattern_id = NONE;
		main.obj[1].material.pattern.pattern_perlin = FALSE;
		main.obj[1].negative = FALSE;

		main.obj_count = 2;
	}
	int draw_debug = 0;

	if (!draw_debug)
	{
		initialize_camera(&main.cam, cam_transform);
		load_perlin_data(&main.perlin);
		create_threads(&main, 1);
		draw_frame(&main);
		while (main.multi.threads_done < NUM_THREADS)
			ft_putstr("");
		edge_detection(&main.sdl.frame_buffer);
		main.ant_al = A_A_DIV;
		draw_frame(&main);
		
		if (main.sdl.stereocopy == TRUE)
			create_stereoscope(&main, cam_scale, cam_transform);
		creat_filters(&main.sdl.frame_buffer);
	}
//	tests(&main, draw_debug);
	rt_loop_and_exit(&main.sdl);
	SDL_Quit();
	return (0);
}