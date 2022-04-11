/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 10:37:58 by mmakinen          #+#    #+#             */
/*   Updated: 2022/04/11 15:57:49 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>

typedef struct s_coord
{
    int invisible;
    int height;
}   t_coord;

typedef struct s_map
{
	int 	x_max;
	int		y_max;
	t_coord	**coords;
	t_coord	*pool;
}	t_map;

t_map	input(char *filename, t_map *map);
void	prep_map(t_map *map);
void	count_elems(char *filename, int *fd, t_map *map);
int		openfd(char *filename, int *fd);
int		closefd(int fd);
#endif
