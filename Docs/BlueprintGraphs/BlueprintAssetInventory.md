# Blueprint asset inventory and implementation checklist

The editor script creates initial asset shells. Each item below must be opened, configured, wired, saved, and tested in Unreal Editor before it is considered implemented.

| Asset | Parent / type | Required graph or layout |
|---|---|---|
| `BP_PlayerCharacter` | `AERPlayerCharacter` | Enhanced Input, camera, interaction intent, ability intents, health event binding |
| `BP_EnemyCharacter` | `ACharacter` | AI controller, aggro, threat, attack telegraphs, server-side death/loot event |
| `BP_NPCCharacter` | `ACharacter` | dialogue interaction, shop/quest providers, faction state |
| `BP_ResourceNode` | `AActor` | server-side gather validation, depletion timer, respawn policy |
| `BP_LootContainer` | `AActor` | owner/eligibility checks, loot table, server-side open and claim |
| `WBP_HUD` | `UUserWidget` | health/stamina, target frame, action bar, quest tracker |
| `WBP_Inventory` | `UUserWidget` | slots, stack counts, sort/filter, item tooltip, server-authorized actions |
| `WBP_Character` | `UUserWidget` | attributes, equipment, resistances and derived-stat display |
| `WBP_QuestTracker` | `UUserWidget` | active objectives and authoritative progress updates |
| `WBP_WorldMap` | `UUserWidget` | player/party markers, region names, discovery state |
| `WBP_Login` | `UUserWidget` | authentication API calls, validation errors, rate-limit feedback |
| `WBP_CharacterCreation` | `UUserWidget` | name validation, class/race choices, server-side creation request |
| `WBP_Settings` | `UUserWidget` | graphics, audio, accessibility, key bindings and persistence |

## Graph conventions
- Prefix event dispatchers with `On`, functions with action verbs, and replicated server mutations with `Server` or an explicit server-authority comment.
- Use Gameplay Tags for cross-system categories rather than fragile display-name string comparisons.
- Keep presentation in Widgets and game rules in C++/server-authoritative gameplay components.
- Use DataAssets/DataTables for content values; do not hardcode every item or enemy in event graphs.
- Every networked mutation needs invalid-input handling and an automated test.
