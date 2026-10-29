# Unreal source modules

Planned Unreal targets: `Etherroad`, `EtherroadEditor`, and `EtherroadServer`.

Planned responsibilities:
- `ERCore`: shared types, identifiers, tags, logging and interfaces.
- `ERGameplay`: attributes, progression and character state.
- `ERCombat`: server-authoritative combat and abilities.
- `ERInventory`: item instances, inventory, equipment and loot.
- `ERQuest`: objectives, dialogue and quest progression.
- `ERWorld`: region identity, world state and streaming integration.
- `ERGeneration`: deterministic procedural generation.
- `ERNetworking`: client/server gameplay transport and session integration.
- `EREditor`: editor-only validation and asset generation tools.

This file records the intended module map; the C++ implementation and Build.cs files still need to be added.
