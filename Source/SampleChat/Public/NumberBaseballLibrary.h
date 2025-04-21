#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "NumberBaseballLibrary.generated.h"

USTRUCT(BlueprintType)
struct FSBResult
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    int32 Strikes;

    UPROPERTY(BlueprintReadOnly)
    int32 Balls;

    UPROPERTY(BlueprintReadOnly)
    bool bIsOut;

    FSBResult()
        : Strikes(0), Balls(0), bIsOut(false) {
    }
};

UCLASS()
class SAMPLECHAT_API UNumberBaseballLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Number Baseball")
    static FString GenerateAnswer(); // ex: "386"

    UFUNCTION(BlueprintCallable, Category = "Number Baseball")
    static FSBResult EvaluateGuess(const FString& Answer, const FString& Guess);

    UFUNCTION(BlueprintCallable, Category = "Number Baseball")
    static bool IsValidGuess(const FString& Guess);
};
