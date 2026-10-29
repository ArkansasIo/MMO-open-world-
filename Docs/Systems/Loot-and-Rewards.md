# Loot and Rewards

## Loot table assets
Create a UERLootTableDefinition Data Asset. Each entry defines item ID, drop chance, and quantity bounds. RollLootIds uses an explicit seed so the same seed and unchanged asset data produce repeatable results within the same engine/runtime implementation.

## Loot containers
AERLootContainer is a replicated interactable holding item stacks. Its interaction transfers items through the server-side inventory component. If the inventory cannot accept the next stack, remaining stacks are retained in the container.

## Production requirements
- Generate loot on the server only, using a seed derived from a server-controlled encounter/loot identity.
- Never accept client-selected drop results or seeds.
- Persist loot grants and inventory changes atomically; retries must be idempotent.
- Add ownership/party eligibility, expiry, despawn, instanced loot, and anti-duplication locks.
- Add max-stack and weight/capacity validation before enabling large loot tables.
- Tie XP rewards to verified contribution/kill attribution and protect reward grants against duplicate death events.

## Current limits
The loot table is not yet wired into enemy death events. The loot container is a generic transfer actor, not a persistent MMO loot service. Unreal compilation and multiplayer tests remain required.
