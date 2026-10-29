#include "ERCombatComponent.h"
#include "ERCombatAbilityDefinition.h"
#include "ERAttributeComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Controller.h"

UERCombatComponent::UERCombatComponent() { SetIsReplicatedByDefault(true); }

bool UERCombatComponent::TryUseAbility(UERCombatAbilityDefinition* Ability, AActor* Target)
{
    if (!Ability || Ability->AbilityId.IsNone() || !IsValid(Target) || Target == GetOwner()) return false;
    AActor* Owner = GetOwner();
    if (!IsValid(Owner) || !Owner->GetWorld()) return false;
    if (!Owner->HasAuthority()) { ServerUseAbility(Ability, Target); return true; }

    const float Now = Owner->GetWorld()->GetTimeSeconds();
    const float* NextUse = NextAllowedUseTime.Find(Ability->AbilityId);
    if (NextUse && Now < *NextUse) return false;
    if (FVector::DistSquared(Owner->GetActorLocation(), Target->GetActorLocation())
        > FMath::Square(FMath::Max(0.0f, Ability->Range))) return false;

    ApplyAbility(Ability, Target);
    NextAllowedUseTime.Add(Ability->AbilityId, Now + FMath::Max(0.0f, Ability->CooldownSeconds));
    return true;
}

void UERCombatComponent::ServerUseAbility_Implementation(UERCombatAbilityDefinition* Ability, AActor* Target)
{
    TryUseAbility(Ability, Target);
}

void UERCombatComponent::ApplyAbility(UERCombatAbilityDefinition* Ability, AActor* Target)
{
    if (!Ability || !IsValid(Target) || !GetOwner() || !GetOwner()->HasAuthority()) return;

    float Damage = FMath::Max(0.0f, Ability->BaseDamage);
    if (FMath::FRand() < FMath::Clamp(Ability->CriticalChance, 0.0f, 1.0f))
        Damage *= FMath::Max(1.0f, Ability->CriticalMultiplier);

    if (UERAttributeComponent* Attributes = Target->FindComponentByClass<UERAttributeComponent>())
    {
        Attributes->ApplyDamage(Damage);
    }
    else
    {
        AController* InstigatorController = GetOwner()->GetInstigatorController();
        Target->TakeDamage(Damage, FDamageEvent(), InstigatorController, GetOwner());
    }

    OnAbilityUsed.Broadcast(Ability->AbilityId, Target);
    OnDamageApplied.Broadcast(Target, Damage);
}
