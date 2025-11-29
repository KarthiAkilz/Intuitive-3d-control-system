        #pragma once

        #include "CoreMinimal.h"
        #include "Components/ActorComponent.h"
        #include "WebSocketsModule.h"
        #include "IWebSocket.h"
        #include "WebSocketClientComponent.generated.h"

        DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWSConnected);
        DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWSConnectionError, const FString&, Error);
        DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWSClosed, int32, StatusCode);
        DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWSMessageReceived, const FString&, Message);

        UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
        class INTUITIVE_3D_CONTROL_API UWebSocketClientComponent : public UActorComponent
        {
            GENERATED_BODY()

        public:
            UWebSocketClientComponent();

            // Blueprint callable actions
            UFUNCTION(BlueprintCallable, Category="WebSocket")
            void Connect(const FString& Url);

            UFUNCTION(BlueprintCallable, Category="WebSocket")
            void SendText(const FString& Message);

            UFUNCTION(BlueprintCallable, Category="WebSocket")
            void Close();

            UFUNCTION(BlueprintCallable, Category="WebSocket")
            bool IsConnected() const;

            // Blueprint events
            UPROPERTY(BlueprintAssignable, Category="WebSocket")
            FWSConnected OnConnected;

            UPROPERTY(BlueprintAssignable, Category="WebSocket")
            FWSConnectionError OnConnectionError;

            UPROPERTY(BlueprintAssignable, Category="WebSocket")
            FWSClosed OnClosed;

            UPROPERTY(BlueprintAssignable, Category="WebSocket")
            FWSMessageReceived OnMessage;

        protected:
            virtual void BeginPlay() override;
            virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

        private:
            TSharedPtr<IWebSocket> Socket;

            void BindSocketDelegates();
            void UnbindSocketDelegates();

            void HandleOnConnected();
            void HandleOnConnectError(const FString& Error);
            void HandleOnClosed(int32 StatusCode, const FString& Reason, bool bWasClean);
            void HandleOnMessage(const FString& Message);
        };
