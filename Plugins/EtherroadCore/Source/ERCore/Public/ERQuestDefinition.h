#pragma once

#include "CoreMinimal.h"
#include "Engine/PrimaryDataAsset.h"
#include "ERQuestTypes.h"
#include "ERQuestDefinition.generated.h"

USTRUCT(BlueprintType)
struct FERQuestObjectiveDefinition
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Objective")
    FName ObjectiveId;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Objective")
    FText Description;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Objective", meta=(ClampMin="1"))
    int32 RequiredCount = 1;
};

UCLASS(BlueprintType)
class ERCORE_API UERQuestDefinition : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Quest")
    FName QuestId;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Quest")
    FText Title;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Quest", meta=(MultiLine="true"))
    FText Description;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Quest")
    TArray<FERQuestObjectiveDefinition> Objectives;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Rewards", meta=(ClampMin="0"))
    int32 ExperienceReward = 0;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Rewards", meta=(ClampMin="0"))
    int64 CurrencyReward = 0;
};
