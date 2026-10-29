#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ERPlayerCharacter.generated.h"

class UERCombatComponent;
class UEREquipmentComponent;
class UERInventoryComponent;
class UERInteractionComponent;
class UERProgressionComponent;
class UERQuestComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FERHealthChanged, float, CurrentHealth, float, MaxHealth);

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

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Etherroad|Systems") TObjectPtr<UERCombatComponent> CombatComponent;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Etherroad|Systems") TObjectPtr<UEREquipmentComponent> EquipmentComponent;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Etherroad|Systems") TObjectPtr<UERInventoryComponent> InventoryComponent;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Etherroad|Systems") TObjectPtr<UERInteractionComponent> InteractionComponent;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Etherroad|Systems") TObjectPtr<UERProgressionComponent> ProgressionComponent;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Etherroad|Systems") TObjectPtr<UERQuestComponent> QuestComponent;

    UPROPERTY(BlueprintAssignable, Category="Etherroad|Events")
    FERHealthChanged OnHealthChanged;

    UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category="Etherroad|Combat")
    void ApplyServerDamage(float DamageAmount);
    UFUNCTION(BlueprintPure, Category="Etherroad|Attributes")
    float GetHealthPercent() const;

    virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
    UFUNCTION() void OnRep_CurrentHealth();
    virtual void BeginPlay() override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
