/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:59:18 by jjuntune          #+#    #+#             */
/*   Updated: 2022/12/05 15:09:05 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATTERNS_H
# define PATTERNS_H
#include "tuple.h"
#include "object.h"
#include "matrix.h"

enum
{
	NONE,
	STRIPED,
	GRID,
};

typedef struct s_pattern
{
	t_matrix	pattern_transfor;
	int			pattern_id; //enum abow
	int			pattern_perlin; //TRUE / FALSE
	double		pattern_dif;
}	t_pattern;


int	pattern_striped(double	coordinate_in);
void	pattern_grid(t_point hit_loc, t_color *hit_color, double pattern_dif, double perlin);

#endif