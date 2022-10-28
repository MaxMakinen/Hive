/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:43:10 by jjuntune          #+#    #+#             */
/*   Updated: 2022/10/20 17:00:42 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

static int	initialize_buffers(t_frame_buffer *fb)
{
	fb->data_len = (WIN_H * WIN_W);
	fb->data = (int *)malloc(sizeof(int) * fb->data_len);
	fb->cartoon = (int *)malloc(sizeof(int) * fb->data_len);
	fb->b_w = (int *)malloc(sizeof(int) * fb->data_len);
	fb->b_w_cartoon = (int *)malloc(sizeof(int) * fb->data_len);
	fb->edge_map = (int *)malloc(sizeof(int) * fb->data_len);
	fb->mask = (char *)malloc(sizeof(char) * fb->data_len);
	if (fb->data == NULL || fb->cartoon == NULL || fb->b_w == NULL
		||fb->b_w_cartoon == NULL || fb->edge_map == NULL
		|| fb->mask == NULL)
		return (0);
	return (1);
}

int	initialize_window(t_main *main)
{
	main->sdl.win = SDL_CreateWindow("RT", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, 0);
	if (main->sdl.win == NULL)
		return (0);
	main->sdl.ren = SDL_CreateRenderer(main->sdl.win, -1, 0);
	if (main->sdl.ren == NULL)
		return (0);
	main->sdl.texture = SDL_CreateTexture(main->sdl.ren, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_STREAMING, WIN_W, WIN_H);
	if (main->sdl.texture == NULL)
		return (0);
	if (initialize_buffers(&main->sdl.frame_buffer) == 0)
		return (0);
	init_pthread(main);
	return (1);
}

void	initialize_camera(t_cam *cam)
{
	double	angle;

	cam->v_up = div_vect_float(cam->v_up,
			sqrt(vec3_dot(cam->v_up, cam->v_up)));
	cam->n = vec3_sub(cam->pos, cam->coi);
	cam->n = div_vect_float(cam->n,
			sqrt(vec3_dot(cam->n, cam->n)));
	cam->n = div_vect_float(cam->n, -1.0);
	angle = vec3_dot(cam->v_up, cam->n);
	if (angle == 1 || angle == -1)
		cam->v_up = add_vect_float(cam->v_up, 0.001);
	cam->u = vec3_cross(cam->n, cam->v_up);
	cam->u = div_vect_float(cam->u,
			sqrt(vec3_dot(cam->u, cam->u)));
	cam->v = vec3_cross(cam->u, cam->n);
	cam->c = vec3_sub(cam->pos,
			multiply_vect_float(cam->n, 0.1));
	cam->plane_h = tan(1.04719 / 2) * 2 * 0.1;
	cam->plane_w = cam->plane_h * ((float)WIN_W / WIN_H);
	cam->l = vec3_sub(cam->c,
			multiply_vect_float(cam->u, (cam->plane_w / 2.0)));
	cam->l = vec3_sub(cam->l,
			multiply_vect_float(cam->v, cam->plane_h / 2.0));
}

void	initialize_ray(t_ray *ray, double x, double y, t_cam *cam)
{
	ray->dir = vec3_add(cam->l, multiply_vect_float(cam->u,
				x * (cam->plane_w / WIN_W)));
	ray->dir = vec3_add(ray->dir, multiply_vect_float(cam->v,
				y * (cam->plane_h / WIN_H)));
	ray->dir = vec3_sub(cam->pos, ray->dir);
	ray->dir = div_vect_float(ray->dir, sqrt(vec3_dot(ray->dir, ray->dir)));
}
