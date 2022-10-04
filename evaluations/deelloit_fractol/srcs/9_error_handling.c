/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_error_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 10:39:26 by deelliot          #+#    #+#             */
/*   Updated: 2022/08/11 11:49:14 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	free_win(t_win *win)
{
	if (win->img.img)
		mlx_destroy_image(win->mlx, win->img.img);
	if (win->mlx && win->win)
		mlx_destroy_window(win->mlx, win->win);
	if (win)
		return ;
}

void	handle_errors(t_win	*win)
{
	free_win(win);
	ft_stderror("error");
	exit(1);
}
