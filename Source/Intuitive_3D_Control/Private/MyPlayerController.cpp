// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

#include "Engine/Engine.h"
#include "Misc/OutputDeviceDebug.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

void AMyPlayerController::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("PlayerController Initialized"));
}

void AMyPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    // Your per-frame logic here (optional)
}

void AMyPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    // Bind inputs here if needed
}

void AMyPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
    // Cleanup logic here (optional)
}


void AMyPlayerController::OnHTMLMessage(const FString& Message)
{
    UE_LOG(LogTemp, Warning, TEXT("Received Message: %s"), *Message);
}
