/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <dmalesev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:01:42 by dmalesev          #+#    #+#             */
/*   Updated: 2022/05/03 14:31:16 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	perspective(t_utils *utils, int elev, int rot_x, int rot_y)
{
	utils->slid.elev = elev;
	utils->rot.alpha = rot_x;
	utils->rot.beta = rot_y;
}

void	change_persp(t_utils *utils)
{
	utils->perspective += 1;
	if (utils->perspective == 3)
		utils->perspective = 0;
	if (utils->perspective == 0)
		perspective(utils, 5, 45, 315);
	if (utils->perspective == 1)
		perspective(utils, 0, 90, 270);
	if (utils->perspective == 2)
		perspective(utils, 10, 0, 270);
	init_proj(utils);
	init_pmatrix(utils);
	init_rmatrix_x(utils);
	init_rmatrix_y(utils);
}

int	key_down(int key, void *param)
{
	t_utils	*utils;

	utils = param;
	if (key == 53 || key == 65307)
		close_fdf(utils, "Exited program succesfully using ESC.", 1);
	if (key == 35)
		print_map(utils);
	if (key == 49)
		change_persp(utils);
	if (key == 47)
		utils->reference *= -1;
	render_screen(utils);
	return (0);
}
