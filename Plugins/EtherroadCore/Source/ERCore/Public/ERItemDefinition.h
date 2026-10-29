#pragma once

#include "CoreMinimal.h"
#include "Engine/PrimaryDataAsset.h"
#include "ERGameplayTypes.h"
#include "ERItemDefinition.generated.h"

UCLASS(BlueprintType)
class ERCORE_API UERItemDefinition : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item")
    FName ItemId;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item")
    FText DisplayName;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item", meta=(MultiLine="true"))
    FText Description;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item")
    EERItemRarity Rarity = EERItemRarity::Common;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item", meta=(ClampMin="1"))
    int32 MaxStackSize = 99;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item", meta=(ClampMin="0"))
    int32 VendorValue = 0;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item")
    bool bIsTradable = true;
};
