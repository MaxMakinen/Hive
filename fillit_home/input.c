/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 10:49:00 by mmakinen          #+#    #+#             */
/*   Updated: 2022/01/18 12:36:46 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
function to append target to queue.

Example tetro : ##
				 #
				 #																  |		|
																		    ->	  v		v
If we assign shape_id in Position A, the shape_id for example tetro will be 0100 1000 1000 0000.
They only point forward to next square, never to already visited ones.		
																			 >	 v <  v  ^    ^
If we assign shape_id in Position B, the shape_id for example tero will be  0100 1010 1001 0001
They point to all neighbours, including already visited ones.

				 v>          <
 ## position A = 1100 0000 0010 0000
##				 v>     <    <^  >
    position B = 1100 0010 0011 0100

				  >   v>
### position A = 0100 1100 0000 0000
 #				  >   v><    <     ^
	position B = 0100 1110 0010 0001 
*/
void	append_queue(short *queue, t_tetro *temp, short direction, short index)
{
	short	count;
	short	found;

	count = 1;
	found = 0;
	while (count < 5)
	{
		if (queue[count++] == index)
			found = 1;
	}
	if (found == 0)
	{
		queue[++queue[0]] = index;
		temp->shape_id = temp->shape_id | direction; //Postition A
	}
//	temp->shape_id = temp->shape_id | direction; //Position B
}

/*
How thew queue works
how many targets have been found
 |
 v
[4][12][13][18][19]
    ^   ^   ^   ^
	index positions of targets 1, 2,3 and 4
##
 ##
*/

/*
function for identifying tetromino and traversing grid after finding first '#' in grid
*/

t_tetro	*recursive_finder(char *grid, t_tetro *head, short index, short *queue)
{
	t_tetro	*temp;

	temp = head;
	while (temp->next)
		temp = temp->next;
	if (queue[0] == 0)
	{
		queue[1] = index;
		queue[0] += 1;
	}
	if (temp->shape_id > 0)
		temp->shape_id = temp->shape_id << 4; //Scoot number over to make space for next key in case shape_id isn't empty.
// These can be put into a check_adjacent function.
	if (index > 5 && grid[index - 5] == '#')
		append_queue(queue, temp, 1, index - 5);
//		queue[queue[0]++] = index - 5;
//		temp->shape_id = temp->shape_id | 1; //0b0001 above.
	if (index - 1 > 0 && grid[index - 1] == '#')
		append_queue(queue, temp, 2, index - 1);
//		temp->shape_id = temp->shape_id | 2; //0b0010 to the left.
	if ((index + 1) < 21 && grid[index + 1] == '#')
		append_queue(queue, temp, 4, index + 1);
//		temp->shape_id = temp->shape_id | 4; //0b0100 to the right.
	if ((index + 5) < 21 && grid[index + 5] == '#')
		append_queue(queue, temp, 8, index + 5);
//		temp->shape_id = temp->shape_id | 8; //0b1000 below.
	if (temp->shape_id == 0 || temp->shape_id == 16) //Has no neighbours | Has too many neighbours.
		return (NULL);
	temp->blocks++; //to count how many blocks have been found so far.
	if (temp->blocks < 4)
	{
		recursive_finder(grid, head, queue[temp->blocks + 1], queue);
/*
		if (previous != 1 && temp->blocks < 4 && (temp->shape_id & 1) == 1) //check did we come from above & and is there a neighour above.
			recursive_finder(grid, head, index - 5, 8);
		if (previous != 2 && temp->blocks < 4 && (temp->shape_id & 2) == 2) //did we come from the left & is there a neighbour on the left.
			recursive_finder(grid, head, index - 1, 4);
		if (previous != 4 && temp->blocks < 4 && (temp->shape_id & 4) == 4) //did we come from the right & is there a neighbour on the right.
			recursive_finder(grid, head, index + 1, 2);
		if (previous != 8 && temp->blocks < 4 && (temp->shape_id & 8) == 8) //did we come from below & is there a neighbour below.
			recursive_finder(grid, head, index + 5, 1);
*/
	}
	return (head);
}

/*
Function to identify tetromino in grid and create a node in the linked list, or return NULL in vase of error.
*/

t_tetro	*find_tetro(char *grid, t_tetro *head)
{
	short index;
	short queue[5];

	index = 0;
	queue[0] = 0;
	while (grid[index] && grid[index] != '#')
		index++;
	if (index > 16)
		return (NULL);
	return (recursive_finder(grid, head, index, queue));

}

/*
function to make new t_tetro node. TODO why was this giving out void pointers before?
*/

