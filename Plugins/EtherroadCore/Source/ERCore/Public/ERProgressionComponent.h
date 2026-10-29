#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ERProgressionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FERLevelChanged, int32, OldLevel, int32, NewLevel, int64, TotalXP);

UCLASS(ClassGroup=(Etherroad), BlueprintType, Blueprintable, meta=(BlueprintSpawnableComponent))
class ERCORE_API UERProgressionComponent : public UActorComponent
{
    GENERATED_BODY()
public:
    UERProgressionComponent();
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Progression", meta=(ClampMin="1")) int32 MaxLevel = 100;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Progression", meta=(ClampMin="1.0")) float XPExponent = 2.0f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Progression", meta=(ClampMin="1.0")) float XPMultiplier = 100.0f;
    UPROPERTY(ReplicatedUsing=OnRep_Progression, VisibleInstanceOnly, BlueprintReadOnly, Category="Progression") int32 Level = 1;
    UPROPERTY(ReplicatedUsing=OnRep_Progression, VisibleInstanceOnly, BlueprintReadOnly, Category="Progression") int64 TotalXP = 0;
    UPROPERTY(BlueprintAssignable, Category="Progression|Events") FERLevelChanged OnLevelChanged;
    UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category="Progression") void GrantXP(int64 Amount);
    UFUNCTION(BlueprintPure, Category="Progression") int64 GetXPForNextLevel() const;
    UFUNCTION(BlueprintPure, Category="Progression") int64 GetXPWithinCurrentLevel() const;
protected:
    UFUNCTION() void OnRep_Progression();
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
