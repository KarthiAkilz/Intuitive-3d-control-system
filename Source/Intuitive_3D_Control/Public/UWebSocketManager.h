#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "IWebSocket.h"
#include "UWebSocketManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWebSocketMessageReceived, const FString&, Message);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class INTUITIVE_3D_CONTROL_API UWebSocketManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UWebSocketManager();

protected:
	virtual void BeginPlay() override;

public:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(BlueprintAssignable, Category = "WebSocket")
	FOnWebSocketMessageReceived OnMessageReceived;

private:
	TSharedPtr<IWebSocket> WebSocket;

	void HandleWebSocketMessage(const FString& Message);
};