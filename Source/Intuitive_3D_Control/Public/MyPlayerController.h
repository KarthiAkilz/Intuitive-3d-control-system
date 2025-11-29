// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

UCLASS()
class INTUITIVE_3D_CONTROL_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

    public:
        virtual void BeginPlay() override;
        virtual void Tick(float DeltaTime) override;
        virtual void SetupInputComponent() override;
        virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

        UFUNCTION(BlueprintCallable)
        void OnHTMLMessage(const FString& Message);
   

	
};
