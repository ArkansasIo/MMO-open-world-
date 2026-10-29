#include "ERLootContainer.h"
#include "ERInventoryComponent.h"
#include "Net/UnrealNetwork.h"

AERLootContainer::AERLootContainer()
{
    bReplicates = true;
    SetReplicateMovement(true);
}

bool AERLootContainer::CanInteract_Implementation(AActor* Interactor) const
{
    return !bLooted && IsValid(Interactor)
        && Interactor->FindComponentByClass<UERInventoryComponent>() != nullptr;
}

void AERLootContainer::Interact_Implementation(AActor* Interactor)
{
    if (!HasAuthority() || !CanInteract_Implementation(Interactor)) return;
    UERInventoryComponent* Inventory = Interactor->FindComponentByClass<UERInventoryComponent>();
    if (!Inventory) return;

    for (int32 Index = 0; Index < Contents.Num(); ++Index)
    {
        const FERLootContainerStack Stack = Contents[Index];
        if (Stack.ItemId.IsNone() || Stack.Quantity <= 0) continue;
        if (!Inventory->AddItem(Stack.ItemId, Stack.Quantity))
        {
            TArray<FERLootContainerStack> Remaining;
            for (int32 RemainingIndex = Index; RemainingIndex < Contents.Num(); ++RemainingIndex)
                Remaining.Add(Contents[RemainingIndex]);
            Contents = Remaining;
            ForceNetUpdate();
            return;
        }
    }
    Contents.Reset();
    bLooted = true;
    ForceNetUpdate();
}

void AERLootContainer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AERLootContainer, Contents);
    DOREPLIFETIME(AERLootContainer, bLooted);
}
