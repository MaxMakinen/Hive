/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coords.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 13:48:26 by jsaarine          #+#    #+#             */
/*   Updated: 2022/11/06 14:51:07 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COORDS_H
# define COORDS_H
# include <stddef.h>

typedef struct s_coords
{
	size_t		row;
	size_t		col;
}	t_coords;

#endif