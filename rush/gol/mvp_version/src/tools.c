#include "gol.h"

static void	check_neighbours(t_data *data, int row, int col)
{
	int count = 0;
	int iRow = row - 1 * (row > 0); 
	int jCol = col - 1 * (col > 0);
	int endRow = row + 1 * (row < data->row - 1);
	int endCol = col + 1 * (col < data->col - 1);
	
	for (int i = iRow; i <= endRow; i++)
	{
		for (int j = jCol; j <= endCol; j++)
		{
			if (data->map1[i][j] == 'X')
			{
				count++;
			}	
		}
	}
	if (data->map1[row][col] == 'X' && (count == 3 || count == 4))
		data->map2[row][col] = 'X';
	else if (data->map1[row][col] == '.' && count == 3)
		data->map2[row][col] = 'X';
	data->steps++;
}

void	gameoflife(t_data *data)
{
	for (int row = 0; row < data->row; row++)
	{
		for (int col = 0; col < data->col; col++)
			check_neighbours(data, row, col);
	}
}