/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:55:52 by jjuntune          #+#    #+#             */
/*   Updated: 2022/10/20 19:01:17 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

//Copys 1d arrey to texture and draws it.

void	draw_to_window(t_sdl *sdl, int *filter)
{
	int		*texture_data;
	int		texture_pitch;

	SDL_LockTexture(sdl->texture, NULL, (void **)&texture_data, &texture_pitch);
	ft_memcpy(texture_data, filter,
		(sdl->frame_buffer.data_len * sizeof(int)));
	SDL_UnlockTexture(sdl->texture);
	SDL_RenderCopy(sdl->ren, sdl->texture, NULL, NULL);
	SDL_RenderPresent(sdl->ren);
}

void	draw_filter(t_sdl *sdl, int *filter_type, int i)
{
	
	if (i == 1)
	{
		if (sdl->event.key.keysym.sym == SDLK_DOWN && *filter_type > 0)
			*filter_type -= 1;
		else if (sdl->event.key.keysym.sym == SDLK_DOWN)
			*filter_type = 4;
		else if (sdl->event.key.keysym.sym == SDLK_UP && *filter_type < 4)
			*filter_type += 1;
		else if (sdl->event.key.keysym.sym == SDLK_UP)
			*filter_type = 0;
	}
	if (*filter_type == 0)
		draw_to_window(sdl, sdl->frame_buffer.data);
	else if (*filter_type == 1)
		draw_to_window(sdl, sdl->frame_buffer.cartoon);
	else if (*filter_type == 2)
		draw_to_window(sdl, sdl->frame_buffer.b_w);
	else if (*filter_type == 3)
		draw_to_window(sdl, sdl->frame_buffer.b_w_cartoon);
	else if (*filter_type == 4)
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
	filter_type = 0;
	while (quit == 0)
	{
		
		if (SDL_WaitEvent(&sdl->event) != 0)
		{
			if (sdl->event.type == SDL_QUIT)
				quit = 1;
			if (sdl->event.type == SDL_KEYDOWN)
			{
				if (sdl->event.key.keysym.sym == SDLK_ESCAPE)
					quit = 1;
				if (sdl->event.key.keysym.sym == SDLK_DOWN
					|| sdl->event.key.keysym.sym == SDLK_UP)
					draw_filter(sdl, &filter_type, 1);
			}
		}
		draw_filter(sdl, &filter_type, 0);
	}
	free_buffers_and_sdl(sdl);
}

int	main(void)
{
	t_main	main;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return (1);
	if (initialize_window(&main) == 0)
		return (1);
	main.cam.pos.x = 0.0;
	main.cam.pos.y = 0.0;
	main.cam.pos.z = 0.0;
	
	main.cam.v_up.x = 0.0;
	main.cam.v_up.y = 1.0;
	main.cam.v_up.z = 0.0;
	
	main.cam.coi.x = 0.0;
	main.cam.coi.y = 0.0;
	main.cam.coi.z = 10.0;

	main.light.pos.x = 10.0;
	main.light.pos.y = 0.0;
	main.light.pos.z = 0.0;

		//0 = sphere
		//1 = cylinder
		//2 = plane
		//3 = cone

		
	main.obj[0].loc.x = 0.0;
	main.obj[0].loc.y = 0.0;
	main.obj[0].loc.z = 30.0;
	main.obj[0].size = 3.0;
	main.obj[0].type = 0;
	main.obj[0].color.rgb.r = 0.0;
	main.obj[0].color.rgb.g = 1.0;
	main.obj[0].color.rgb.b = 0.0;
	
	main.obj[1].loc.x = 5.0;
	main.obj[1].loc.y = 0.0;
	main.obj[1].loc.z = 30.0;
	main.obj[1].size = 0.1;
	main.obj[1].type = 0;
	main.obj[1].color.rgb.r = 1.0;
	main.obj[1].color.rgb.g = 0.0;
	main.obj[1].color.rgb.b = 0.0;

	main.obj[2].loc.x = 0.0;
	main.obj[2].loc.y = 0.0;
	main.obj[2].loc.z = 40.0;
	main.obj[2].rot.x = 0.0;
	main.obj[2].rot.y = 0.0;
	main.obj[2].rot.z = 1.0;
	main.obj[2].type = 2;
	main.obj[2].color.rgb.r = 1.0;
	main.obj[2].color.rgb.g = 1.0;
	main.obj[2].color.rgb.b = 1.0;

	main.obj[3].loc.x = 0.0;
	main.obj[3].loc.y = -10.0;
	main.obj[3].loc.z = 40.0;
	main.obj[3].rot.x = 0.0;
	main.obj[3].rot.y = 1.0;
	main.obj[3].rot.z = 0.0;
	main.obj[3].type = 2;
	main.obj[3].color.rgb.r = 0.0;
	main.obj[3].color.rgb.g = 1.0;
	main.obj[3].color.rgb.b = 1.0;
		
	main.obj[4].loc.x = 0.0;
	main.obj[4].loc.y = 0.0;
	main.obj[4].loc.z = 30.0;
	main.obj[4].rot.x = 1.0;
	main.obj[4].rot.y = 1.0;
	main.obj[4].rot.z = 1.0;
	main.obj[4].type = 1;
	main.obj[4].size = 1;
	main.obj[4].color.rgb.r = 1.0;
	main.obj[4].color.rgb.g = 1.0;
	main.obj[4].color.rgb.b = 1.0;

	main.obj[5].loc.x = 0.0;
	main.obj[5].loc.y = 0.0;
	main.obj[5].loc.z = 30.0;
	main.obj[5].rot.x = -1.0;
	main.obj[5].rot.y = 1.0;
	main.obj[5].rot.z = 1.0;
	main.obj[5].type = 1;
	main.obj[5].size = 0.5;
	main.obj[5].color.rgb.r = 1.0;
	main.obj[5].color.rgb.g = 0.0;
	main.obj[5].color.rgb.b = 1.0;

	main.obj[6].loc.x = -10.0;
	main.obj[6].loc.y = 0.0;
	main.obj[6].loc.z = 30.0;
	main.obj[6].rot.x = 0.0;
	main.obj[6].rot.y = 1.0;
	main.obj[6].rot.z = 0.0;
	main.obj[6].type = 3;
	main.obj[6].size = 1;
	main.obj[6].color.rgb.r = 1.0;
	main.obj[6].color.rgb.g = 0.1;
	main.obj[6].color.rgb.b = 0.8;
	main.obj_count = 7;
	
	initialize_camera(&main.cam);
	create_threads(&main, 1);
	draw_frame(&main);
	edge_detection(&main.sdl.frame_buffer);
	main.ant_al = A_A_DIV;
	draw_frame(&main);
	creat_filters(&main.sdl.frame_buffer);
	draw_to_window(&main.sdl, main.sdl.frame_buffer.data);
	rt_loop_and_exit(&main.sdl);
	SDL_Quit();
	return (0);
}
