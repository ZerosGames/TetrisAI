// Fill out your copyright notice in the Description page of Project Settings.

#include "Tetris_Ai.h"
#include "Tetromineo.h"

Tetromineo::Tetromineo()
{
	x = 0;
	y = 0;
}

Tetromineo::~Tetromineo()
{
}

Tetromineo Tetromineo::RandomTetrominoe(int _index)
{
	Tetromineo piece;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			piece.Shape[i][j] = -1;
		}
	}

	switch (_index)
	{
		case 0: //Tower!
			{
				piece.Shape[1][0] = 2;
				piece.Shape[1][1] = 2;
				piece.Shape[1][2] = 2;
				piece.Shape[1][3] = 2;
				piece.y = 0;
				break;
			}
		case 1: //Box!
			{
				piece.Shape[1][1] = 3;
				piece.Shape[1][2] = 3;
				piece.Shape[2][1] = 3;
				piece.Shape[2][2] = 3;
				break;
			}
		case 2: //Pyramid!
			{
				piece.Shape[0][1] = 4;
				piece.Shape[1][0] = 4;
				piece.Shape[1][1] = 4;
				piece.Shape[1][2] = 4;
				break;
			}
		case 3://Left Leaner
			{
				piece.Shape[0][1] = 5;
				piece.Shape[1][1] = 5;
				piece.Shape[1][2] = 5;
				piece.Shape[2][2] = 5;
				break;
			}
		case 4://Right Leaner
			{
				piece.Shape[2][1] = 6;
				piece.Shape[1][1] = 6;
				piece.Shape[1][2] = 6;
				piece.Shape[0][2] = 6;
				break;
			}
		case 5://Left Knight
			{
				piece.Shape[1][1] = 7;
				piece.Shape[2][1] = 7;
				piece.Shape[2][2] = 7;
				piece.Shape[2][3] = 7;
				break;
			}
		case 6://Right Knight
			{
				piece.Shape[2][1] = 8;
				piece.Shape[1][1] = 8;
				piece.Shape[1][2] = 8;
				piece.Shape[1][3] = 8;
				break;
			}
	}

	return piece;
}

void Tetromineo::Rotate(int _rotations)
{
	Tetromineo temp = Tetromineo();

	for (int _x = 0; _x < _rotations; _x++)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				temp.Shape[3 - j][i] = Shape[i][j];
			}
		}

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				Shape[i][j] = temp.Shape[i][j];
			}
		}
	}
}

Tetromineo Tetromineo::CopyPiece()
{
	Tetromineo temp = Tetromineo();

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			temp.Shape[i][j] = Shape[i][j];
		}
	}

	temp.x = x;
	temp.y = y;

	return temp;
}
