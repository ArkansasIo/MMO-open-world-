# Etherroad Implementation Roadmap

## Phase 0 — Build foundation
- [ ] Add a valid Unreal Engine 5.7 `.uproject`, target files, module rules, plugin descriptor, and source modules.
- [ ] Add build, static-analysis, asset-validation, and test workflows.
- [ ] Establish content naming conventions and module boundaries.

## Phase 1 — Playable vertical slice
- [ ] Third-person character, Enhanced Input, camera, interaction interface.
- [ ] One settlement, one wilderness region, one dungeon.
- [ ] Server-authoritative movement and combat baseline.
- [ ] One class, three abilities, five enemies, loot and equipment.
- [ ] HUD, inventory, character panel, quest tracker, map, pause/settings menus.

## Phase 2 — Core RPG systems
- [ ] Attributes, progression, abilities and cooldowns.
- [ ] Inventory/equipment and item-instance persistence.
- [ ] Quest objectives, rewards, dialogue and NPC interaction.
- [ ] Crafting, gathering, vendors, currency ledger and atomic trading.
- [ ] Party, guild, chat, friends and moderation.

## Phase 3 — Persistent MMO services
- [ ] Identity and account recovery.
- [ ] Realm directory and server registry.
- [ ] Session allocator, signed one-time tickets, leases and fencing.
- [ ] Character persistence and reconnect/recovery.
- [ ] Admin tools, audit logs, metrics, alerts and incident runbooks.

## Phase 4 — World and content
- [ ] Deterministic region generator with versioned manifests.
- [ ] Biomes, geography, roads, settlements, factions and ecology.
- [ ] World Partition, streaming and region boundaries.
- [ ] Dungeons, raids, world bosses, dynamic events and endgame progression.
- [ ] Content validation and migration strategy.

## Phase 5 — Scale and release
- [ ] Dedicated-server packaging and deployment pipeline.
- [ ] Staged load and fault-injection tests.
- [ ] Backup/restore drills, anti-cheat controls, privacy and security review.
- [ ] Closed alpha, telemetry-based tuning, rollback and release operations.
- [ ] Console integration only with approved SDKs, platform services, and certification.

A checkbox is complete only after implementation, review, tests, and evidence. Documentation alone is not a finished feature.
