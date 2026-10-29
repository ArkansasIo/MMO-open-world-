# Etherroad MMO

Etherroad is an original open-world MMORPG prototype targeting Unreal Engine 5.7. This repository contains an Unreal project, C++ gameplay foundation, an EtherroadCore plugin, an editor asset-shell generator, starter data catalogs, a TypeScript/Fastify control-plane scaffold, PostgreSQL schema, Docker Compose configuration, CI metadata checks, and implementation documentation.

> **Build status:** source files have been committed, but Unreal compilation and editor-generated Blueprint assets have not been verified in an installed Unreal Engine 5.7 environment. This is a development scaffold, not a production-ready MMO.

## Gameplay foundations

- Replicated player character and starter game mode.
- Replicated inventory, attributes, equipment, XP progression, quest progress, combat abilities, and interaction components.
- Data Asset-based ability definitions with server-side range/cooldown checks and damage routed to supported target health systems.
- Replicated enemy character and resource node native classes for Blueprint extension.
- Editor Python script creates starter Blueprint and Widget Blueprint shells, including native enemy/resource parents.
- Starter CSV catalogs for items, regions, and quests.
- Fastify health and realm-discovery endpoints. Session allocation intentionally returns HTTP 503 until identity verification, capacity-aware allocation, leases/fencing, and signed one-time tickets are implemented.
- PostgreSQL initial schema, Docker Compose, architecture notes, Blueprint graph guides, and CI metadata/syntax checks.

## Repository layout

```text
Etherroad.uproject
Config/
Content/Data/{Items,Regions,Quests}/
Plugins/EtherroadCore/Source/ERCore/
Source/{Etherroad,EtherroadEditor}/
Backend/{src,migrations}/
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
- [Backend economy transaction contract](Backend/docs/Economy-Transactions.md)
- [Test plan](Tests/README.md)

## Important implementation limits

The current code is a starter foundation. Unreal C++ compilation, generated Blueprint assets, multiplayer contention tests, backend integration tests, and production deployment have not been verified. Ability stamina cost, full loot/reward attribution, AI behavior trees, item ownership validation, persistence, authentication, and production session allocation remain incomplete.

## License

No license has been selected. Do not assume reuse permissions until a license is added.
