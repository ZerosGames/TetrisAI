// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Tetris_Cell.generated.h"

UCLASS()
class TETRIS_AI_API ATetris_Cell : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATetris_Cell();

	// Called when the game starts or when spawned
	int Value;

	void SetMaterial(int);

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere)
	TArray<UMaterialInterface*> Materials;


protected:

	UPROPERTY(Category = Scene, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAcess = "true"))
	class USceneComponent * Scene;

	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAcess = "true"))
	class UStaticMeshComponent* Mesh;

};
