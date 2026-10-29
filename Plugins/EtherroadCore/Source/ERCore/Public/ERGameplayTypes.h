#pragma once

#include "CoreMinimal.h"
#include "ERGameplayTypes.generated.h"

UENUM(BlueprintType)
enum class EERCombatResult : uint8
{
    Miss,
    Hit,
    Critical,
    Blocked,
    Immune
};

UENUM(BlueprintType)
enum class EERItemRarity : uint8
{
    Common,
    Uncommon,
    Rare,
    Epic,
    Legendary,
    Mythic
};

USTRUCT(BlueprintType)
struct FERAttributeSnapshot
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Etherroad|Attributes", meta=(ClampMin="0.0"))
    float Health = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Etherroad|Attributes", meta=(ClampMin="0.0"))
    float MaxHealth = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Etherroad|Attributes", meta=(ClampMin="0.0"))
    float Stamina = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Etherroad|Attributes", meta=(ClampMin="0.0"))
    float MaxStamina = 100.0f;
};
