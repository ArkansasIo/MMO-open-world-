#include "ERPlayerCharacter.h"
#include "Net/UnrealNetwork.h"
#include "ERCombatComponent.h"
#include "EREquipmentComponent.h"
#include "ERInventoryComponent.h"
#include "ERInteractionComponent.h"
#include "ERProgressionComponent.h"
#include "ERQuestComponent.h"

AERPlayerCharacter::AERPlayerCharacter()
{
    bReplicates = true;
    SetReplicateMovement(true);
    CombatComponent = CreateDefaultSubobject<UERCombatComponent>(TEXT("CombatComponent"));
    EquipmentComponent = CreateDefaultSubobject<UEREquipmentComponent>(TEXT("EquipmentComponent"));
    InventoryComponent = CreateDefaultSubobject<UERInventoryComponent>(TEXT("InventoryComponent"));
    InteractionComponent = CreateDefaultSubobject<UERInteractionComponent>(TEXT("InteractionComponent"));
    ProgressionComponent = CreateDefaultSubobject<UERProgressionComponent>(TEXT("ProgressionComponent"));
    QuestComponent = CreateDefaultSubobject<UERQuestComponent>(TEXT("QuestComponent"));
}

void AERPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();
    if (HasAuthority())
    {
        CurrentHealth = FMath::Clamp(CurrentHealth, 0.0f, MaxHealth);
    }
}

void AERPlayerCharacter::ApplyServerDamage(float DamageAmount)
{
    if (!HasAuthority() || DamageAmount <= 0.0f || CurrentHealth <= 0.0f) return;
    CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.0f, MaxHealth);
    OnHealthChanged.Broadcast(CurrentHealth, MaxHealth);
    ForceNetUpdate();
}

float AERPlayerCharacter::GetHealthPercent() const
{
    return MaxHealth > 0.0f ? FMath::Clamp(CurrentHealth / MaxHealth, 0.0f, 1.0f) : 0.0f;
}

void AERPlayerCharacter::OnRep_CurrentHealth()
{
    OnHealthChanged.Broadcast(CurrentHealth, MaxHealth);
}

void AERPlayerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AERPlayerCharacter, CurrentHealth);
}
