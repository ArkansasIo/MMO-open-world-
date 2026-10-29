# Required gameplay checks

These checks are proposed coverage, not executed test results.

## Unreal gameplay
- Ability target outside configured range is rejected.
- Cooldown prevents duplicate ability use before the allowed time.
- Invalid item IDs and non-positive quantities are rejected.
- Removing more items than owned leaves inventory unchanged.
- A full inventory does not consume a resource node.
- Concurrent gathers cannot extract more than the node's remaining quantity.
- A partially full inventory leaves untransferred loot in the container.
- Equipment slot replacement results in one entry for that slot.
- XP grants crossing multiple thresholds set the correct final level.
- Interaction target validity and range are checked by the server.

## Backend
- Repeated idempotency key and identical request return the recorded result.
- Reusing an idempotency key with a different request hash is rejected.
- Stale character save version does not overwrite a newer snapshot.
- Expired or previously redeemed join ticket is rejected.
- Economy debit cannot make a balance negative under concurrent requests.
- Session allocator never assigns a server beyond its configured capacity.

## Execution requirements
Run automation tests in the target Unreal Engine 5.7 environment and backend integration tests against disposable PostgreSQL. Record actual logs and test results in CI; never infer a pass from a source file existing.
