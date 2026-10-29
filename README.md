# Etherroad MMO

Etherroad is an original open-world MMORPG prototype targeting Unreal Engine 5.7. This repository contains an Unreal project, C++ gameplay foundation, an EtherroadCore plugin, an editor asset-shell generator, starter data catalogs, a TypeScript/Fastify control-plane scaffold, PostgreSQL schema, Docker Compose configuration, CI metadata checks, and implementation documentation.

> **Build status:** source files have been committed, but Unreal compilation and editor-generated Blueprint assets have not been verified in an installed Unreal Engine 5.7 environment. This is a development scaffold, not a production-ready MMO.

## Gameplay foundations

- Replicated player character with combat, inventory, equipment, interaction, progression, and quest components.
- Data Asset-based combat abilities with server-side range/cooldown checks and damage routing.
- Replicated enemy, resource node, and loot-container native classes for Blueprint extension.
- Seeded loot-table Data Assets and a server-side loot-container transfer flow.
- Editor Python script creates starter Blueprint and Widget Blueprint shells, including native enemy, resource, and loot-container parents.
- Starter CSV catalogs for items, regions, and quests.
- Fastify health and realm-discovery endpoints. Session allocation intentionally returns HTTP 503 until identity verification, capacity-aware allocation, leases/fencing, and signed one-time tickets are implemented.
- PostgreSQL starter schema plus follow-on idempotency, character-save version, game-server process, and join-ticket tables.

## Repository layout

```text
Etherroad.uproject
Config/
Content/Data/{Items,Regions,Quests}/
Plugins/EtherroadCore/Source/ERCore/
Source/{Etherroad,EtherroadEditor}/
Backend/{src,migrations,docs}/
Scripts/Editor/
Docs/
Tests/
.github/workflows/
```

## Start developing

1. Install Unreal Engine 5.7 and its matching C++ toolchain.
2. Clone this repository and open Etherroad.uproject.
3. Generate project files and build the EtherroadEditor target.
4. Enable Unreal's Python Editor Script Plugin and run Scripts/Editor/CreateEtherroadAssets.py.
5. Open generated assets, wire and validate their graphs/layouts, then save them in the editor.
6. Start the local backend with Docker Compose from Backend/ or run the Node service directly.
7. Apply SQL migrations through a migration runner in development; review and test them before any production use.

## Architecture rules

- The client is untrusted; the server owns combat, loot, inventory, quest progress, and currency.
- Unreal native networking handles real-time gameplay replication; HTTP is for control-plane operations.
- Durable economy changes require database transactions, idempotency, and audit records.
- Procedural regions use explicit realm/region/seed/generator/content-manifest identities.
- A logical planet is not one server process. Use World Partition and bounded region simulation.
- Million-concurrent-player capacity is a target requiring measured load, capacity planning, and failure testing.

## Documentation

- [Architecture](Docs/Architecture.md)
- [Implementation roadmap](Docs/ROADMAP.md)
- [Security baseline](Docs/SECURITY.md)
- [Blueprint asset inventory](Docs/BlueprintGraphs/BlueprintAssetInventory.md)
- [World generation contract](Docs/WorldGeneration.md)
- [Combat, equipment, and progression](Docs/Systems/Combat-Equipment-Progression.md)
- [World interaction and AI](Docs/Systems/World-Interaction-and-AI.md)
- [Loot and rewards](Docs/Systems/Loot-and-Rewards.md)
- [Quest rewards and persistence](Docs/Systems/Quest-Rewards-and-Persistence.md)
- [Backend economy transaction contract](Backend/docs/Economy-Transactions.md)
- [Character persistence contract](Backend/docs/Character-Persistence.md)
- [Required gameplay checks](Tests/Required-Gameplay-Checks.md)

## Important implementation limits

The current code is a starter foundation. Unreal C++ compilation, generated Blueprint assets, multiplayer contention tests, backend integration tests, and production deployment have not been verified. Ability stamina cost, complete AI behavior trees, persistent loot/reward attribution, item ownership validation, save/load APIs, authentication, and production session allocation remain incomplete.

## License

No license has been selected. Do not assume reuse permissions until a license is added.
