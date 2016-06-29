// Fill out your copyright notice in the Description page of Project Settings.

#include "Tetris_Ai.h"
#include "Tetris.h"
#include "Tetris_Cell.h"
#include "Grid.h"
#include "Tetromineo.h"
#include "AI.h"


// Sets default values
ATetris::ATetris()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SudoDeltaTime = 0;
}

// Called when the game starts or when spawned
void ATetris::BeginPlay()
{
	Super::BeginPlay();

	Tetris_AI = AI(0.5f,0.8f,0.4f,0.6f);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = Instigator;

	FRotator CellRotation(-90, 180, 90);

	//start out the map
	for (int x = 0; x < GridSizeX; x++)
	{
		for (int y = 0; y < GridSizeY + 1; y++)
		{
			FVector startPos(x * CellRadius * 2 - (GridWorldX / 2), 100, -y * CellRadius * 2 + (GridWorldY / 2));
			ATetris_Cell* Cell = GetWorld()->SpawnActor<ATetris_Cell>(Tetris_Cell, startPos, CellRotation, SpawnParams);
			TetrisBoard[x][y] = Cell;

			if (y == GridSizeY)
			{
				Tetris_Board._grid[x][y] = 1;
				TetrisBoard[x][y]->Value = 1;
			}
			else
			{
				Tetris_Board._grid[x][y] = 0;
				TetrisBoard[x][y]->Value = 0;
			}
		}
	}

	for (int _x = 0; _x < 4; _x++)
	{
		for (int _y = 0; _y < 4; _y++)
		{
			FVector startPos((_x * CellRadius * 2 - ((32 * 4) / 2)) - 300, 100, (-_y * CellRadius * 2 + ((32 * 4) / 2)) + 300);
			ATetris_Cell* Cell = GetWorld()->SpawnActor<ATetris_Cell>(Tetris_Cell, startPos, CellRotation, SpawnParams);
			NextShape[_x][_y] = Cell;
			NextShape[_x][_y]->Value = -1;
		}
	}

	CreatePiece();
}

// Called every frame
void ATetris::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if ((GetTickCount() - SudoDeltaTime) > 100)
	{
		if (Tetris_Board.canMoveDown(CurrentPiece))
		{
			CurrentPiece.y++;
		}
		else
		{
			if (CurrentPiece.y < 1)
			{

			}
			else
			{
				bool killblock = false;
				int i, j;
				//new block time! add this one to the list!

				Tetris_Board.AddPrementPiece(CurrentPiece.CopyPiece());

				//check for cleared row!
				for (j = 0; j < GridSizeY; j++)
				{
					bool filled = true;
					for (i = 0; i < GridSizeX; i++)
						if (Tetris_Board._grid[i][j] == 0)
							filled = false;

					if (filled)
					{
						RemoveRow(j);
						killblock = true;
					}
				}

				if (killblock)
				{
					for (i = 0; i < 4; i++)
						for (j = 0; j < 4; j++)
							CurrentPiece.Shape[i][j] = -1;
				}
				CreatePiece();				
			}
		}

		DrawBoard();
		SudoDeltaTime = GetTickCount();
	}
}

void ATetris::CreatePiece()
{
	int Rand = 0;

	if (GameStarted == false)
	{
		GameStarted = true;

		Rand = FMath::RandRange(0, 6);
		CurrentPiece = Tetromineo().RandomTetrominoe(Rand);
		CurrentPiece.x = 0;
		CurrentPiece.y = 0;
		if (Rand == 0)
		{
			CurrentPiece.y = 0;
		}
	}
	else
	{
		CurrentPiece = PreviewPiece.CopyPiece();
		CurrentPiece.x = 0;
		CurrentPiece.y = 0;
	}

	Rand = FMath::RandRange(0, 6);
	PreviewPiece = Tetromineo().RandomTetrominoe(Rand);
	PreviewPiece.x = 0;
	PreviewPiece.y = 0;

	if (Tetris_AI.BestPlaceForCurrent(Tetris_Board.CopyGrid(), CurrentPiece.CopyPiece(), PreviewPiece.CopyPiece()) != 0)
	{
		int LastY = CurrentPiece.y;
		CurrentPiece = Tetris_AI.returnPiece();
		CurrentPiece.y = LastY;
	}

	DrawBoard();
}

void ATetris::DrawBoard()
{

	for (int xmy = 0; xmy < 4; xmy++)
	{
		for (int ymx = 0; ymx < 4; ymx++)
		{
			NextShape[xmy][ymx]->Value = PreviewPiece.Shape[xmy][ymx];
		}
	}

	for (int _x = 0; _x < GridSizeX; _x++)
	{
		for (int _y = 0; _y < GridSizeY; _y++)
		{
			TetrisBoard[_x][_y]->Value = Tetris_Board._grid[_x][_y];
		}
	}

	for (int xmy = 0; xmy < 4; xmy++)
	{
		for (int ymx = 0; ymx < 4; ymx++)
		{
			if (CurrentPiece.Shape[xmy][ymx] != -1)
			{
				TetrisBoard[CurrentPiece.x + xmy][CurrentPiece.y + ymx]->Value = CurrentPiece.Shape[xmy][ymx];
			}
		}
	}
}

void ATetris::RemoveRow(int _Row)
{
	int x, y;

	for (x = 0; x < GridSizeX; x++)
	{
		for (y = _Row; y > 0; y--)
		{
			Tetris_Board._grid[x][y] = Tetris_Board._grid[x][y - 1];
		}
	}
}