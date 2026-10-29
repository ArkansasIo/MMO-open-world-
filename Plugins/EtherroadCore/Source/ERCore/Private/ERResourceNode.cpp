#include "ERResourceNode.h"
#include "ERInventoryComponent.h"
#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h"

AERResourceNode::AERResourceNode()
{
    bReplicates = true;
    SetReplicateMovement(true);
}

bool AERResourceNode::CanInteract_Implementation(AActor* Interactor) const
{
    return IsValid(Interactor) && RemainingQuantity > 0 && !ResourceItemId.IsNone()
        && Interactor->FindComponentByClass<UERInventoryComponent>() != nullptr;
}

void AERResourceNode::Interact_Implementation(AActor* Interactor)
{
    if (!HasAuthority() || !CanInteract_Implementation(Interactor)) return;
    UERInventoryComponent* Inventory = Interactor->FindComponentByClass<UERInventoryComponent>();
    if (!Inventory) return;
    const int32 Amount = FMath::Min(FMath::Max(1, QuantityPerGather), RemainingQuantity);
    if (Inventory->AddItem(ResourceItemId, Amount))
    {
        RemainingQuantity -= Amount;
        ForceNetUpdate();
    }
}

void AERResourceNode::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AERResourceNode, RemainingQuantity);
}
