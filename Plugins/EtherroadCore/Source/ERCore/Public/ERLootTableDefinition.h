#pragma once
#include "CoreMinimal.h"
#include "Engine/PrimaryDataAsset.h"
#include "ERLootTableDefinition.generated.h"

USTRUCT(BlueprintType)
struct FERLootEntry
{
    GENERATED_BODY()
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Loot") FName ItemId = NAME_None;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Loot", meta=(ClampMin="0.0", ClampMax="1.0")) float DropChance = 1.0f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Loot", meta=(ClampMin="1")) int32 MinQuantity = 1;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Loot", meta=(ClampMin="1")) int32 MaxQuantity = 1;
};

UCLASS(BlueprintType)
class ERCORE_API UERLootTableDefinition : public UPrimaryDataAsset
{
    GENERATED_BODY()
public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Loot") FName LootTableId = NAME_None;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Loot", meta=(ClampMin="0")) int32 Rolls = 1;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Loot") TArray<FERLootEntry> Entries;
    UFUNCTION(BlueprintCallable, Category="Loot") TArray<FName> RollLootIds(TArray<int32>& OutQuantities, int32 Seed) const;
};
