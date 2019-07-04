// Fill out your copyright notice in the Description page of Project Settings.


#include "JLRPGCharacter.h"
#include"Components/CapsuleComponent.h"
#include"GameFramework/CharacterMovementComponent.h"
#include"GameFramework/SpringArmComponent.h"
#include"Camera/CameraComponent.h"
// Sets default values
AJLRPGCharacter::AJLRPGCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	BaseTurnRate = 45.0f;
	BaseLookUpRate = 45.0f;

	
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	bUseControllerRotationPitch = false;//¸©Ñö
	bUseControllerRotationRoll = false;//·­¹ö
	bUseControllerRotationYaw = false;//Æ«º½

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f,540.0f,0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->AirControl = 0.2f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
	FollowCamera->bUsePawnControlRotation = false;







}

// Called when the game starts or when spawned
void AJLRPGCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJLRPGCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AJLRPGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

