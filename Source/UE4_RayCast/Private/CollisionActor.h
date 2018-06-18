// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CollisionActor.generated.h"

UCLASS()
class ACollisionActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollisionActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = "My Collision Actor")
	class USphereComponent* Sphere;

	UPROPERTY(EditAnywhere, Category = "My Collision Actor")
		class UPhysicalMaterial * PhysicalMaterial;

	UPROPERTY(EditAnywhere, Category = "My Collision Actor")
		TEnumAsByte<ECollisionResponse> CameraChannelCollisionResponse = ECollisionResponse::ECR_Block;
};
