// Fill out your copyright notice in the Description page of Project Settings.

#include "Tetris_Ai.h"
#include "AI.h"
#include "Tetromineo.h"
#include "Grid.h"

AI::AI()
{
}

AI::AI(float _Height, float _Lines, float _Holes, float _Bumpiness)
{
	//setup all the heurstics when the class is created.
	Height = _Height;
	Lines = _Lines;
	Holes = _Holes;
	Bumpiness = _Bumpiness;
}

AI::~AI()
{

}

float AI::BestPlaceForCurrent(Grid _grid, Tetromineo _Current, Tetromineo _Preview)
{
	//initalises all the var needed to calculate the best piece.
	float BestScore = 0;
	int count = 0;
	//var for holding the preview and the current pieces
	Tetromineo _PreviewPiece = Tetromineo();
	_PreviewPiece = _Preview.CopyPiece();
	Tetromineo tempPiece = Tetromineo();
	tempPiece = _Current.CopyPiece();

	//for every rotation the current piece can move
	for (int r = 0; r < 4; r++)
	{
		//set the current piece's x = 0
		tempPiece.x = 0;

		//if r = 0 don't but if r > 0 rotate the piece by one
		if (r != 0)
		{
			tempPiece.Rotate(1);
		}

		//while the current piece can moveleft on the grid
		while (_grid.canMoveLeft(tempPiece))
		{
			//move left on the grid
			tempPiece.x--;
		}

		//while true
		while (true)
		{
			//reset the current piece's y to 0 
			tempPiece.y = 0;

			//make a copy of the current piece so we change the currentpiece
			Tetromineo XtempPiece = Tetromineo();
			XtempPiece = tempPiece.CopyPiece();

			//while the currentpiece copy can move down
			while (_grid.canMoveDown(XtempPiece))
			{
				//while the currentpiece copy move down
				XtempPiece.y++;
			}

			//make a copy of the grid that is in play
			Grid _Grid = _grid.CopyGrid();
			//add the currentpiece copy to the copy of the board
			_Grid.AddPrementPiece(XtempPiece.CopyPiece());

			//var for the score
			float Score = 0;

			//calculate the score by calling the bestplaceforpreview
			Score = BestPlaceForPreview(_Grid, _PreviewPiece.CopyPiece());

			//if the returned score from the BesPlaceForPreview to greater than the best score
			//set best score equal to score and set best piece equal to the piece that was just checked
			if (Score > BestScore || BestScore == 0)
			{
				BestScore = Score;
				BestPiece = tempPiece.CopyPiece();
			}

			//while the currentpiece can move right, move it right by 1
			if (_grid.canMoveRight(tempPiece))
			{
				tempPiece.x++;
			}
			else
			{
				break;
			}
		}
	}

	return BestScore;
}

//This does the excaulty the same thing as the BestPlaceforCurrent expect it does not 
//set the best piece, and just returns the bestscore
//it also calculates the score from the heuristics and the Grid calculations
float AI::BestPlaceForPreview(Grid _grid, Tetromineo _Pieces)
{
	float BestScore = 0;
	Tetromineo PreviewtempPiece = Tetromineo();
	PreviewtempPiece = _Pieces.CopyPiece();

	for (int r = 0; r < 4; r++)
	{

		PreviewtempPiece.x = 0;

		if (r != 0)
		{
			PreviewtempPiece.Rotate(1);
		}

		while (_grid.canMoveLeft(PreviewtempPiece))
		{
			PreviewtempPiece.x--;
		}

		while (true)
		{

			PreviewtempPiece.y = 0;

			Tetromineo XtempPiece = Tetromineo();
			XtempPiece = PreviewtempPiece.CopyPiece();

			while (_grid.canMoveDown(XtempPiece))
			{
				XtempPiece.y++;
			}

			Grid _Grid = _grid.CopyGrid();
			_Grid.AddPrementPiece(XtempPiece.CopyPiece());

			float Score = 0;

			Score = (-Height * _Grid.gridAvergeHeight()) + (Lines * _Grid.gridCompletedLines()) - (Holes * _Grid.gridHoles()) - (Bumpiness * _Grid.gridBump());

			if (Score > BestScore || BestScore == 0)
			{
				BestScore = Score;
			}

			if (_grid.canMoveRight(PreviewtempPiece))
			{
				PreviewtempPiece.x++;
			}
			else
			{
				break;
			}
		}
	}

	return BestScore;
}

Tetromineo AI::returnPiece()
{
	return BestPiece.CopyPiece();
}