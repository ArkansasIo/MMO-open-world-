#pragma once

#include "CoreMinimal.h"
#include "Engine/PrimaryDataAsset.h"
#include "ERRegionDefinition.generated.h"

UENUM(BlueprintType)
enum class EERBiomeType : uint8
{
    TemperateForest,
    BorealForest,
    Grassland,
    Desert,
    Tundra,
    Wetlands,
    Mountains,
    Volcanic,
    Coastal,
    Arcane
};

UCLASS(BlueprintType)
class ERCORE_API UERRegionDefinition : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Region")
    FName RegionId;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Region")
    FText DisplayName;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Region")
    EERBiomeType Biome = EERBiomeType::TemperateForest;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Generation")
    int32 GeneratorVersion = 1;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Generation")
    int32 DefaultSeed = 12345;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Streaming", meta=(ClampMin="1000.0"))
    float RegionExtentMeters = 10000.0f;
};
