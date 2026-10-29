#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ERGenerationLibrary.generated.h"

/** Deterministic seed helpers. Generator-version changes must be tracked in region manifests. */
UCLASS()
class ERCORE_API UERGenerationLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure, Category="Etherroad|Generation")
    static int32 MakeRegionSeed(FName RealmId, FName RegionId, int32 WorldSeed, int32 GeneratorVersion);

    UFUNCTION(BlueprintPure, Category="Etherroad|Generation")
    static float StableNoise01(int32 Seed, int32 X, int32 Y);
};
