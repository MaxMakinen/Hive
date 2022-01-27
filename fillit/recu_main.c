/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:55:20 by mmakinen          #+#    #+#             */
/*   Updated: 2022/01/26 17:15:57 by mmakinen         ###   ########.fr       */
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
	if (open_fd(argv[1], &fd) == -1)
		return (1);
	head = input(fd, &head);
	if (close_fd(fd) == -1)
		return (2);
	if (!head)
		return (error(3));
/*	int x = 0;
	t_tetro	*temp = head;
	while (temp->next)
	{
		while (x < 5)
		{
			ft_putnbr(temp->queue[x++]);
			ft_putstr(", ");
		}
		ft_putchar('\n');
		temp = temp->next;
		x = 0;
	}
	while (x < 5)
	{
		ft_putnbr(temp->queue[x++]);
		ft_putstr(", ");
	}
	ft_putendl("solution follows");*/
//	solver(head);
	utils = solver(head);
	ft_putendl("\n\n***RECURSIVE ANSWER***");
	ft_putendl(utils.grid);
	free(utils.grid);
/*mmakinen tests. Prints out content of struct list*/
/*	t_tetro	*temp = head;
	while (temp->next)
	{
		ft_putnbr(temp->shape_id);
		ft_putstr("\n");
		ft_putchar(temp->letter);
		ft_putchar('\n');
		temp = temp->next;
	}
	ft_putnbr(temp->shape_id);
	ft_putstr("\n");
	ft_putchar(temp->letter);
	ft_putchar('\n');
*/
	if (head)
		free_list(head);
	return (0);
}
