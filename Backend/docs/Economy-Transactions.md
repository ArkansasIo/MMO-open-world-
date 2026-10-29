# Economy transaction contract

The API must not accept a client-selected account ID as proof of ownership. Resolve the authenticated account from a verified session/token first; the current session endpoint intentionally does not issue sessions.

## Required transaction properties
- Use a PostgreSQL transaction for balance changes and the corresponding ledger row.
- Lock the currency account row with SELECT ... FOR UPDATE, or use an atomic conditional UPDATE that cannot make a balance negative.
- Require a caller-generated idempotency key scoped to the authenticated principal and operation.
- Store both debit and credit ledger entries for transfers; enforce conservation of value.
- Validate positive integer amounts, currency type, transfer permissions, and account status.
- Record an audit event and commit all related writes atomically.
- Apply per-account and per-IP rate limits, authorization checks, and operational alerts.

## Suggested API boundary
POST /v1/economy/transfer should accept recipient character/account reference, currency code, positive amount, and idempotency key. The server resolves the sender from authentication. The route must return the prior result for a repeated idempotency key and reject a key reused with a different payload.

## Current status
This document is a contract only. No public economy mutation endpoint is enabled until authentication, idempotency storage, transaction handling, and integration tests are implemented.
