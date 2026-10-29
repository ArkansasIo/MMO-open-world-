# Security and Validation Baseline

- Never trust client-reported damage, loot, currency, inventory, quest completion, cooldowns, or ownership.
- Store secrets in environment configuration or a managed secret store; never commit tokens, passwords, or private keys.
- Use a maintained authentication library and modern password hashing; do not implement cryptography manually.
- Require short-lived, audience-bound, signed, single-use session tickets.
- Add rate limits and replay protection to authentication, trade, mail, auction, and reward endpoints.
- Enforce authorization at every API and server boundary; audit privileged actions.
- Use database transactions and idempotency keys for economy changes.
- Validate and bound player names, chat, custom text, and uploaded content.
- Minimize personal data and define retention, deletion, and incident-response procedures.
- Test backup restoration, credential rotation, and recovery from region/server loss.
- Treat console account linking and distribution as platform-dependent integration work.
