# Quest system Blueprint implementation guide

Use `UERQuestDefinition` DataAssets to define quest IDs, titles, descriptions, objective IDs, counts and rewards. Add `UERQuestComponent` to the player state or another actor whose lifetime matches the player's persistent quest state.

## Acceptance flow
- Server validates that the quest is available and prerequisites are met.
- `StartQuest` initializes objective progress.
- Authoritative gameplay events call `AddObjectiveProgress` after validating the event source and actor eligibility.
- `OnQuestUpdated` refreshes the quest tracker.
- Completion must trigger a separate idempotent reward transaction; the current prototype only marks objectives and status complete.

## Required before production
Prerequisites, repeatable quests, abandonment policy, objective event routing, reward idempotency, persistence, migration, localization, and exploit tests.
