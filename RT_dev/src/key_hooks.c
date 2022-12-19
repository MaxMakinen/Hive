/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 13:38:00 by jjuntune          #+#    #+#             */
/*   Updated: 2022/12/12 12:53:45 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

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

int	*get_correct_buffer(t_sdl *sdl, int *filter_type)
{
	if (*filter_type == NORMAL)
		return (sdl->frame_buffer.data);
	else if (filter_type == STEREOSCOPY)
		return (sdl->frame_buffer.stereocopy);
	else
		return (sdl->frame_buffer.filter);
}

void	kay_hooks(t_sdl *sdl, int *quit, int *filter_type)
{
	if (sdl->event.type == SDL_QUIT)
		*quit = 1;
	if (sdl->event.type == SDL_KEYDOWN)
	{
		if (sdl->event.key.keysym.sym == SDLK_ESCAPE)
			*quit = 1;
		if (sdl->event.key.keysym.sym == SDLK_DOWN
			|| sdl->event.key.keysym.sym == SDLK_UP)
			draw_filter(sdl, filter_type, 1);
		if (sdl->event.key.keysym.sym == SDLK_p)
		{
			creat_screen_shot(get_correct_buffer(sdl, filter_type));
			ft_putstr("Screen shot created\n");
		}
	}
}
