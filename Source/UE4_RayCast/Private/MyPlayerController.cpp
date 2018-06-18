// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"

void AMyPlayerController::SingleRayCast()
{	
	UE_LOG(LogTemp, Warning, TEXT("S"))
	float distance = 1000.f;
	FVector start = PlayerCameraManager->GetCameraLocation();
	FVector direction = PlayerCameraManager->GetActorForwardVector();
	FVector end = start + (direction * distance);
	
	FHitResult outHitResult;

	UWorld* w = GetWorld();
	bool HasHitSomething = w->LineTraceSingleByChannel(outHitResult, start, end, ECollisionChannel::ECC_Visibility);


	if (HasHitSomething && outHitResult.Actor != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit %s"), *outHitResult.Actor->GetName())
		DrawDebugLine(w, start, outHitResult.ImpactPoint, FColor::MakeRandomColor(), true, 5.f, (uint8)0, 10.f);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Missed"))
		DrawDebugLine(w, start, end, FColor::MakeRandomColor(), true, 5.f, (uint8)0, 10.f);
	}
	
}

void AMyPlayerController::MultiRayCast()
{
	float distance = 1000.f;
	FVector start = PlayerCameraManager->GetCameraLocation();
	FVector direction = PlayerCameraManager->GetActorForwardVector();
	FVector end = start + (direction * distance);

	TArray<FHitResult> outHits;

	UWorld* w = GetWorld();
	bool HasHitSomething = w->LineTraceMultiByChannel(outHits, start, end, ECollisionChannel::ECC_Visibility);

	if (HasHitSomething)
	{
		for (FHitResult &elem : outHits)
		{
			FVector impact = elem.ImpactPoint;
			FColor color = FColor::MakeRandomColor();
			DrawDebugLine(w, start, impact, color, true, 10.f, (uint8)0, 10.f);

			ClientMessage(FString::Printf(TEXT("Hit %s"), *elem.GetActor()->GetName()), NAME_None, 10.f);
			UE_LOG(LogTemp, Warning, TEXT("Hit %s "), *elem.GetActor()->GetName())
		}
	}
	else
	{
		DrawDebugLine(w, start, end, FColor::MakeRandomColor(), true, 5.f, (uint8)0, 10.f);
	}


}

void  AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("SingleRay", EInputEvent::IE_Released, this, &AMyPlayerController::SingleRayCast);
	InputComponent->BindAction("MultiRay", EInputEvent::IE_Released, this, &AMyPlayerController::MultiRayCast);
}
