# Etherroad Architecture Baseline

## 1. Runtime topology

- Unreal client: rendering, input, prediction where appropriate, UI, and local presentation.
- Unreal dedicated-server processes: authoritative simulation for bounded world regions or gameplay instances.
- Control plane: account/session authentication, realm discovery, session allocation, server registration, leases, handoff tickets, and operational controls.
- Persistence services: durable character, inventory, quest, guild, and economy state.
- Data/asset delivery: immutable game assets and versioned content manifests.

Use Unreal's native networking for real-time actor replication. Use HTTP APIs for control-plane operations rather than sending high-frequency movement or combat traffic through REST.

## 2. Authority and trust boundaries

Clients are untrusted. Server code validates movement constraints, ability cooldowns, range, line of sight, inventory ownership, loot eligibility, currency balances, and all trading operations. Client UI must not be the source of truth for damage, loot, or currency.

## 3. Region identity and generation

Every generated region should be identified by:

`realm_id + region_id + seed + generator_version + content_manifest_version`

Generation must be deterministic for a given identity. Persist changes that players make; do not regenerate mutated player state from the seed.

## 4. Handoff and session safety

A session allocator should:
1. Authenticate the account and character.
2. Find a healthy target process with sufficient capacity.
3. issue a short-lived, signed, single-use join ticket.
4. Use process leases and fencing tokens to prevent stale processes from writing authoritative state.
5. Transfer character state safely and record the handoff.
6. Reject expired, replayed, mismatched, or already-consumed tickets.

The allocator and ticket signer are production-critical services, not implemented merely by adding an endpoint placeholder.

## 5. Persistence rules

- Use database transactions for inventory moves, currency transfers, auction settlement, and trade completion.
- Add idempotency keys to retryable economy operations.
- Maintain audit records for privileged actions and economy mutations.
- Use versioned migrations and tested restore procedures.
- Replication is not a backup; backups must be independently recoverable.

## 6. World rendering and streaming

Use World Partition and level/asset streaming for world presentation. Split simulation into bounded server workloads. A logical planet is a world-design abstraction, not one process and not a storage-volume sizing formula.

## 7. Testing gates

- Unit: formulas, inventory invariants, ability rules, deterministic generation.
- Integration: authentication, character persistence, session tickets, region handoff, database transactions.
- Multiplayer: replication, reconnects, packet loss, latency, authority checks.
- Load: players per process, CPU, memory, network bandwidth, database throughput, and recovery after process failure.
- Security: replayed tickets, forged client state, duplication exploits, rate limiting, and privilege boundaries.

No target concurrency number should be treated as achieved until repeatable load and failure tests demonstrate it.
