# Inventory component — Blueprint integration

**Native class:** `UERInventoryComponent`

## Setup
1. Add the component to the player character Blueprint.
2. Set `SlotCapacity` from a server-approved character or progression configuration.
3. Bind `OnInventoryChanged` to refresh the inventory widget.
4. Populate item definitions using `UERItemDefinition` DataAssets keyed by `ItemId`.

## Graphs
- Pickup request: client interacts with pickup → server validates distance and pickup availability → server grants item → server marks pickup consumed → replicated inventory refreshes UI.
- Remove item: server validates item ownership and quantity → removes quantity → emits inventory-changed event.
- UI refresh: enumerate replicated stacks and resolve display name/icon from local item-definition assets.

## Known prototype limitations
- Current stack model merges matching IDs without per-item max-stack enforcement.
- It has no item instance IDs, durability, binding, equipment slots, persistence, audit trail, trade locks, or atomic currency transaction.
- Do not use this prototype for production economy transactions until stack rules and persistence are implemented and tested.
