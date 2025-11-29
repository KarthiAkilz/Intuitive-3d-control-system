#include "WebSocketClientComponent.h"
#include "WebSocketsModule.h"
#include "Async/Async.h"

UWebSocketClientComponent::UWebSocketClientComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UWebSocketClientComponent::BeginPlay()
{
    Super::BeginPlay();
    FModuleManager::LoadModuleChecked<FWebSocketsModule>("WebSockets");
}

void UWebSocketClientComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Close();
    UnbindSocketDelegates();
    Super::EndPlay(EndPlayReason);
}

void UWebSocketClientComponent::Connect(const FString& Url)
{
    if (Socket.IsValid() && Socket->IsConnected())
    {
        Socket->Close();
        Socket.Reset();
    }

    Socket = FWebSocketsModule::Get().CreateWebSocket(Url);

    BindSocketDelegates();

    Socket->Connect();
}

void UWebSocketClientComponent::BindSocketDelegates()
{
    if (!Socket.IsValid()) return;

    TWeakObjectPtr<UWebSocketClientComponent> WeakThis(this);

    // OnConnected
    Socket->OnConnected().AddLambda([WeakThis]() {
        AsyncTask(ENamedThreads::GameThread, [WeakThis]() {
            if (UWebSocketClientComponent* Strong = WeakThis.Get())
            {
                Strong->HandleOnConnected();
            }
        });
    });

    // OnConnectionError
    Socket->OnConnectionError().AddLambda([WeakThis](const FString& Err) {
        AsyncTask(ENamedThreads::GameThread, [WeakThis, Err]() {
            if (UWebSocketClientComponent* Strong = WeakThis.Get())
            {
                Strong->HandleOnConnectError(Err);
            }
        });
    });

    // OnClosed
    Socket->OnClosed().AddLambda([WeakThis](int32 StatusCode, const FString& Reason, bool bWasClean) {
        AsyncTask(ENamedThreads::GameThread, [WeakThis, StatusCode, Reason, bWasClean]() {
            if (UWebSocketClientComponent* Strong = WeakThis.Get())
            {
                Strong->HandleOnClosed(StatusCode, Reason, bWasClean);
            }
        });
    });

    // OnMessage
    Socket->OnMessage().AddLambda([WeakThis](const FString& Msg) {
        AsyncTask(ENamedThreads::GameThread, [WeakThis, Msg]() {
            if (UWebSocketClientComponent* Strong = WeakThis.Get())
            {
                Strong->HandleOnMessage(Msg);
            }
        });
    });
}

void UWebSocketClientComponent::UnbindSocketDelegates()
{
    OnConnected.Clear();
    OnConnectionError.Clear();
    OnClosed.Clear();
    OnMessage.Clear();

    if (!Socket.IsValid()) return;
    Socket.Reset();
}

void UWebSocketClientComponent::HandleOnConnected()
{
    OnConnected.Broadcast();
}

void UWebSocketClientComponent::HandleOnConnectError(const FString& Error)
{
    OnConnectionError.Broadcast(Error);
}

void UWebSocketClientComponent::HandleOnClosed(int32 StatusCode, const FString& Reason, bool bWasClean)
{
    OnClosed.Broadcast(StatusCode);
}

void UWebSocketClientComponent::HandleOnMessage(const FString& Message)
{
    OnMessage.Broadcast(Message);
}

void UWebSocketClientComponent::SendText(const FString& Message)
{
    if (Socket.IsValid() && Socket->IsConnected())
    {
        Socket->Send(Message);
    }
}

void UWebSocketClientComponent::Close()
{
    if (Socket.IsValid())
    {
        if (Socket->IsConnected()) Socket->Close();
        Socket.Reset();
    }
}

bool UWebSocketClientComponent::IsConnected() const
{
    return Socket.IsValid() && Socket->IsConnected();
}
