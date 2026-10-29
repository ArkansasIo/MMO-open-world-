# BP_ERPlayerCharacter — Blueprint graph specification

**Parent class:** `AERPlayerCharacter`

## Components
- Inherited Capsule Component and Character Movement Component.
- Inherited Mesh and camera rig as configured by the project.
- Optional interaction probe component (implement after interface and server validation are in place).

## Variables
- `MaxHealth` (float): defaults to 100; instance overrides should be restricted to approved data assets.
- `CurrentHealth` (float): replicated by the C++ parent.
- `HealthPercent` (pure function): use parent `GetHealthPercent`.

## Event graph
1. `Event BeginPlay` → initialize local presentation only. Do not grant rewards or trust client-side state here.
2. Bind `OnHealthChanged` → update health-bar presentation.
3. On local player only, bind input actions for movement, camera, interact, and abilities.
4. Interact input sends an interaction request to the server; the server validates range, target state, permissions, and cooldown before changing state.
5. Ability input sends an ability intent; server validates resource cost, cooldown, range, line of sight, and target eligibility before resolving effects.

## Important authority rules
- Never call `ApplyServerDamage` on a client and expect it to replicate. The server must call it.
- This class is a foundation only: it does not yet implement death, respawn, healing, damage types, threat, combat logs, anti-cheat, or persistence.
- Bind health UI through the event and avoid per-frame polling.
