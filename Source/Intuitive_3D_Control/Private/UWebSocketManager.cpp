#include "UWebSocketManager.h"
#include "WebSocketsModule.h"
#include "IWebSocket.h"
#include "Json.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UWebSocketManager::UWebSocketManager()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UWebSocketManager::BeginPlay()
{
	Super::BeginPlay();

	if (!FModuleManager::Get().IsModuleLoaded("WebSockets"))
	{
		FModuleManager::Get().LoadModule("WebSockets");
	}

	WebSocket = FWebSocketsModule::Get().CreateWebSocket(TEXT("ws://<YOUR_LOCAL_IP>:8081"));

	WebSocket->OnConnected().AddLambda([]()
		{
			UE_LOG(LogTemp, Warning, TEXT("Connected to WebSocket Server!"));
		});

	WebSocket->OnMessage().AddUObject(this, &UWebSocketManager::HandleWebSocketMessage);

	WebSocket->OnConnectionError().AddLambda([](const FString& Error)
		{
			UE_LOG(LogTemp, Error, TEXT("WebSocket Connection Error: %s"), *Error);
		});

	WebSocket->Connect();
}

void UWebSocketManager::HandleWebSocketMessage(const FString& Message)
{
	UE_LOG(LogTemp, Warning, TEXT("Message from HTML: %s"), *Message);

    OnMessageReceived.Broadcast(Message);

	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Message);

	if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
	{
		FString Type = JsonObject->GetStringField(TEXT("type"));

		if (Type == TEXT("left") || Type == TEXT("right"))
		{
			float X = JsonObject->GetNumberField(TEXT("x"));
			float Y = JsonObject->GetNumberField(TEXT("y"));

		}
		else if (Type == TEXT("button"))
		{
			FString ButtonId = JsonObject->GetStringField(TEXT("id"));
			bool Pressed = JsonObject->GetBoolField(TEXT("pressed"));

		}
	}
}

void UWebSocketManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (WebSocket && WebSocket->IsConnected())
		WebSocket->Close();

	Super::EndPlay(EndPlayReason);
}
