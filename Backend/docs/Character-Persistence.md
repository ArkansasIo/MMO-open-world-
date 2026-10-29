# Character persistence contract

Character snapshots must be written by trusted game servers, not arbitrary clients. The current schema stores a state JSONB document as a flexible starter, but production persistence should use versioned schemas and explicit migration logic.

## Save contract
- Identify the character from a verified session, not a client-provided owner ID.
- Include character ID, realm ID, schema version, sequence/version, and server timestamp.
- Use optimistic concurrency (WHERE character_id = $1 AND version = $expected) or a per-character lease to reject stale writes.
- Write inventory, equipment, progression, quest state, and currency changes consistently.
- Use bounded save queues, retry with backoff, and dead-letter/alert on repeated failures.
- Define checkpoint frequency and recovery point objective; do not save every movement tick to PostgreSQL.
- Audit administrative edits and preserve rollback/recovery capability.

## API status
No public save/load route is implemented by this document. Implement authenticated server-to-server endpoints and integration tests before connecting persistence to gameplay.
