# Etherroad MMO

Etherroad is an original open-world MMORPG prototype targeting Unreal Engine 5.7. This repository now contains a starter Unreal project, C++ gameplay foundation, an `EtherroadCore` plugin, an editor asset-shell generator, starter data catalogs, a TypeScript/Fastify control-plane scaffold, PostgreSQL schema, Docker Compose configuration, and implementation documentation.

> **Build status:** files have been committed to GitHub, but Unreal compilation and editor-generated Blueprint assets have not yet been verified in an installed Unreal Engine 5.7 environment. Treat this as a source foundation, not a production-ready MMO.

## Current source foundation

- `Etherroad.uproject`, game/editor/server targets, module build rules, and plugin descriptor.
- Replicated player health foundation and game mode.
- Core item definitions, replicated inventory component, replicated attribute component, quest definition/progress component, interactable interface, region definition, and deterministic seed helpers.
- Unreal Editor Python script to create starter Blueprint and Widget Blueprint shells.
- Item, region, and quest CSV catalogs.
- Fastify health and realm-discovery endpoints; session allocation deliberately fails closed with HTTP 503 until real identity verification, capacity-aware allocation, leases/fencing, and signed one-time tickets are implemented.
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
Docs/BlueprintGraphs/
Tests/
.github/workflows/
```

## Start developing

1. Install Unreal Engine 5.7 and its matching C++ toolchain.
2. Clone this repository and open `Etherroad.uproject`.
3. Generate project files and build the `EtherroadEditor` target.
4. Enable Unreal's Python Editor Script Plugin and run `Scripts/Editor/CreateEtherroadAssets.py`.
5. Open each generated asset, wire and validate its graphs/layout, then save it in the editor.
6. Start the local backend with Docker Compose from `Backend/` or run the Node service directly.

## Architecture rules

- The client is untrusted; the server owns combat, loot, inventory, quest progress, and currency.
- Unreal native networking handles real-time gameplay; HTTP is for control-plane operations.
- Durable economy changes require database transactions, idempotency, and audit records.
- Procedural regions use explicit realm/region/seed/generator/content-manifest identities.
- A logical planet is not one server process. Use World Partition and bounded region simulation.
- Million-concurrent-player capacity is a target that requires measured load and failure testing.

## Key documents

- [Architecture](Docs/Architecture.md)
- [Implementation roadmap](Docs/ROADMAP.md)
- [Security baseline](Docs/SECURITY.md)
- [Blueprint asset inventory](Docs/BlueprintGraphs/BlueprintAssetInventory.md)
- [World generation contract](Docs/WorldGeneration.md)
- [Test plan](Tests/README.md)

## License

No license has been selected. Do not assume reuse permissions until a license is added.
