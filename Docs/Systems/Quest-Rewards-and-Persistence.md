# Quest rewards and persistence

## Quest completion
The current quest component tracks objective progress and status, but reward delivery is not implemented. Completion must be a server-side transition that occurs once. A completed quest should not be able to grant rewards again after reconnect, retry, duplicate objective events, or simultaneous requests.

## Reward transaction
1. Validate that the quest is active and all required objectives are complete.
2. Lock or version-check the character quest state.
3. Record the completion idempotency key.
4. Apply XP, currency, and item rewards within a consistent transaction boundary.
5. Write audit/ledger records and commit.
6. Replicate the updated quest state and show a UI notification only after authoritative success.

For rewards spanning PostgreSQL and an Unreal dedicated server, use a durable outbox/inbox or an equivalent retry-safe protocol; do not assume a database transaction can atomically commit a remote gameplay RPC.

## Persistence model
Store versioned character snapshots with optimistic concurrency or a character lease. Persist progression, inventory, equipment, quest state, and economy references together where consistency requires it. Do not use client-originated snapshots as authoritative state.

## Current status
This document specifies the integration contract. Quest reward grants, save/load API routes, and cross-service transaction orchestration are not implemented yet.
