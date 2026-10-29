#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ERAttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FERAttributeChanged, float, Current, float, Maximum);

UCLASS(ClassGroup=(Etherroad), BlueprintType, Blueprintable, meta=(BlueprintSpawnableComponent))
class ERCORE_API UERAttributeComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UERAttributeComponent();

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes", meta=(ClampMin="1.0"))
    float MaxHealth = 100.0f;

    UPROPERTY(ReplicatedUsing=OnRep_Health, VisibleInstanceOnly, BlueprintReadOnly, Category="Attributes")
    float Health = 100.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes", meta=(ClampMin="0.0"))
    float MaxStamina = 100.0f;

    UPROPERTY(ReplicatedUsing=OnRep_Stamina, VisibleInstanceOnly, BlueprintReadOnly, Category="Attributes")
    float Stamina = 100.0f;

    UPROPERTY(BlueprintAssignable, Category="Attributes|Events")
    FERAttributeChanged OnHealthChanged;

    UPROPERTY(BlueprintAssignable, Category="Attributes|Events")
    FERAttributeChanged OnStaminaChanged;

    UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category="Attributes")
    void ApplyDamage(float Amount);

    UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category="Attributes")
    void Heal(float Amount);

    UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category="Attributes")
    bool SpendStamina(float Amount);

    UFUNCTION(BlueprintPure, Category="Attributes")
    float GetHealthPercent() const;

protected:
    UFUNCTION()
    void OnRep_Health();

    UFUNCTION()
    void OnRep_Stamina();

    virtual void BeginPlay() override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
