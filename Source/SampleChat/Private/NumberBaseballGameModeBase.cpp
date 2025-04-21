#include "NumberBaseballGameModeBase.h"
#include "Kismet/KismetSystemLibrary.h"

ANumberBaseballGameModeBase::ANumberBaseballGameModeBase()
{
    HostTries = 3;
    GuestTries = 3;
    bHostOut = false;
    bGuestOut = false;
    bHostWin = false;
    bGuestWin = false;
}

void ANumberBaseballGameModeBase::BeginPlay()
{
    Super::BeginPlay();
    CurrentAnswer = UNumberBaseballLibrary::GenerateAnswer();
    PrintMessageToScreen(TEXT("게임이 시작되었습니다."));
}

void ANumberBaseballGameModeBase::OnChatCommand(EPlayerType PlayerType, const FString& Command)
{
    if (!Command.StartsWith("/"))
        return;

    FString Guess = Command.RightChop(1);

    if (!UNumberBaseballLibrary::IsValidGuess(Guess))
    {
        PrintMessageToScreen(TEXT("잘못된 입력입니다. OUT 처리됩니다."));
        if (PlayerType == EPlayerType::Host)
        {
            HostTries--;
            if (HostTries <= 0) bHostOut = true;
        }
        else
        {
            GuestTries--;
            if (GuestTries <= 0) bGuestOut = true;
        }
        CheckGameResult();
        return;
    }

    FSBResult Result = UNumberBaseballLibrary::EvaluateGuess(CurrentAnswer, Guess);

    FString Feedback = FString::Printf(TEXT("결과: %dS %dB"), Result.Strikes, Result.Balls);
    if (Result.Strikes == 0 && Result.Balls == 0)
    {
        Feedback = TEXT("OUT!");
    }
    PrintMessageToScreen(Feedback);

    if (PlayerType == EPlayerType::Host)
    {
        HostTries--;
        if (Result.Strikes == 3)
            bHostWin = true;
        else if (HostTries <= 0)
            bHostOut = true;
    }
    else
    {
        GuestTries--;
        if (Result.Strikes == 3)
            bGuestWin = true;
        else if (GuestTries <= 0)
            bGuestOut = true;
    }

    CheckGameResult();
}

void ANumberBaseballGameModeBase::CheckGameResult()
{
    if (bHostWin)
    {
        PrintMessageToScreen(TEXT("Host Won!! 다시 게임이 시작됐다."));
        ResetGame();
        return;
    }

    if (bGuestWin)
    {
        PrintMessageToScreen(TEXT("Guest Won!! 다시 게임이 시작됐다."));
        ResetGame();
        return;
    }

    if ((bHostOut || HostTries <= 0) && (bGuestOut || GuestTries <= 0))
    {
        PrintMessageToScreen(TEXT("Draw!"));
        ResetGame();
    }
}

void ANumberBaseballGameModeBase::ResetGame()
{
    HostTries = 3;
    GuestTries = 3;
    bHostOut = false;
    bGuestOut = false;
    bHostWin = false;
    bGuestWin = false;
    CurrentAnswer = UNumberBaseballLibrary::GenerateAnswer();
    PrintMessageToScreen(TEXT("새 게임이 시작됩니다."));
}

void ANumberBaseballGameModeBase::PrintMessageToScreen(const FString& Msg)
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, Msg);
    }
}
