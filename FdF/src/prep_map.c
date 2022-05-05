/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:31:07 by mmakinen          #+#    #+#             */
/*   Updated: 2022/05/05 14:31:47 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	malloc_struct(t_map *map)
{
	map->coords = (t_coord **)ft_calloc(map->y_max, sizeof(t_coord *));
	if (!map->coords)
		ft_error(ERR_MALLOC);
	map->pool = (t_coord *)ft_calloc(map->x_max * map->y_max, sizeof(t_coord));
	if (!map->pool)
		ft_error(ERR_MALLOC);
	map->vec = (t_coord **)ft_calloc(map->y_max, sizeof(t_coord *));
	if (!map->vec)
		ft_error(ERR_MALLOC);
	map->pvec = (t_coord *)ft_calloc(map->y_max * map->x_max, sizeof(t_coord));
	if (!map->pvec)
		ft_error(ERR_MALLOC);
}

void	prep_map(t_map *map)
{
	int		counter;
	t_coord	*temp_coord;
	t_coord	*temp_vec;

	counter = 0;
	malloc_struct(map);
	temp_coord = map->pool;
	temp_vec = map->pvec;
	while (counter < map->y_max)
	{
		*(map->coords + counter) = temp_coord;
		temp_coord += map->x_max;
		*(map->vec + counter) = temp_vec;
		temp_vec += map->x_max;
		counter++;
	}
}
