// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Tetromineo.h"

/**
 * 
 */
class TETRIS_AI_API Grid
{
public:

	Grid();
	~Grid();

	const int gridHeight = 30;
	const int gridWidth = 10;
	int _grid[10][31];
	

	Grid CopyGrid();

	bool canMoveDown(Tetromineo _piece);
	bool canMoveRight(Tetromineo _piece);
	bool canMoveLeft(Tetromineo _piece);

	float gridBump();
	float gridAvergeHeight();
	float gridHoles();
	float gridCompletedLines();
	float ColumnHeight(int _column);

	void AddPrementPiece(Tetromineo _piece);
};
