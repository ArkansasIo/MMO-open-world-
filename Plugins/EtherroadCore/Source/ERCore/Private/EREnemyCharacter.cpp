#include "EREnemyCharacter.h"
#include "ERAttributeComponent.h"

AEREnemyCharacter::AEREnemyCharacter()
{
    bReplicates = true;
    SetReplicateMovement(true);
    AttributesComponent = CreateDefaultSubobject<UERAttributeComponent>(TEXT("AttributesComponent"));
}
