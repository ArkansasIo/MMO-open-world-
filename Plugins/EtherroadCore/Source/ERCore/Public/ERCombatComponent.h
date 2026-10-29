#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ERCombatComponent.generated.h"

class UERCombatAbilityDefinition;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FERAbilityUsed, FName, AbilityId, AActor*, Target);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FERCombatDamageApplied, AActor*, Target, float, Damage);

UCLASS(ClassGroup=(Etherroad), BlueprintType, Blueprintable, meta=(BlueprintSpawnableComponent))
class ERCORE_API UERCombatComponent : public UActorComponent
{
    GENERATED_BODY()
public:
    UERCombatComponent();
    UPROPERTY(BlueprintAssignable, Category="Combat|Events") FERAbilityUsed OnAbilityUsed;
    UPROPERTY(BlueprintAssignable, Category="Combat|Events") FERCombatDamageApplied OnDamageApplied;
    UFUNCTION(BlueprintCallable, Category="Combat") bool TryUseAbility(UERCombatAbilityDefinition* Ability, AActor* Target);
protected:
    UPROPERTY(Transient) TMap<FName, float> NextAllowedUseTime;
    UFUNCTION(Server, Reliable) void ServerUseAbility(UERCombatAbilityDefinition* Ability, AActor* Target);
    void ApplyAbility(UERCombatAbilityDefinition* Ability, AActor* Target);
};
