# Attributes and combat Blueprint implementation guide

Attach `UERAttributeComponent` to player and enemy character Blueprints. Configure maximum health/stamina through approved class data. Bind `OnHealthChanged` and `OnStaminaChanged` to UI events.

## Combat ability flow
1. Enhanced Input captures an ability intent.
2. Client sends intent to an authoritative server RPC on a replicated gameplay actor/component.
3. Server validates player state, target, range, line of sight, cooldown, resource costs, and ability eligibility.
4. Server applies gameplay effects and records combat telemetry.
5. Replicated state and presentation cues update clients.

## Required before production
Cooldown and resource-cost model; damage types, resistance, mitigation, block, critical chance, threat and death state; server-side target validation and rate limits; combat logs and anti-cheat telemetry; reconnect-safe state; and tests for invalid requests and concurrent combat.
