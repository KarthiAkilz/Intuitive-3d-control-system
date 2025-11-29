#include "AMandoChar.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Json.h"
#include "JsonUtilities.h"
#include "UWebSocketManager.h"

// Sets default values
AMandoChar::AMandoChar()
{
    PrimaryActorTick.bCanEverTick = true;

    WebSocketManager = CreateDefaultSubobject<UWebSocketManager>(TEXT("WebSocketManager"));
}

// Called when the game starts or when spawned
void AMandoChar::BeginPlay()
{
    Super::BeginPlay();

    if (WebSocketManager)
    {
        UE_LOG(LogTemp, Log, TEXT("✅ MandoChar: WebSocketManager attached and active"));

        // Bind WebSocket event to handle incoming messages
        WebSocketManager->OnMessageReceived.AddDynamic(this, &AMandoChar::HandleWebSocketMessage);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("❌ WebSocketManager not found!"));
    }
}

void AMandoChar::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    ApplyRemoteInput(DeltaTime);
}

void AMandoChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMandoChar::HandleWebSocketMessage(const FString& Message)
{
    TSharedPtr<FJsonObject> JsonObject;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Message);

    if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
    {
        FString Type = JsonObject->GetStringField(TEXT("type"));

        if (Type == TEXT("left"))
        {
            float X = JsonObject->GetNumberField(TEXT("x"));
            float Y = JsonObject->GetNumberField(TEXT("y"));
            MovementInput = FVector2D(X, Y);
            UE_LOG(LogTemp, Warning, TEXT("🕹️ Movement Input: X=%f, Y=%f"), X, Y);
        }
        else if (Type == TEXT("right"))
        {
            float X = JsonObject->GetNumberField(TEXT("x"));
            float Y = JsonObject->GetNumberField(TEXT("y"));
            LookInput = FVector2D(X, Y);
            UE_LOG(LogTemp, Warning, TEXT("🎯 Look Input: X=%f, Y=%f"), X, Y);
        }
        else if (Type == TEXT("button"))
        {
            FString ButtonID = JsonObject->GetStringField(TEXT("id"));
            bool Pressed = JsonObject->GetBoolField(TEXT("pressed"));

            if (Pressed)
            {
                if (ButtonID == TEXT("C")) { Jump(); }
                else if (ButtonID == TEXT("A"))
                {
                    UE_LOG(LogTemp, Warning, TEXT("🤜 Grab triggered via WebSocket"));
                    GrabEvent(); 
                }
                else if (ButtonID == TEXT("B"))
                {
                    UE_LOG(LogTemp, Warning, TEXT("🎯 Throw triggered via WebSocket"));
                    ThrowEvent(); 
                }
            }
        }
    }
}

void AMandoChar::ApplyRemoteInput(float DeltaTime)
{

	if (!Controller) return;

	const FRotator ControlRot = Controller->GetControlRotation();
	const FRotator YawRot(0, ControlRot.Yaw, 0);
	const FVector ForwardDir = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
	const FVector RightDir = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);

	const float MovementSensitivity = 3.0f;
	static FVector2D SmoothedMovement = FVector2D::ZeroVector;

    if (!MovementInput.IsNearlyZero())
    {
        SmoothedMovement = FMath::Lerp(SmoothedMovement, MovementInput, DeltaTime * 8.0f);
    }
    else
    {
		SmoothedMovement = FVector2D::ZeroVector;
    }


    if (!SmoothedMovement.IsNearlyZero())
    {
        AddMovementInput(ForwardDir, SmoothedMovement.Y);
        AddMovementInput(RightDir, SmoothedMovement.X);
	}

	const float CameraSensitivity = 2.0f;

	static FVector2D SmoothedLook = FVector2D::ZeroVector;

    if (!LookInput.IsNearlyZero())
    {
        SmoothedLook = FMath::Lerp(SmoothedLook, LookInput, DeltaTime * 1.0f);

    }
    else
    {
		SmoothedLook = FVector2D::ZeroVector;
    }

    // Apply look rotation (camera movement)
    if (!SmoothedLook.IsNearlyZero())
    {
        AddControllerYawInput(SmoothedLook.X * 0.8f * CameraSensitivity);     // horizontal rotation
        AddControllerPitchInput(SmoothedLook.Y * -0.8f * CameraSensitivity);  // vertical rotation (inverted for natural feel)
    }
}
