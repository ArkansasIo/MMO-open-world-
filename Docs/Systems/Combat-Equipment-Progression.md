# Combat, Equipment, and Progression

This is the first C++ foundation for Etherroad MMO, not a finished MMO service.

## Combat
Create UERCombatAbilityDefinition Data Assets with a stable AbilityId, damage, stamina cost, cooldown, critical chance/multiplier, and range. Add UERCombatComponent to a character and call TryUseAbility from a server-validated input flow. Targets need UERAttributeComponent for damage to apply. The server validates target validity, self-targeting, range, and cooldown.

Current limitations: stamina cost is exposed but not charged; there is no line-of-sight test, team/faction check, damage resistance pipeline, client prediction, combat log, or ability animation. Add these before production use.

## Equipment
UEREquipmentComponent stores one item identifier per equipment slot and replicates the equipped-slot array. It does not validate item ownership or slot compatibility, consume inventory items, apply stat modifiers, or persist equipment.

## Progression
UERProgressionComponent stores total XP and level. Thresholds use ceil(level ^ XPExponent × XPMultiplier). Defaults are exponent 2 and multiplier 100. The server grants XP and advances levels; level and total XP replicate.

## Interaction
UERInteractionComponent uses the UERInteractableTarget interface. Server-side checks include range and interface support. Implement target-specific authorization, line of sight, rate limiting, and interaction-specific validation.

## Integration checklist
1. Add components to BP_PlayerCharacter and enemy/NPC base Blueprints.
2. Create ability Data Assets and item definition assets.
3. Bind Enhanced Input actions to interaction and ability requests.
4. Test cooldown boundaries, invalid targets, XP thresholds, and equipment slot replacement.
5. Compile with the exact Unreal Engine 5.7 toolchain and resolve API/generated-header differences.
6. Keep inventory, equipment, XP, and combat outcomes server-authoritative.
