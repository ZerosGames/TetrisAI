// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Tetris_Cell.h"
#include "Grid.h"
#include "Tetromineo.h"
#include "AI.h"
#include "Tetris.generated.h"

UCLASS()
class TETRIS_AI_API ATetris : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATetris();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void CreatePiece();
	void DrawBoard();
	void RemoveRow(int _Row);

	UPROPERTY(EditDefaultsOnly, Category = PuzzleCell)
	TSubclassOf<class ATetris_Cell> Tetris_Cell;
	
	ATetris_Cell* TetrisBoard[10][31];
	ATetris_Cell* NextShape[4][4];

	Grid Tetris_Board = Grid();
	AI Tetris_AI;

	Tetromineo CurrentPiece;
	Tetromineo PreviewPiece;

	const int GridSizeX = 10;
	const int GridSizeY = 30;
	const int CellRadius = 16;
	const int GridWorldX = 320;
	const int GridWorldY = 960;
	int SudoDeltaTime;
	bool GameStarted;
};
