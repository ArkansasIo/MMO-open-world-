#include "EREquipmentComponent.h"
#include "Net/UnrealNetwork.h"

UEREquipmentComponent::UEREquipmentComponent() { SetIsReplicatedByDefault(true); }

bool UEREquipmentComponent::EquipItem(EEREquipmentSlot Slot, FName ItemId)
{
    if (!GetOwner() || !GetOwner()->HasAuthority() || ItemId.IsNone()) return false;
    for (FEREquippedItem& Entry : EquippedItems)
    {
        if (Entry.Slot == Slot) { Entry.ItemId = ItemId; OnEquipmentChanged.Broadcast(); return true; }
    }
    FEREquippedItem Entry; Entry.Slot = Slot; Entry.ItemId = ItemId;
    EquippedItems.Add(Entry); OnEquipmentChanged.Broadcast(); return true;
}

bool UEREquipmentComponent::UnequipItem(EEREquipmentSlot Slot)
{
    if (!GetOwner() || !GetOwner()->HasAuthority()) return false;
    const int32 Removed = EquippedItems.RemoveAll([Slot](const FEREquippedItem& Entry) { return Entry.Slot == Slot; });
    if (Removed > 0) { OnEquipmentChanged.Broadcast(); return true; }
    return false;
}

FName UEREquipmentComponent::GetEquippedItem(EEREquipmentSlot Slot) const
{
    for (const FEREquippedItem& Entry : EquippedItems) if (Entry.Slot == Slot) return Entry.ItemId;
    return NAME_None;
}

void UEREquipmentComponent::OnRep_Equipment() { OnEquipmentChanged.Broadcast(); }
void UEREquipmentComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(UEREquipmentComponent, EquippedItems);
}
