#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ERCombatAbilityDefinition.generated.h"

UCLASS(BlueprintType)
class ERCORE_API UERCombatAbilityDefinition : public UDataAsset
{
    GENERATED_BODY()
public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability") FName AbilityId = NAME_None;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability") FText DisplayName;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability", meta=(ClampMin="0.0")) float BaseDamage = 10.0f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability", meta=(ClampMin="0.0")) float StaminaCost = 10.0f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability", meta=(ClampMin="0.0")) float CooldownSeconds = 1.0f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability", meta=(ClampMin="0.0", ClampMax="1.0")) float CriticalChance = 0.05f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability", meta=(ClampMin="1.0")) float CriticalMultiplier = 1.5f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability", meta=(ClampMin="0.0")) float Range = 250.0f;
};
