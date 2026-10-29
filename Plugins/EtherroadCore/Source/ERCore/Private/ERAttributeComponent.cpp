#include "ERAttributeComponent.h"
#include "Net/UnrealNetwork.h"

UERAttributeComponent::UERAttributeComponent()
{
    SetIsReplicatedByDefault(true);
}

void UERAttributeComponent::BeginPlay()
{
    Super::BeginPlay();
    if (GetOwner() && GetOwner()->HasAuthority())
    {
        Health = FMath::Clamp(Health, 0.0f, MaxHealth);
        Stamina = FMath::Clamp(Stamina, 0.0f, MaxStamina);
    }
}

void UERAttributeComponent::ApplyDamage(float Amount)
{
    if (!GetOwner() || !GetOwner()->HasAuthority() || Amount <= 0.0f || Health <= 0.0f) return;
    Health = FMath::Clamp(Health - Amount, 0.0f, MaxHealth);
    OnHealthChanged.Broadcast(Health, MaxHealth);
    GetOwner()->ForceNetUpdate();
}

void UERAttributeComponent::Heal(float Amount)
{
    if (!GetOwner() || !GetOwner()->HasAuthority() || Amount <= 0.0f || Health <= 0.0f) return;
    Health = FMath::Clamp(Health + Amount, 0.0f, MaxHealth);
    OnHealthChanged.Broadcast(Health, MaxHealth);
    GetOwner()->ForceNetUpdate();
}

bool UERAttributeComponent::SpendStamina(float Amount)
{
    if (!GetOwner() || !GetOwner()->HasAuthority() || Amount < 0.0f || Stamina < Amount) return false;
    Stamina = FMath::Clamp(Stamina - Amount, 0.0f, MaxStamina);
    OnStaminaChanged.Broadcast(Stamina, MaxStamina);
    GetOwner()->ForceNetUpdate();
    return true;
}

float UERAttributeComponent::GetHealthPercent() const
{
    return MaxHealth > 0.0f ? FMath::Clamp(Health / MaxHealth, 0.0f, 1.0f) : 0.0f;
}

void UERAttributeComponent::OnRep_Health() { OnHealthChanged.Broadcast(Health, MaxHealth); }
void UERAttributeComponent::OnRep_Stamina() { OnStaminaChanged.Broadcast(Stamina, MaxStamina); }

void UERAttributeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(UERAttributeComponent, Health);
    DOREPLIFETIME(UERAttributeComponent, Stamina);
}
