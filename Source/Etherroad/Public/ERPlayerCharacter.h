#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ERPlayerCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FERHealthChanged, float, CurrentHealth, float, MaxHealth);

/**
 * Minimal replicated player-character foundation.
 * Production combat must still validate range, cooldown, line of sight, and target authority.
 */
UCLASS(Blueprintable)
class ETHERROAD_API AERPlayerCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AERPlayerCharacter();

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Etherroad|Attributes", meta=(ClampMin="1.0"))
    float MaxHealth = 100.0f;

    UPROPERTY(ReplicatedUsing=OnRep_CurrentHealth, VisibleInstanceOnly, BlueprintReadOnly, Category="Etherroad|Attributes")
    float CurrentHealth = 100.0f;

    UPROPERTY(BlueprintAssignable, Category="Etherroad|Events")
    FERHealthChanged OnHealthChanged;

    UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category="Etherroad|Combat")
    void ApplyServerDamage(float DamageAmount);

    UFUNCTION(BlueprintPure, Category="Etherroad|Attributes")
    float GetHealthPercent() const;

protected:
    UFUNCTION()
    void OnRep_CurrentHealth();

    virtual void BeginPlay() override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
