#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ERInteractionComponent.generated.h"

UINTERFACE(BlueprintType)
class UERInteractableTarget : public UInterface { GENERATED_BODY() };

class ERCORE_API IERInteractableTarget
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction") bool CanInteract(AActor* Interactor) const;
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction") void Interact(AActor* Interactor);
};

UCLASS(ClassGroup=(Etherroad), BlueprintType, Blueprintable, meta=(BlueprintSpawnableComponent))
class ERCORE_API UERInteractionComponent : public UActorComponent
{
    GENERATED_BODY()
public:
    UERInteractionComponent();
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interaction", meta=(ClampMin="50.0")) float InteractionRange = 300.0f;
    UFUNCTION(BlueprintCallable, Category="Interaction") bool RequestInteract(AActor* Target);
protected:
    UFUNCTION(Server, Reliable) void ServerInteract(AActor* Target);
    bool ValidateTarget(AActor* Target) const;
};
