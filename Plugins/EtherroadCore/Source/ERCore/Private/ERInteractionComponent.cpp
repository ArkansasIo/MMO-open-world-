#include "ERInteractionComponent.h"
#include "GameFramework/Actor.h"

UERInteractionComponent::UERInteractionComponent() { SetIsReplicatedByDefault(true); }

bool UERInteractionComponent::ValidateTarget(AActor* Target) const
{
    const AActor* Owner = GetOwner();
    if (!IsValid(Owner) || !IsValid(Target) || Target == Owner || !Owner->GetWorld()) return false;
    if (FVector::DistSquared(Owner->GetActorLocation(), Target->GetActorLocation())
        > FMath::Square(FMath::Max(50.0f, InteractionRange))) return false;
    if (!Target->GetClass()->ImplementsInterface(UERInteractableTarget::StaticClass())) return false;
    return IERInteractableTarget::Execute_CanInteract(Target, const_cast<AActor*>(Owner));
}

bool UERInteractionComponent::RequestInteract(AActor* Target)
{
    AActor* Owner = GetOwner();
    if (!IsValid(Owner)) return false;
    if (!Owner->HasAuthority()) { ServerInteract(Target); return true; }
    if (!ValidateTarget(Target)) return false;
    IERInteractableTarget::Execute_Interact(Target, Owner);
    return true;
}

void UERInteractionComponent::ServerInteract_Implementation(AActor* Target) { RequestInteract(Target); }
