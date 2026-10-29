#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ERGameModeBase.generated.h"

/** Server-authoritative rules entry point for Etherroad maps. */
UCLASS(Blueprintable)
class ETHERROAD_API AERGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
    AERGameModeBase();
};
