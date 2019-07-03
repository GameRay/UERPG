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

	//X����ת��ͷ����
	UPROPERTY(VisiableAnywhere, BluerintReadOnly, Category = "Camera|Rate")
	float BaseTurnRate;
	//Y����ת��ͷ����
	UPROPERTY(VisiableAnywhere, BlueprintReadOnly, Category = "Camera|Rate")
	float BaseLookUpRate;

};
