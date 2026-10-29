#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EREnemyCharacter.generated.h"

UCLASS(Blueprintable)
class ERCORE_API AEREnemyCharacter : public ACharacter
{
    GENERATED_BODY()
public:
    AEREnemyCharacter();
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Enemy|Rewards", meta=(ClampMin="0"))
    int64 XPReward = 25;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Enemy|Combat", meta=(ClampMin="1.0"))
    float BaseDamage = 8.0f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Enemy|AI")
    FName AIProfileId = FName("DefaultMelee");
};
