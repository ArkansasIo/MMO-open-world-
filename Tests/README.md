# Etherroad test plan

## C++ / Unreal automation tests
- Attribute damage clamps at zero; healing clamps at maximum; invalid values are rejected.
- Inventory rejects client-side mutation, invalid item IDs, nonpositive quantities and removal beyond available quantity.
- Quest acceptance rejects duplicate quests; objective counts clamp to the requirement; only server-authoritative events advance progress.
- Region seed generation is deterministic for identical inputs and changes when a seed or generator version changes.

## Backend integration tests
- Health endpoint returns service status.
- Realm discovery returns schema-valid results.
- Session endpoint rejects malformed requests and returns 503 until a real allocator and signer are configured.
- Economy tests should verify atomic transfer, idempotent retries, nonnegative balances, and rollback on failure.

## Multiplayer and scale tests
- Test dedicated-server startup, join/leave, reconnect, replication, packet loss, and process failure.
- Measure players per process, server frame time, CPU, memory, network throughput, persistence latency and recovery time.
- Do not claim target concurrency until repeated load and failure tests support it.
