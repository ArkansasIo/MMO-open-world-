#include "ERInventoryComponent.h"
#include "Net/UnrealNetwork.h"

UERInventoryComponent::UERInventoryComponent()
{
    SetIsReplicatedByDefault(true);
}

bool UERInventoryComponent::AddItem(FName ItemId, int32 Quantity)
{
    if (!GetOwner() || !GetOwner()->HasAuthority() || ItemId.IsNone() || Quantity <= 0)
    {
        return false;
    }

    for (FERItemStack& Stack : Items)
    {
        if (Stack.ItemId == ItemId)
        {
            Stack.Quantity += Quantity;
            OnInventoryChanged.Broadcast();
            return true;
        }
    }

    if (Items.Num() >= SlotCapacity)
    {
        return false;
    }

    FERItemStack NewStack;
    NewStack.ItemId = ItemId;
    NewStack.Quantity = Quantity;
    Items.Add(NewStack);
    OnInventoryChanged.Broadcast();
    return true;
}

bool UERInventoryComponent::RemoveItem(FName ItemId, int32 Quantity)
{
    if (!GetOwner() || !GetOwner()->HasAuthority() || ItemId.IsNone() || Quantity <= 0)
    {
        return false;
    }

    const int32 Index = Items.IndexOfByPredicate([ItemId](const FERItemStack& Stack)
    {
        return Stack.ItemId == ItemId;
    });

    if (Index == INDEX_NONE || Items[Index].Quantity < Quantity)
    {
        return false;
    }

    Items[Index].Quantity -= Quantity;
    if (Items[Index].Quantity == 0)
    {
        Items.RemoveAt(Index);
    }
    OnInventoryChanged.Broadcast();
    return true;
}

int32 UERInventoryComponent::GetItemQuantity(FName ItemId) const
{
    int32 Total = 0;
    for (const FERItemStack& Stack : Items)
    {
        if (Stack.ItemId == ItemId)
        {
            Total += Stack.Quantity;
        }
    }
    return Total;
}

void UERInventoryComponent::OnRep_Items()
{
    OnInventoryChanged.Broadcast();
}

void UERInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(UERInventoryComponent, Items);
}
