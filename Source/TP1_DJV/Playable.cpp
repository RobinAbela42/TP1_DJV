// Fill out your copyright notice in the Description page of Project Settings.


#include "Playable.h"
#include "Components/BoxComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/CapsuleComponent.h"

// Sets default values
APlayable::APlayable()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create BoxComponent and set as RootComponent for the Actor
	BoxCollision = CreateDefaultSubobject<UCapsuleComponent>("BoxCollision");
	RootComponent = BoxCollision;

	// Create StaticMeshComponent and Attach to BoxComponent
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(BoxCollision);

	
	

}

// Called when the game starts or when spawned
void APlayable::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayable::Move(const FInputActionValue& Value)
{
	// Console Log
	UE_LOG(LogTemp, Warning, TEXT("Moving"));

	
	FVector2D Direction = Value.Get<FVector2D>();
	
	if (Direction.X)
	{
		FVector NormalizedDirection = FVector(Direction.X, Direction.Y, 0.0f).GetSafeNormal();

		AddMovementInput(NormalizedDirection);
	}
}

// Called every frame
void APlayable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayable::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (APlayerController* PlayerController = GetController<APlayerController>())
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Ajouter le Input Mapping Context
			InputSubsystem->AddMappingContext(InputMapping, 0);
		}
	}

	if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayable::Move);
	}

}	

