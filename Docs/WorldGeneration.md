# World generation contract

Each region is identified by realm ID, region ID, world seed, generator version, and content-manifest version. The same versioned inputs should produce stable region identity and generation decisions.

## Pipeline
1. Resolve the immutable region definition and manifest.
2. Derive a deterministic region seed.
3. Generate macro terrain and biome masks.
4. Apply authored landmarks and protected navigation corridors.
5. Place settlements, roads, resources, encounter areas and spawn points using versioned rules.
6. Validate bounds, connectivity, collision, navmesh and content references.
7. Stream the region and persist player-created changes separately from generated baseline data.

## Invariants
- Do not regenerate player-mutated state from a seed.
- Bump generator version when generation behavior changes.
- Use bounded server simulation and Unreal World Partition; a whole planet is not one server process.
- Keep generated output reproducible in automated tests.
