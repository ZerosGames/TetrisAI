// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


class TETRIS_AI_API Tetromineo
{
public:
	Tetromineo();
	~Tetromineo();

	int Shape[4][4];
	int x;
	int y;

	Tetromineo RandomTetrominoe(int _index);
	Tetromineo CopyPiece();

	void Rotate(int _rotations);
};
