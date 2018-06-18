// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionActor.h"
#include "Components/SphereComponent.h"


// Sets default values
ACollisionActor::ACollisionActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(FName("Collistion Sphere"));
	SetRootComponent(Sphere);

	Sphere->SetSphereRadius(32.f);
	Sphere->bHiddenInGame = false;
	Sphere->SetVisibility(true);

	Sphere->SetSimulatePhysics(true);
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//Sphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	Sphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Block);
	Sphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);



}

// Called when the game starts or when spawned
void ACollisionActor::BeginPlay()
{
	Super::BeginPlay();

	if (PhysicalMaterial)
	{
		Sphere->BodyInstance.SetPhysMaterialOverride(PhysicalMaterial);
	}

	Sphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, CameraChannelCollisionResponse);
}

// Called every frame
void ACollisionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

