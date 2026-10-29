-- Additional control-plane primitives. Authentication/session issuance is not implemented yet.
CREATE TABLE IF NOT EXISTS character_save_versions (
  character_id UUID PRIMARY KEY REFERENCES characters(character_id) ON DELETE CASCADE,
  version BIGINT NOT NULL DEFAULT 0 CHECK (version >= 0),
  schema_version INTEGER NOT NULL DEFAULT 1 CHECK (schema_version >= 1),
  updated_at TIMESTAMPTZ NOT NULL DEFAULT now()
);

CREATE TABLE IF NOT EXISTS idempotency_records (
  principal_id TEXT NOT NULL,
  operation TEXT NOT NULL,
  idempotency_key TEXT NOT NULL,
  request_hash TEXT NOT NULL,
  response_status INTEGER,
  response_body JSONB,
  state TEXT NOT NULL DEFAULT 'pending' CHECK (state IN ('pending','completed','failed')),
  created_at TIMESTAMPTZ NOT NULL DEFAULT now(),
  expires_at TIMESTAMPTZ NOT NULL DEFAULT (now() + interval '7 days'),
  PRIMARY KEY (principal_id, operation, idempotency_key)
);

CREATE INDEX IF NOT EXISTS idx_idempotency_expiry ON idempotency_records(expires_at);

CREATE TABLE IF NOT EXISTS game_server_processes (
  process_id TEXT PRIMARY KEY,
  realm_id TEXT NOT NULL REFERENCES realms(realm_id),
  region_code TEXT NOT NULL,
  endpoint TEXT NOT NULL,
  capacity_limit INTEGER NOT NULL CHECK (capacity_limit > 0),
  current_players INTEGER NOT NULL DEFAULT 0 CHECK (current_players >= 0),
  status TEXT NOT NULL DEFAULT 'starting' CHECK (status IN ('starting','ready','draining','offline')),
  lease_owner TEXT,
  lease_expires_at TIMESTAMPTZ,
  heartbeat_at TIMESTAMPTZ,
  updated_at TIMESTAMPTZ NOT NULL DEFAULT now()
);

CREATE INDEX IF NOT EXISTS idx_game_server_selection
  ON game_server_processes(realm_id, status, current_players, capacity_limit);

-- Session tickets should be stored hashed, expire quickly, and be consumed exactly once.
CREATE TABLE IF NOT EXISTS join_ticket_redemptions (
  ticket_hash TEXT PRIMARY KEY,
  account_id UUID NOT NULL REFERENCES accounts(account_id),
  character_id UUID NOT NULL REFERENCES characters(character_id),
  process_id TEXT NOT NULL REFERENCES game_server_processes(process_id),
  expires_at TIMESTAMPTZ NOT NULL,
  redeemed_at TIMESTAMPTZ,
  created_at TIMESTAMPTZ NOT NULL DEFAULT now()
);

CREATE INDEX IF NOT EXISTS idx_join_ticket_expiry ON join_ticket_redemptions(expires_at);
