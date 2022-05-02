/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:18:20 by mmakinen          #+#    #+#             */
/*   Updated: 2022/05/02 18:09:56 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int mouse_press(int button, int x, int y, t_data *data)
{
	if (button == MOUSE_SCROLL_UP)
		zoom(data, -1);
	if (button == MOUSE_SCROLL_DOWN)
		zoom(data, 1);
	project(data->map, data->map->proj);
	render(data);
	printf("Mouse press, button %d at %dx%d.\n",button,x,y);
	return (1);
}
