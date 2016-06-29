// Fill out your copyright notice in the Description page of Project Settings.

#include "Tetris_Ai.h"
#include "Tetris_Cell.h"


// Sets default values
ATetris_Cell::ATetris_Cell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = Scene;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->AttachTo(RootComponent);
}

void ATetris_Cell::SetMaterial(int state)
{
	if (state == -1)
	{
		Mesh->SetMaterial(0, Materials[0]);
	}
	else if (state == 0)
	{
		Mesh->SetMaterial(0, Materials[1]);
	}
	else if (state == 1)
	{
		Mesh->SetMaterial(0, Materials[2]);
	}
	else if (state == 2)
	{
		Mesh->SetMaterial(0, Materials[3]);
	}
	else if (state == 3)
	{
		Mesh->SetMaterial(0, Materials[4]);
	}
	else if (state == 4)
	{
		Mesh->SetMaterial(0, Materials[5]);
	}
	else if (state == 5)
	{
		Mesh->SetMaterial(0, Materials[6]);
	}
	else if (state == 6)
	{
		Mesh->SetMaterial(0, Materials[7]);
	}
	else if (state == 7)
	{
		Mesh->SetMaterial(0, Materials[8]);
	}
	else if (state == 8)
	{
		Mesh->SetMaterial(0, Materials[9]);
	}
}

void ATetris_Cell::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	SetMaterial(Value);
}
