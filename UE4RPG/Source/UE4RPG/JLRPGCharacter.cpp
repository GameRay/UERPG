// Fill out your copyright notice in the Description page of Project Settings.


#include "JLRPGCharacter.h"
#include"Components/CapsuleComponent.h"
#include"GameFramework/CharacterMovementComponent.h"
#include"GameFramework/SpringArmComponent.h"
#include"Camera/CameraComponent.h"
#include"Components/InputComponent.h"
#include"HeadMountedDisplayFunctionLibrary.h"
#include"GameFramework/Controller.h"
#include"Components/SkeletalMeshComponent.h"
#include"Runtime/UMG/Public/Blueprint/UserWidget.h"
#include"SlateCore/Public/Styling/SlateBrush.h"
#include"UMG/Public/Components/Image.h"
#include"Classes/Kismet/GameplayStatics.h"
//#include"D:\Program Files\Epic Games\UE_4.22\Engine\Source\Runtime\UMG\Public\Components\Image.h"
// Sets default values
AJLRPGCharacter::AJLRPGCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//Super::ACharacter();
	PrimaryActorTick.bCanEverTick = true;

	UObject *SKMeshObj=LoadObject<UObject>(NULL,TEXT("/Game/Mesh/Character/Eve/Eve_by_J__Gonzales.Eve_by_J__Gonzales"));
	USkeletalMesh* SKMesh = Cast<USkeletalMesh>(SKMeshObj);
	
	
	
	GetMesh()->SetSkeletalMesh(SKMesh);
	BaseTurnRate = 45.0f;
	BaseLookUpRate = 45.0f;

	
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	bUseControllerRotationPitch = false;//俯仰
	bUseControllerRotationRoll = false;//翻滚
	bUseControllerRotationYaw = false;//偏航

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
	//


	/*UUserWidget*UserWidge = nullptr;
	TSubclassOf<UUserWidget> WidgetClas = LoadClass<UUserWidget>(this, TEXT("/Game/ThirdPersonCPP/Blueprints/RPGHUD.RPGHUD_C"));


	
	if (WidgetClas)
	{
		UserWidge = CreateWidget<UUserWidget>(GetWorld(),WidgetClas);
		UserWidge->AddToViewport();
		UWidget* pro=UserWidge->GetWidgetFromName(FName("Image_75"));
		if (pro)
		{
			UImage*Image = Cast<UImage>(pro);
			
			UE_LOG(LogTemp, Warning, TEXT("SlotName:--%s"),*(Image->Brush.GetResourceName().ToString()));
		}
		
	}*/
}

// Called every frame
void AJLRPGCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AJLRPGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent)
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this,&ACharacter::Jump);;
	PlayerInputComponent->BindAction("Jump",EInputEvent::IE_Released,this,&ACharacter::StopJumping);
	PlayerInputComponent->BindAction("ResetVR",EInputEvent::IE_Pressed,this,&AJLRPGCharacter::OnResetVR);
	PlayerInputComponent->BindAction("InputOpenBag",EInputEvent::IE_Pressed,this,&AJLRPGCharacter::OpenMyBag);


	PlayerInputComponent->BindAxis("MoveForward",this,&AJLRPGCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AJLRPGCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this,&AJLRPGCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AJLRPGCharacter::LookUpAtRate);

	PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed,this,&AJLRPGCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(EInputEvent::IE_Released, this, &AJLRPGCharacter::TouchStoped);


}

void AJLRPGCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AJLRPGCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}
void AJLRPGCharacter::TouchStoped(ETouchIndex::Type FingerIndex,FVector Location)
{
	StopJumping();
}

void AJLRPGCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate*BaseTurnRate*GetWorld()->GetDeltaSeconds());
}

void AJLRPGCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate*BaseLookUpRate*GetWorld()->GetDeltaSeconds());
}

void AJLRPGCharacter::MoveForward(float Value)
{
	if ((Controller!=NULL)&&(Value!=0.0f))
	{
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0,Rotation.Yaw,0);
		//获取此时的正前方 X
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(Direction,Value);
	}
}

void AJLRPGCharacter::MoveRight(float Value)
{
	if ((Controller!=NULL)&&(Value!=0))
	{
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0,Rotation.Yaw,0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);


		AddMovementInput(Direction,Value);
	}
}

void AJLRPGCharacter::SetHealth(float Value)
{
	if (Value>=0)
	{
		Health = Value;
	}
	
}
void AJLRPGCharacter::AddHealth(float Value)
{
	(Health = (Health + Value)) < 0 ? 0 : Health;
	(Health > 1) ? Health : 1;
}
void AJLRPGCharacter::OpenMyBag()
{
	TSubclassOf<UUserWidget> BagWidget = LoadClass<UUserWidget>(this, TEXT("/Game/Blueprint/Inventory.Inventory_C"));
	if (BagWidget)
	{
		CreateWidget<UUserWidget>(GetWorld(),BagWidget)->AddToViewport();
		UGameplayStatics::GetPlayerController(GetWorld(),0)->bShowMouseCursor=1;
	}
}