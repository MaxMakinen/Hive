/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:10:32 by mmakinen          #+#    #+#             */
/*   Updated: 2022/05/04 13:23:58 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	destroy(void	*param)
{
	clean_exit(param);
	exit(0);
}

void	free_matrix(t_matrix **matrix)
{
	free((*matrix)->pool);
	(*matrix)->pool = NULL;
	free((*matrix)->m);
	(*matrix)->m = NULL;
	free(*matrix);
	*matrix = NULL;
}

void	free_coord(t_coord **coord)
{
	free(*coord);
	*coord = NULL;
}

void	free_map(t_map **map)
{
	free_matrix(&(*map)->proj);
	free_matrix(&(*map)->rot_x);
	free_matrix(&(*map)->rot_y);
	free_matrix(&(*map)->rot_z);
	free((*map)->coords);
	(*map)->coords = NULL;
	free_coord(&(*map)->pool);
	free((*map)->vec);
	(*map)->vec = NULL;
	free_coord(&(*map)->pvec);
	free(*map);
	*map = NULL;
}

void	clean_exit(t_data *data)
{
	free_map(&data->map);
	mlx_destroy_image(data->mlx_ptr, data->img->mlx_img);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	exit(0);
}
