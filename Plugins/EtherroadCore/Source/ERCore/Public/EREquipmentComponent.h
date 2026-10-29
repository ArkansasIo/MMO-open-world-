#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EREquipmentComponent.generated.h"

UENUM(BlueprintType)
enum class EEREquipmentSlot : uint8 { Head, Chest, Legs, Feet, MainHand, OffHand, Accessory1, Accessory2 };

USTRUCT(BlueprintType)
struct FEREquippedItem
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Equipment") EEREquipmentSlot Slot = EEREquipmentSlot::MainHand;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Equipment") FName ItemId = NAME_None;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEREquipmentChanged);

UCLASS(ClassGroup=(Etherroad), BlueprintType, Blueprintable, meta=(BlueprintSpawnableComponent))
class ERCORE_API UEREquipmentComponent : public UActorComponent
{
    GENERATED_BODY()
public:
    UEREquipmentComponent();
    UPROPERTY(ReplicatedUsing=OnRep_Equipment, VisibleInstanceOnly, BlueprintReadOnly, Category="Equipment") TArray<FEREquippedItem> EquippedItems;
    UPROPERTY(BlueprintAssignable, Category="Equipment|Events") FEREquipmentChanged OnEquipmentChanged;
    UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category="Equipment") bool EquipItem(EEREquipmentSlot Slot, FName ItemId);
    UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category="Equipment") bool UnequipItem(EEREquipmentSlot Slot);
    UFUNCTION(BlueprintPure, Category="Equipment") FName GetEquippedItem(EEREquipmentSlot Slot) const;
protected:
    UFUNCTION() void OnRep_Equipment();
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
