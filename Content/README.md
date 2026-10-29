# Unreal content layout

Create and save these assets in Unreal Editor; do not fabricate text files with a `.uasset` extension.

- `Blueprints/Characters`: player, enemy and NPC Blueprint subclasses.
- `Blueprints/AI`: AI controllers, Behavior Trees and Blackboard assets.
- `Blueprints/Combat`: ability actors, projectiles and combat effects.
- `Blueprints/World`: interactables, portals, gathering nodes and region actors.
- `Blueprints/UI`: HUD and menu Widget Blueprints.
- `Data/Items`, `Data/Abilities`, `Data/Classes`, `Data/Quests`, `Data/Enemies`, `Data/Biomes`: DataAssets/DataTables.
- `Maps/Startup`, `Maps/Prototype`, `Maps/World`: startup, vertical-slice and streamed maps.

Use the editor Python API to create asset shells and then validate, configure, save and test them in the editor.
