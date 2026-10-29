#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ERInteractionComponent.h"
#include "ERResourceNode.generated.h"

UCLASS(Blueprintable)
class ERCORE_API AERResourceNode : public AActor, public IERInteractableTarget
{
    GENERATED_BODY()
public:
    AERResourceNode();

    UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Resource", meta=(ExposeOnSpawn="true"))
    FName ResourceItemId = FName("wood");

    UPROPERTY(Replicated, EditInstanceOnly, BlueprintReadOnly, Category="Resource", meta=(ClampMin="0", ExposeOnSpawn="true"))
    int32 RemainingQuantity = 5;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Resource", meta=(ClampMin="1"))
    int32 QuantityPerGather = 1;

    virtual bool CanInteract_Implementation(AActor* Interactor) const override;
    virtual void Interact_Implementation(AActor* Interactor) override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
