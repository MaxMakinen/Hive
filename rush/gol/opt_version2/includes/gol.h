/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gol.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:53:49 by mmakinen          #+#    #+#             */
/*   Updated: 2022/06/23 18:50:23 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GOL_H
# define GOL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_data
{
	int		row;
	int		col;
	int		iterations;
	char	*pool1;
	char	*pool2;
	char	**map1;
	char	**map2;
}	t_data;

void	prep_map(char *filename, t_data *data);
void	read_map(FILE *file, t_data *data);
void	init_map(t_data *data, int len);

void	check_first_neighbours(t_data *data, int row, int col);
void	check_neighbours(t_data *data, int row, int col);
void	print_map(t_data *data, char **map);
void	gameoflife(t_data *data);

#endif
