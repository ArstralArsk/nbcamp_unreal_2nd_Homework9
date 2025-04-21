#include "NumberBaseballLibrary.h"

FString UNumberBaseballLibrary::GenerateAnswer()
{
    TArray<int32> Digits;
    for (int32 i = 1; i <= 9; ++i)
    {
        Digits.Add(i);
    }
    // ¼¯±â
    for (int32 i = Digits.Num() - 1; i > 0; --i)
    {
        int32 j = FMath::RandRange(0, i);
        Digits.Swap(i, j);
    }

    FString Result;
    for (int32 i = 0; i < 3; ++i)
    {
        Result.AppendInt(Digits[i]);
    }

    return Result;
}

FSBResult UNumberBaseballLibrary::EvaluateGuess(const FString& Answer, const FString& Guess)
{
    FSBResult Result;
    if (!IsValidGuess(Guess))
    {
        Result.bIsOut = true;
        return Result;
    }

    for (int32 i = 0; i < 3; ++i)
    {
        if (Guess[i] == Answer[i])
        {
            Result.Strikes++;
        }
        else if (Answer.Contains(FString::Chr(Guess[i])))
        {
            Result.Balls++;
        }
    }

    return Result;
}

bool UNumberBaseballLibrary::IsValidGuess(const FString& Guess)
{
    if (Guess.Len() != 3) return false;

    TSet<TCHAR> UniqueDigits;
    for (TCHAR C : Guess)
    {
        if (!FChar::IsDigit(C) || C == '0')
            return false;

        if (UniqueDigits.Contains(C))
            return false;

        UniqueDigits.Add(C);
    }

    return true;
}