t_tetro	*new_tetro(char letter)
{
	t_tetro	*newnode;

	newnode = (t_tetro *)malloc(sizeof(t_tetro));
	if (!newnode)
		return (NULL);
	newnode->shape_id = 0;
	newnode->queue[0] = 0;
	newnode->blocks = 0;
	newnode->letter = letter;
	newnode->next = NULL;
	return (newnode);
}

/*
function to add new t_tetro node to end of list
*/

t_tetro	*append_tetro(t_tetro *head)
{
	t_tetro	*temp;
	t_tetro *new;
	int		letter;

	letter = 1;
	temp = head;
	while (temp->next)
	{
		temp = temp->next;
		letter++;
	}
	new = new_tetro('A' + letter);
	if (!new)
		return (NULL);
	temp->next = new;
	return (head);
}

/*
Function that takes the opened fd as input and reads through the file, identifying tetrominos and placing them into a linked list.
Returns pointer to head of linked list.
In case of error, return NULL pointer.
*/

t_tetro *input(int fd)
{
	int			check_gnl;
	int			row;
	char		*line;
	char		grid[21];
	t_tetro		*head;
	int			hash = 0;

	head = new_tetro('A'); //function to initialize new piece in t_tetro struct
	if (head == NULL)
	{
		ft_putendl("new_tetro failed");
		return (NULL);
	}
	ft_bzero(grid, 21); // grid[0] = 0; might be faster. Will have to test if it even matters. Bzero allows us to avoid potential corrupotion by pre-existing data.
	row = 1;
	check_gnl = get_next_line(fd, &line);
	while (check_gnl > 0)
	{
		if (row > 129)
		{
			ft_putendl("row test");
			return (NULL); // We have gone past the maximum 26 tetrominos, and return NULL.
		}
		if(ft_strlen(line) != 4 && (row % 5))
		{
			ft_putendl("strlen test");
			return (NULL);
		}
		if((row % 5) == 0 && *line)
		{
			ft_putendl("row % 5 & *line test");
			return (NULL);
		}
		if (row % 5) //Checks if row is anything else than a multiple of 5. Like 5, 10, 15 etc.
		{
			hash += ft_strccount(line, '#');
			if (hash > 4)
			{
				ft_putendl("hashcount test");
				return (NULL);
			}
			ft_strlcat(grid, line, 21);
			ft_strlcat(grid, "\n", 21);
		}
		else if ((row % 5) == 0) // could propably be just an else. Checks if row is 5, 10, 15 etc. It should be the empty ine between tetro grids.
		{
			if (!find_tetro(grid, head)) //function for identifying tetromino piece. If there's an issue, return NULL.
				return (NULL);
			if (!append_tetro(head))
				return (NULL);; //add new tetro to end of list.
			ft_bzero(grid, 21); //If everything has gone well, we clean out the grid for the next tetromino.
			hash = 0;
		}
		check_gnl = get_next_line(fd, &line);
		row++;
	}
	if (!find_tetro(grid, head)) //function for identifying tetromino piece. If there's an issue, return NULL.
		return (NULL);
	return (head);
}

/*
Function to check for errors in file. Closes file at end to reset file offset, to be opened again in later.
*/

int	check_file(int fd)
{
	int		ret;
	char	str[27];

	ret = read(fd, str, 26); 
	while (ret >= 26)
		ret = read(fd, str, 26) ;
	str[ret] = 0;
	if (str[ret - 1] == '\n' && str[ret - 2] == '\n')
		return (-1);
	if (close(fd) == -1)
		return (-1);
	return (1);
}

/*
function to turn shape_id to binary
*/
unsigned long long	binary(unsigned short num)
{
	if (num == 0)
		return (0);
	if (num == 1)
		return (1);
	return (num % 2) + 10 * binary(num/2);
}

int main(void)
{
	int 	fd;
	t_tetro	*head;
	char	*filename = "tetro.txt";

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (1);
	if (check_file(fd) == -1)
	{
		ft_putendl("Check_file error");
		return (1);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (1);
	head = input(fd);
	if (!head)
	{
		ft_putendl("Input error");
		return (1);
	}
	if (close(fd) == -1)
	{
		ft_putendl("Close error");
		return (1);
	}
	while (head->next)
	{
		ft_putnbr(head->shape_id);
		ft_putstr("\n");
		ft_putchar(head->letter);
		ft_putchar('\n');
		head = head->next;
	}
	ft_putnbr(head->shape_id);
	ft_putstr("\n");
	ft_putchar(head->letter);
	ft_putchar('\n');
	return (0);
}
