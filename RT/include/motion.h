/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:53:25 by jjuntune          #+#    #+#             */
/*   Updated: 2022/12/07 10:54:04 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOTION_H
# define MOTION_H

# include "tuple.h"
# include "matrix.h"

typedef struct s_motion_blur
{
	int		on_off; // True / False
	double	speed; // distance for the motionblur +0.1 to dir while speed_iteration < speed
	double	speed_iteration;
	t_tuple	dir; // direction of the movement. normalised ( tuple_unit(...) ).
}			t_motion_blur;



t_matrix	motion_move(t_matrix orig, t_motion_blur *motion);
t_motion_blur motion_new(int true_false, double speed, t_tuple dir);
#endif