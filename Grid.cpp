// Fill out your copyright notice in the Description page of Project Settings.

#include "Tetris_Ai.h"
#include "Grid.h"

Grid::Grid()
{
	for (int x = 0; x < gridWidth; x++)
	{
		for (int y = 0; y < gridHeight + 1; y++)
		{
			if (y == gridHeight)
			{
				_grid[x][y] = 1;
			}
			else
			{
				_grid[x][y] = 0;
			}
		}
	}
}

Grid::~Grid()
{
	
}

Grid Grid::CopyGrid()
{
	Grid _temp;

	for (int x = 0; x < gridWidth; x++)
	{
		for (int y = 0; y < gridHeight + 1; y++)
		{
			_temp._grid[x][y] = _grid[x][y];
		}
	}

	return _temp;
}

bool Grid::canMoveDown(Tetromineo _piece)
{
	int newy = _piece.y + 1;
	int newx = _piece.x;

	int i;
	int k;

	for (i = 0; i < 4; i++)
	{
		for (k = 0; k < 4; k++)
		{
			if (_piece.Shape[i][k] != -1)
			{
				if ( newy + k < 0 || newy + k > gridHeight - 1)
				{
					return false;
				}
			}
		}
	}

	for (int x = 0; x < gridWidth; x++)
	{
		for (int y = 0; y < gridHeight; y++)
		{
			if (x >= newx && x < newx + 4)
			{
				if (y >= newy && y < newy + 4)
				{
					if (_grid[x][y] != 0)
					{
						if (_piece.Shape[x - newx][y - newy] != -1)
						{
							return false;
						}
					}
				}
			}
		}
	}

	return true;
}

bool Grid::canMoveRight(Tetromineo _piece)
{
	int newx = _piece.x + 1;
	int newy = _piece.y;

	int i;
	int k;

	for (i = 0; i < 4; i++)
	{
		for (k = 0; k < 4; k++)
		{
			if (_piece.Shape[i][k] != -1)
			{
				if (newx + i > gridWidth - 1)
				{
					return false;
				}
			}
		}
	}

	for (int x = 0; x < gridWidth; x++)
	{
		for (int y = 0; y < gridHeight; y++)
		{
			if (x >= newx && x < newx + 4)
			{
				if (y >= newy && y < newy + 4)
				{
					if (_grid[x][y] != 0)
					{
						if (_piece.Shape[x - newx][y - newy] != -1)
						{
							return false;
						}
					}
				}
			}
		}
	}

	return true;
}

bool Grid::canMoveLeft(Tetromineo _piece)
{
	int newx = _piece.x - 1;
	int newy = _piece.y;

	int i;
	int k;

	for (i = 0; i < 4; i++)
	{
		for (k = 0; k < 4; k++)
		{
			if (_piece.Shape[i][k] != -1)
			{
				if (newx + i < 0)
				{
					return false;
				}
			}
		}
	}

	for (int x = 0; x < gridWidth; x++)
	{
		for (int y = 0; y < gridHeight; y++)
		{
			if (x >= newx && x < newx + 4)
			{
				if (y >= newy && y < newy + 4)
				{
					if (_grid[x][y] != 0)
					{
						if (_piece.Shape[x - newx][y- newy] != -1)
						{
							return false;
						}
					}
				}
			}
		}
	}

	return true;
}

float Grid::ColumnHeight(int _column)
{
	int i = 0;

	for (i = 0; i < 30; i++)
	{
		if (_grid[i][_column] != 0)
		{
			return 30 - i;
		}
	}

	return 0;
}

float Grid::gridBump()
{
	int total = 0;

	for (int c = 0; c < 10-1; c++)
	{
		total += FMath::Abs(ColumnHeight(c) - ColumnHeight(c + 1));
	}

	return total;
}

float Grid::gridAvergeHeight()
{
	int count = 0;

	for (int j = 0; j < 10; j++)
	{
		count += ColumnHeight(j);
	}

	return count;
}

float Grid::gridHoles()
{
	int count = 0;

	for (int i = 0; i < 10; i++)
	{
		for (int j = 1; j < 30; j++)
		{
			if (_grid[i][j] == 0)
			{
				if (_grid[i][j - 1] != 0)
				{
					count += 1;
				}
			}
		}
	}

	return count;
}

float Grid::gridCompletedLines()
{
	int count = 0;

	for (int j = 0; j < 30; j++)
	{
		count += 1;

		for (int i = 0; i < 10; i++)
		{
			if (_grid[i][j] == 0)
			{
				count -= 1;
				break;
			}
		}
	}
	return count;
}

void Grid::AddPrementPiece(Tetromineo _piece)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (_piece.Shape[i][j] != -1)
			{
				_grid[_piece.x + i][_piece.y + j] = _piece.Shape[i][j];
			}
		}
	}
}