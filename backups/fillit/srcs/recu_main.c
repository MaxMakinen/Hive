/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recu_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:55:20 by mmakinen          #+#    #+#             */
/*   Updated: 2022/02/08 10:03:54 by mmakinen         ###   ########.fr       */
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
	ft_putendl(utils.grid);
	free(utils.grid);
	if (head)
		free_list(head);
	return (0);
}
