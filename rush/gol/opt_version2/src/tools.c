#include "gol.h"

void	check_neighbours(t_data *data, int row, int col)
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
			if (data->map1[i][j] & 1)
				count++;
		}
	}
	if (data->map1[row][col] & 1 && (count == 3 || count == 4))
	{
		data->map2[row][col] |= 1;
	}	
	else if (!(data->map1[row][col] & 1) && count == 3)
	{
		data->map2[row][col] |= 1;
	}
	data->map1[row][col] |= 2;
}

void check_first_neighbours(t_data *data, int row, int col)
{
	int iRow = row - 1 * (row > 0); 
	int jCol = col - 1 * (col > 0);
	int endRow = row + 1 * (row < data->row - 1);
	int endCol = col + 1 * (col < data->col - 1);
	
	for (int i = iRow; i <= endRow; i++)
	{
		for (int j = jCol; j <= endCol; j++)
		{
			if ((data->map1[i][j] & 2) != 2)
				check_neighbours(data, i, j);
		}
	}
}

void	gameoflife(t_data *data)
{
	for (int row = 0; row < data->row; row++)
	{
		for (int col = 0; col < data->col; col++)
		{
			if ((data->map1[row][col] & 1) == 1)
				check_first_neighbours(data, row, col);
		}
	}
}

