#pragma once

#include "CoreMinimal.h"
#include "ERQuestTypes.generated.h"

UENUM(BlueprintType)
enum class EERQuestStatus : uint8
{
    NotStarted,
    Active,
    Completed,
    Abandoned
};

USTRUCT(BlueprintType)
struct FERQuestObjectiveProgress
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Quest")
    FName ObjectiveId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Quest", meta=(ClampMin="0"))
    int32 CurrentCount = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Quest", meta=(ClampMin="1"))
    int32 RequiredCount = 1;

    bool IsComplete() const { return CurrentCount >= RequiredCount; }
};
