/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:55:20 by mmakinen          #+#    #+#             */
/*   Updated: 2022/01/31 15:40:03 by mmakinen         ###   ########.fr       */
/*   Updated: 2022/01/21 15:46:55 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
Example for building and testing main.
*/
int	main(int argc, char **argv)
{
	int		fd;
	t_tetro	*head;
	t_utils utils;

	if (argc != 2)
		return (print_usage());
	open_fd(argv[1], &fd);
	head = new_tetro('A');
	head = input(fd, &head);
	close_fd(fd);
	if (!head)
		return (error(3));
	utils = solver_iterative(head);
	ft_putendl("\n\n***ITERATIVE ANSWER***");
	ft_putendl(utils.grid);
	free(utils.grid);
	if (head)
		free_list(head);
	return (0);
}
