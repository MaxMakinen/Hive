/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:55:52 by jjuntune          #+#    #+#             */
/*   Updated: 2022/11/16 21:50:00 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

//Copys 1d arrey to texture and draws it.

void	draw_filter(t_sdl *sdl, int *filter_type, int i)
{
	if (i == 1)
	{
		if (sdl->event.key.keysym.sym == SDLK_DOWN && *filter_type > 0)
			*filter_type -= 1;
		else if (sdl->event.key.keysym.sym == SDLK_DOWN)
			*filter_type = EDGE;
		else if (sdl->event.key.keysym.sym == SDLK_UP && *filter_type < 4)
			*filter_type += 1;
		else if (sdl->event.key.keysym.sym == SDLK_UP)
			*filter_type = NORMAL;
	}
	if (*filter_type == NORMAL)
		draw_to_window(sdl, sdl->frame_buffer.data);
	else if (*filter_type == CARTOON)
		draw_to_window(sdl, sdl->frame_buffer.cartoon);
	else if (*filter_type == BLACK_AND_WHITE)
		draw_to_window(sdl, sdl->frame_buffer.b_w);
	else if (*filter_type == B_W_CARTOON)
		draw_to_window(sdl, sdl->frame_buffer.b_w_cartoon);
	else if (*filter_type == EDGE)
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
}

// Infinite loop to handle the window.

void	rt_loop_and_exit(t_sdl *sdl)
{
	int	quit;
	int	filter_type;

	quit = 0;
	filter_type = NORMAL;
	while (quit == 0)
	{
		if (SDL_PollEvent(&sdl->event) != 0)
			kay_hooks(sdl, &quit, &filter_type);
		draw_filter(sdl, &filter_type, 0);
	}
	free_buffers_and_sdl(sdl);
}

void	tests(t_main *main, int draw_debug); // unit tests

int	main(void)
{
	t_main		main;
	t_matrix	cam_transform;
	t_matrix	rotate;
	t_matrix	cam_scale;
	t_matrix	scale;


	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return (1);
	if (initialize_window(&main) == 0)
		return (1);
	
	
	cam_transform = matrix_translate(0.0, 2.5, -20.0);
	double						x_r = 0.0;
	double						y_r = 0.0;
	double						z_r = 0.0;

	rotate = matrix_rotate_x(x_r);
	cam_transform = matrix_multiply(&cam_transform, &rotate);
	rotate = matrix_rotate_y(y_r);
	cam_transform = matrix_multiply(&cam_transform, &rotate);
	rotate = matrix_rotate_z(z_r);
	cam_transform = matrix_multiply(&cam_transform, &rotate);
	cam_scale = matrix_scale(1,1,1);
	cam_transform = matrix_multiply(&cam_transform, &cam_scale);
	

	main.light = point_light_new(point_new(0.0, 2.5, -20.0), color_new(1,1,1));
	// main.light.pos = point_new(10, 0, 0);
	
	main.obj[0] = object_new(PLANE);
	main.obj[0].transform = matrix_translate(0.0, 0.0, 10.0);
											x_r = 0.0;
											y_r = 0.0;
											z_r = 0.0;

	rotate = matrix_rotate_x(x_r);
	main.obj[0].transform = matrix_multiply(&main.obj[0].transform, &rotate);
	rotate = matrix_rotate_y(y_r);
	main.obj[0].transform = matrix_multiply(&main.obj[0].transform, &rotate);
	rotate = matrix_rotate_z(z_r);
	main.obj[0].transform = matrix_multiply(&main.obj[0].transform, &rotate);
	main.obj[0].material.color = color_new(0,1,1);
	main.obj[0].material.pattern.pattern_id = STRIPED;
	main.obj[0].material.pattern.pattern_perlin = FALSE;

	main.obj[1] = object_new(PLANE);
	main.obj[1].transform = matrix_translate(0.0, 0.0, 9.9999);
											x_r = -M_PI_2;
											y_r = 0.0;
											z_r = 0.0;

	rotate = matrix_rotate_x(x_r);
	main.obj[1].transform = matrix_multiply(&main.obj[1].transform, &rotate);
	rotate = matrix_rotate_y(y_r);
	main.obj[1].transform = matrix_multiply(&main.obj[1].transform, &rotate);
	rotate = matrix_rotate_z(z_r);
	main.obj[1].transform = matrix_multiply(&main.obj[1].transform, &rotate);
	main.obj[1].material.color = color_new(0,1,0);
	main.obj[1].material.pattern.pattern_id = GRID;
	main.obj[1].material.pattern.pattern_perlin = FALSE;



	main.obj[2] = object_new(SPHERE);
	main.obj[2].transform = matrix_translate(0.0, 0.0, 2.0);
											x_r = 0.0;
											y_r = 0.0;
											z_r = 0.0;

	rotate = matrix_rotate_x(x_r);
	main.obj[2].transform = matrix_multiply(&main.obj[2].transform, &rotate);
	rotate = matrix_rotate_y(y_r);
	main.obj[2].transform = matrix_multiply(&main.obj[2].transform, &rotate);
	rotate = matrix_rotate_z(z_r);
	main.obj[2].transform = matrix_multiply(&main.obj[2].transform, &rotate);
	scale = matrix_scale(5,5,5);
	main.obj[2].transform = matrix_multiply(&main.obj[2].transform, &scale);
	main.obj[2].material.color = color_new(1,0,0);
	main.obj[2].material.pattern.pattern_id = GRID;
	main.obj[2].material.pattern.pattern_perlin = TRUE;




	main.obj[3] = object_new(CONE);
	main.obj[3].transform = matrix_translate(3.0, 2.0, 5.0);
											x_r = 0.0;
											y_r = 0.0;
											z_r = 0.0;

	rotate = matrix_rotate_x(x_r);
	main.obj[3].transform = matrix_multiply(&main.obj[3].transform, &rotate);
	rotate = matrix_rotate_y(y_r);
	main.obj[3].transform = matrix_multiply(&main.obj[3].transform, &rotate);
	rotate = matrix_rotate_z(z_r);
	main.obj[3].transform = matrix_multiply(&main.obj[3].transform, &rotate);
	cam_scale = matrix_scale(0.5,1,1);
	main.obj[3].transform = matrix_multiply(&main.obj[3].transform, &cam_scale);
	main.obj[3].material.color = color_new(1, 0.5,0);
	main.obj[3].material.pattern.pattern_id = NONE;
	main.obj[3].material.pattern.pattern_perlin = FALSE;

	main.obj[4] = object_new(CYLINDER);
	main.obj[4].transform = matrix_translate(-3.0, -2.0, 5.0);
											x_r = 0.0;
											y_r = 0.0;
											z_r = 0.0;

	rotate = matrix_rotate_x(x_r);
	main.obj[4].transform = matrix_multiply(&main.obj[4].transform, &rotate);
	rotate = matrix_rotate_y(y_r);
	main.obj[4].transform = matrix_multiply(&main.obj[4].transform, &rotate);
	rotate = matrix_rotate_z(z_r);
	main.obj[4].transform = matrix_multiply(&main.obj[4].transform, &rotate);
	cam_scale = matrix_scale(1,1,1);
	main.obj[4].transform = matrix_multiply(&main.obj[4].transform, &cam_scale);
	main.obj[4].material.color = color_new(1, 0.5,0);
	main.obj[4].material.pattern.pattern_id = NONE;
	main.obj[4].material.pattern.pattern_perlin = FALSE;


	main.obj_count = 5;

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
		creat_filters(&main.sdl.frame_buffer);
	}
	tests(&main, draw_debug);


	draw_to_window(&main.sdl, main.sdl.frame_buffer.data);
	rt_loop_and_exit(&main.sdl);

	
	SDL_Quit();
	return (0);
}