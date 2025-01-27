// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "JLRPGCharacter.generated.h"

UCLASS()
class UE4RPG_API AJLRPGCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AJLRPGCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//X轴旋转镜头速率
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera|Rate")
	float BaseTurnRate;
	//Y轴旋转镜头速率
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera|Rate")
	float BaseLookUpRate;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;



	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Mono = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Coins = 0;

	UFUNCTION(BlueprintCallable)
	void SetHealth(float Value);

	UFUNCTION(BlueprintCallable)
	void AddHealth(float Value);
	UFUNCTION(BlueprintCallable)
	void OpenMyBag();




protected:

	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void OnResetVR();
	void MoveForward(float Value);
	void MoveRight(float Value);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);
	void TouchStoped(ETouchIndex::Type FingerIndex,FVector Location);
	


	

};
