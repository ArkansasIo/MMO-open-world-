#include "ERLootTableDefinition.h"
#include "Math/RandomStream.h"

TArray<FName> UERLootTableDefinition::RollLootIds(TArray<int32>& OutQuantities, int32 Seed) const
{
    TArray<FName> Result;
    OutQuantities.Reset();
    if (Entries.IsEmpty() || Rolls <= 0) return Result;

    FRandomStream Random(Seed);
    for (int32 RollIndex = 0; RollIndex < Rolls; ++RollIndex)
    {
        const FERLootEntry& Entry = Entries[Random.RandRange(0, Entries.Num() - 1)];
        if (Entry.ItemId.IsNone() || Random.FRand() > FMath::Clamp(Entry.DropChance, 0.0f, 1.0f)) continue;
        Result.Add(Entry.ItemId);
        const int32 MinQty = FMath::Max(1, Entry.MinQuantity);
        const int32 MaxQty = FMath::Max(MinQty, Entry.MaxQuantity);
        OutQuantities.Add(Random.RandRange(MinQty, MaxQty));
    }
    return Result;
}
