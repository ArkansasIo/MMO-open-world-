#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ERInteractable.generated.h"

UINTERFACE(BlueprintType)
class ERCORE_API UERInteractable : public UInterface
{
    GENERATED_BODY()
};

class ERCORE_API IERInteractable
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Etherroad|Interaction")
    FText GetInteractionPrompt() const;

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Etherroad|Interaction")
    bool CanInteract(AActor* InteractingActor) const;

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Etherroad|Interaction")
    void Interact(AActor* InteractingActor);
};
