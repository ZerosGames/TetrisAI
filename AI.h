// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Tetromineo.h"
#include "Grid.h"

/**
 * 
 */
class TETRIS_AI_API AI
{
public:
	//constructor and destructor for the AI class.
	AI();
	AI(float Height, float Lines, float Holes, float Bumpiness);
	~AI();

	//retrns the best score of the current piece and sets BestPiece var to the best piece.
	float BestPlaceForCurrent(Grid _grid, Tetromineo _CurrentPiece, Tetromineo _PreviewPieces);

	//return the best score for the preview piece and sends it to the BestPlaceForCurrent.
	float BestPlaceForPreview(Grid _grid, Tetromineo _Pieces);

	//returns the the bestpiece to the Tetris class;
	Tetromineo returnPiece();

	//variable for holding the bestpiece
	Tetromineo BestPiece;

	//variable for holding the height heuristic.
	float Height;
	//variable for holding the Lines heuristic.
	float Lines;
	//variable for holding the Holes heuristic.
	float Holes;
	//variable for holding the Bumpiness heuristic.
	float Bumpiness;
};
