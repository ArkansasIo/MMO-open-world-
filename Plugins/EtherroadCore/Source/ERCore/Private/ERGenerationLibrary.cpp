#include "ERGenerationLibrary.h"

int32 UERGenerationLibrary::MakeRegionSeed(FName RealmId, FName RegionId, int32 WorldSeed, int32 GeneratorVersion)
{
    // Stable inputs are explicit; changing the hash algorithm requires a generator-version bump.
    uint32 Hash = GetTypeHash(RealmId);
    Hash = HashCombine(Hash, GetTypeHash(RegionId));
    Hash = HashCombine(Hash, GetTypeHash(WorldSeed));
    Hash = HashCombine(Hash, GetTypeHash(GeneratorVersion));
    return static_cast<int32>(Hash & 0x7fffffff);
}

float UERGenerationLibrary::StableNoise01(int32 Seed, int32 X, int32 Y)
{
    uint32 Hash = GetTypeHash(Seed);
    Hash = HashCombine(Hash, GetTypeHash(X));
    Hash = HashCombine(Hash, GetTypeHash(Y));
    const uint32 Positive = Hash & 0x00FFFFFFu;
    return static_cast<float>(Positive) / static_cast<float>(0x00FFFFFFu);
}
