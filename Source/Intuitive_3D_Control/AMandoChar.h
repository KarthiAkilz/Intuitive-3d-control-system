#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UWebSocketManager.h"
#include "AMandoChar.generated.h"

class UWebSocketManager;

UCLASS()
class INTUITIVE_3D_CONTROL_API AMandoChar : public ACharacter
{
    GENERATED_BODY()

public:
    AMandoChar();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

    UFUNCTION()
    void HandleWebSocketMessage(const FString& Message);

private:
    // Movement & Look input vectors coming from HTML joystick
    FVector2D MovementInput;
    FVector2D LookInput;

    void ApplyRemoteInput(float DeltaTime);

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "WebSocket")
    UWebSocketManager* WebSocketManager;

    UFUNCTION(BlueprintImplementableEvent, Category = "WebSocket")
    void GrabEvent();

    UFUNCTION(BlueprintImplementableEvent, Category = "WebSocket")
    void ThrowEvent();
};
