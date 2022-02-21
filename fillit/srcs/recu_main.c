/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recu_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:55:20 by mmakinen          #+#    #+#             */
/*   Updated: 2022/02/21 14:43:28 by mmakinen         ###   ########.fr       */
/*   Updated: 2022/01/21 15:46:55 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
Our main, after error checks and opening FD i creates a head for our
linked list and then calls input to find all tetros in input file.
It solves for smallest possible square by calling solver.
Once everything is done it frees all pointers.
*/

int	main(int argc, char **argv)
{
	int		fd;
	t_tetro	*head;
	t_utils	utils;

	if (argc != 2)
		return (print_usage());
	if (open_fd(argv[1], &fd) == -1)
		return (1);
	head = new_tetro('A');
	head = input(fd, &head);
	if (close_fd(fd) == -1)
		return (2);
	if (!head)
		return (error(3));
	utils = solver(head);
	ft_putstr(utils.grid);
	free(utils.grid);
	if (head)
		free_list(head);
	return (0);
}
