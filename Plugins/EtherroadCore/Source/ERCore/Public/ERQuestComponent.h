#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ERQuestDefinition.h"
#include "ERQuestComponent.generated.h"

USTRUCT(BlueprintType)
struct FERQuestProgress
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category="Quest")
    FName QuestId;

    UPROPERTY(BlueprintReadOnly, Category="Quest")
    EERQuestStatus Status = EERQuestStatus::NotStarted;

    UPROPERTY(BlueprintReadOnly, Category="Quest")
    TArray<FERQuestObjectiveProgress> Objectives;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FERQuestUpdated, FName, QuestId);

UCLASS(ClassGroup=(Etherroad), BlueprintType, Blueprintable, meta=(BlueprintSpawnableComponent))
class ERCORE_API UERQuestComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UERQuestComponent();

    UPROPERTY(ReplicatedUsing=OnRep_QuestProgress, VisibleInstanceOnly, BlueprintReadOnly, Category="Quests")
    TArray<FERQuestProgress> QuestProgress;

    UPROPERTY(BlueprintAssignable, Category="Quests|Events")
    FERQuestUpdated OnQuestUpdated;

    UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category="Quests")
    bool StartQuest(UERQuestDefinition* Definition);

    UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category="Quests")
    bool AddObjectiveProgress(FName QuestId, FName ObjectiveId, int32 Amount = 1);

protected:
    UFUNCTION()
    void OnRep_QuestProgress();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
