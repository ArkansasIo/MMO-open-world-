#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ERInteractionComponent.h"
#include "ERLootContainer.generated.h"

USTRUCT(BlueprintType)
struct FERLootContainerStack
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Loot") FName ItemId = NAME_None;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Loot", meta=(ClampMin="1")) int32 Quantity = 1;
};

UCLASS(Blueprintable)
class ERCORE_API AERLootContainer : public AActor, public IERInteractableTarget
{
    GENERATED_BODY()
public:
    AERLootContainer();
    UPROPERTY(Replicated, EditInstanceOnly, BlueprintReadOnly, Category="Loot") TArray<FERLootContainerStack> Contents;
    UPROPERTY(Replicated, VisibleInstanceOnly, BlueprintReadOnly, Category="Loot") bool bLooted = false;
    virtual bool CanInteract_Implementation(AActor* Interactor) const override;
    virtual void Interact_Implementation(AActor* Interactor) override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
