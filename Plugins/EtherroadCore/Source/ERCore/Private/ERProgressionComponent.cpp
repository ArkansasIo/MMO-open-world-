#include "ERProgressionComponent.h"
#include "Net/UnrealNetwork.h"

UERProgressionComponent::UERProgressionComponent() { SetIsReplicatedByDefault(true); }

int64 UERProgressionComponent::GetXPForNextLevel() const
{
    if (Level >= MaxLevel) return 0;
    const double Raw = FMath::Pow(static_cast<double>(Level), FMath::Max(1.0f, XPExponent)) * FMath::Max(1.0f, XPMultiplier);
    return FMath::Max<int64>(1, static_cast<int64>(FMath::CeilToDouble(Raw)));
}

int64 UERProgressionComponent::GetXPWithinCurrentLevel() const
{
    const int64 Threshold = Level <= 1 ? 0 : static_cast<int64>(
        FMath::Pow(static_cast<double>(Level - 1), FMath::Max(1.0f, XPExponent)) * FMath::Max(1.0f, XPMultiplier));
    return FMath::Max<int64>(0, TotalXP - Threshold);
}

void UERProgressionComponent::GrantXP(int64 Amount)
{
    if (!GetOwner() || !GetOwner()->HasAuthority() || Amount <= 0 || Level >= MaxLevel) return;
    const int32 OldLevel = Level;
    TotalXP = FMath::Max<int64>(0, TotalXP + Amount);
    while (Level < MaxLevel)
    {
        const int64 Threshold = static_cast<int64>(
            FMath::CeilToDouble(FMath::Pow(static_cast<double>(Level), FMath::Max(1.0f, XPExponent)) * FMath::Max(1.0f, XPMultiplier)));
        if (TotalXP < Threshold) break;
        ++Level;
    }
    if (Level != OldLevel) OnLevelChanged.Broadcast(OldLevel, Level, TotalXP);
}

void UERProgressionComponent::OnRep_Progression() { OnLevelChanged.Broadcast(Level, Level, TotalXP); }
void UERProgressionComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(UERProgressionComponent, Level);
    DOREPLIFETIME(UERProgressionComponent, TotalXP);
}
