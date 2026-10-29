# MMO backend

Backend services are separate from Unreal's real-time gameplay replication.

Planned services:
- Identity and account recovery.
- Realm directory and health registry.
- Session allocator and signed, one-time join tickets.
- Character persistence and reconnect recovery.
- Transactional economy operations and audit records.
- Metrics, administration, moderation and operational tooling.

Production requirements: validated authentication, schema migrations, transaction boundaries, idempotency keys, rate limits, secrets management, integration tests, backup/restore drills, and monitoring. No production service should be considered complete from a route stub alone.
