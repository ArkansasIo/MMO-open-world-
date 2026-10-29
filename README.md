# Etherroad MMO

Etherroad is an original open-world MMORPG project targeting Unreal Engine 5.7, with a Blueprint-first gameplay workflow backed by reusable C++ systems.

> **Repository status:** This repository was empty when inspected. This commit initializes the project documentation and architecture baseline; it does not yet contain a compiled Unreal project or finished Blueprint `.uasset` assets.

## Project goals

- A persistent open world built from authored landmarks and deterministic procedural regions.
- A modular Unreal Engine C++ plugin with Blueprint-extensible gameplay systems.
- Server-authoritative combat, inventory, trading, progression, and world state.
- Data-driven classes, abilities, items, quests, enemies, biomes, dungeons, and events.
- A separate MMO control plane for identity, realm discovery, session allocation, persistence, and operations.
- PC-first development, with console support only after platform SDK access and certification.

## Planned repository layout

```text
Etherroad/
├── Etherroad.uproject
├── Config/
├── Content/
│   ├── Blueprints/{Characters,AI,Combat,Inventory,Quests,World,UI}
│   ├── Data/{Items,Abilities,Classes,Quests,Enemies,Biomes,Regions}
│   ├── Maps/{Startup,Prototype,World}
│   └── UI/{HUD,Menus,Widgets}
├── Plugins/EtherroadCore/
│   ├── EtherroadCore.uplugin
│   └── Source/
│       ├── ERCore/
│       ├── ERGameplay/
│       ├── ERCombat/
│       ├── ERInventory/
│       ├── ERQuest/
│       ├── ERWorld/
│       ├── ERGeneration/
│       ├── ERNetworking/
│       └── EREditor/
├── Source/{Etherroad,EtherroadEditor,EtherroadServer}/
├── Backend/
│   ├── services/{identity,realms,sessions,persistence}
│   ├── migrations/
│   └── tests/
├── Scripts/Editor/
├── Tests/{Unit,Integration,Load}/
└── Docs/
```

## Development principles

1. **Server authority:** clients submit intents; the server validates outcomes.
2. **Transactional economy:** item transfers and currency movements must be atomic and auditable.
3. **Deterministic generation:** persist the realm/region seed, generator version, and content-manifest version.
4. **Bounded simulation:** use World Partition and region/server processes; do not attempt to simulate an entire planet in one Unreal process.
5. **Capacity measured, not assumed:** large concurrency goals require staged load tests and failure tests.
6. **Secrets stay out of source:** use environment variables or a secrets manager; commit only safe example configuration.

## Getting started

The full Unreal project must be added before it can be opened in Unreal Editor. Once present:

1. Install Unreal Engine 5.7 and the matching C++ toolchain.
2. Generate project files from `Etherroad.uproject`.
3. Build the Editor target.
4. Run asset-generation scripts inside the Unreal Editor, then save and validate generated assets.
5. Run backend unit/integration tests and dedicated-server smoke tests before deployment.

## Scope and non-goals

This repository is an original game project, not a copy of the code, maps, or assets of another commercial MMORPG. References to other games are design comparisons only. A million concurrent players is a long-term capacity target, not a validated capacity claim.

## Documentation

- [Architecture baseline](Docs/Architecture.md)
- [Implementation roadmap](Docs/ROADMAP.md)
- [Security and validation principles](Docs/SECURITY.md)

## License

No license has been selected yet. Until a license is added, do not assume that this repository grants permission to reuse its contents.
