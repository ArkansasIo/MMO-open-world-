#include "ERGameModeBase.h"
#include "ERPlayerCharacter.h"

AERGameModeBase::AERGameModeBase()
{
    DefaultPawnClass = AERPlayerCharacter::StaticClass();
}
