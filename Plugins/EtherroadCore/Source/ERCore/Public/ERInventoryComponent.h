#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ERInventoryComponent.generated.h"

USTRUCT(BlueprintType)
struct FERItemStack
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory")
    FName ItemId;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory", meta=(ClampMin="0"))
    int32 Quantity = 0;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FERInventoryChanged);

UCLASS(ClassGroup=(Etherroad), BlueprintType, Blueprintable, meta=(BlueprintSpawnableComponent))
class ERCORE_API UERInventoryComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UERInventoryComponent();

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory", meta=(ClampMin="1"))
    int32 SlotCapacity = 40;

    UPROPERTY(ReplicatedUsing=OnRep_Items, VisibleInstanceOnly, BlueprintReadOnly, Category="Inventory")
    TArray<FERItemStack> Items;

    UPROPERTY(BlueprintAssignable, Category="Inventory|Events")
    FERInventoryChanged OnInventoryChanged;

    UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category="Inventory")
    bool AddItem(FName ItemId, int32 Quantity);

    UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category="Inventory")
    bool RemoveItem(FName ItemId, int32 Quantity);

    UFUNCTION(BlueprintPure, Category="Inventory")
    int32 GetItemQuantity(FName ItemId) const;

protected:
    UFUNCTION()
    void OnRep_Items();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
