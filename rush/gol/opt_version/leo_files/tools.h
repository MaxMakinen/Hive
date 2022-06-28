#ifndef TOOLS_H
# define TOOLS_H
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

typedef struct s_data {
	int row, col;
	char **map1;
	char **map2;
}	t_data;

char 	**gameoflife(t_data *data);
void 	print_map(char **map);
char 	**init_map(int row, int col);

#endif