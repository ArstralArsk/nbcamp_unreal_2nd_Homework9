#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NumberBaseballLibrary.h"
#include "NumberBaseballGameModeBase.generated.h"

UENUM(BlueprintType)
enum class EPlayerType : uint8
{
    Host,
    Guest
};

UCLASS()
class SAMPLECHAT_API ANumberBaseballGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
    ANumberBaseballGameModeBase();

    UFUNCTION(BlueprintCallable, Category = "Number Baseball")
    void OnChatCommand(EPlayerType PlayerType, const FString& Command);


protected:
    virtual void BeginPlay() override;

private:
    FString CurrentAnswer;

    int32 HostTries;
    int32 GuestTries;

    bool bHostOut;
    bool bGuestOut;

    bool bHostWin;
    bool bGuestWin;

    void ResetGame();
    void CheckGameResult();

    void PrintMessageToScreen(const FString& Msg);
};
