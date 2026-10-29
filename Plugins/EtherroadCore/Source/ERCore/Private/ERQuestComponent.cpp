#include "ERQuestComponent.h"
#include "Net/UnrealNetwork.h"

UERQuestComponent::UERQuestComponent()
{
    SetIsReplicatedByDefault(true);
}

bool UERQuestComponent::StartQuest(UERQuestDefinition* Definition)
{
    if (!GetOwner() || !GetOwner()->HasAuthority() || !Definition || Definition->QuestId.IsNone()) return false;
    if (QuestProgress.ContainsByPredicate([Definition](const FERQuestProgress& P) { return P.QuestId == Definition->QuestId; })) return false;

    FERQuestProgress Progress;
    Progress.QuestId = Definition->QuestId;
    Progress.Status = EERQuestStatus::Active;
    for (const FERQuestObjectiveDefinition& Objective : Definition->Objectives)
    {
        FERQuestObjectiveProgress O;
        O.ObjectiveId = Objective.ObjectiveId;
        O.RequiredCount = FMath::Max(1, Objective.RequiredCount);
        Progress.Objectives.Add(O);
    }
    QuestProgress.Add(Progress);
    OnQuestUpdated.Broadcast(Definition->QuestId);
    GetOwner()->ForceNetUpdate();
    return true;
}

bool UERQuestComponent::AddObjectiveProgress(FName QuestId, FName ObjectiveId, int32 Amount)
{
    if (!GetOwner() || !GetOwner()->HasAuthority() || Amount <= 0) return false;
    FERQuestProgress* Progress = QuestProgress.FindByPredicate([QuestId](const FERQuestProgress& P) { return P.QuestId == QuestId; });
    if (!Progress || Progress->Status != EERQuestStatus::Active) return false;
    FERQuestObjectiveProgress* Objective = Progress->Objectives.FindByPredicate([ObjectiveId](const FERQuestObjectiveProgress& O) { return O.ObjectiveId == ObjectiveId; });
    if (!Objective || Objective->IsComplete()) return false;

    Objective->CurrentCount = FMath::Min(Objective->CurrentCount + Amount, Objective->RequiredCount);
    const bool bAllComplete = Progress->Objectives.Num() > 0 && Progress->Objectives.ContainsByPredicate([](const FERQuestObjectiveProgress& O) { return !O.IsComplete(); }) == false;
    if (bAllComplete) Progress->Status = EERQuestStatus::Completed;
    OnQuestUpdated.Broadcast(QuestId);
    GetOwner()->ForceNetUpdate();
    return true;
}

void UERQuestComponent::OnRep_QuestProgress()
{
    for (const FERQuestProgress& Progress : QuestProgress) OnQuestUpdated.Broadcast(Progress.QuestId);
}

void UERQuestComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(UERQuestComponent, QuestProgress);
}
