"""Idempotently create Etherroad starter Blueprint and Widget Blueprint assets.

Run inside Unreal Editor with the Python Editor Script Plugin enabled after compiling
the EtherroadEditor target. This creates asset shells only; configure and validate
graphs, UI, materials, collision, animation, and data assets in the editor.
"""
import unreal

ROOT = "/Game/Etherroad"


def ensure_folder(path):
    if not unreal.EditorAssetLibrary.does_directory_exist(path):
        unreal.EditorAssetLibrary.make_directory(path)


def ensure_blueprint(name, folder, parent_class):
    ensure_folder(folder)
    asset_path = f"{folder}/{name}"
    if unreal.EditorAssetLibrary.does_asset_exist(asset_path):
        unreal.log(f"[Etherroad] Exists: {asset_path}")
        return unreal.load_asset(asset_path)

    factory = unreal.BlueprintFactory()
    factory.set_editor_property("parent_class", parent_class)
    asset_tools = unreal.AssetToolsHelpers.get_asset_tools()
    asset = asset_tools.create_asset(name, folder, unreal.Blueprint, factory)
    if asset:
        unreal.EditorAssetLibrary.save_loaded_asset(asset)
        unreal.log(f"[Etherroad] Created Blueprint: {asset_path}")
    else:
        unreal.log_error(f"[Etherroad] Failed to create: {asset_path}")
    return asset


def ensure_widget(name, folder):
    ensure_folder(folder)
    asset_path = f"{folder}/{name}"
    if unreal.EditorAssetLibrary.does_asset_exist(asset_path):
        unreal.log(f"[Etherroad] Exists: {asset_path}")
        return unreal.load_asset(asset_path)

    factory = unreal.WidgetBlueprintFactory()
    factory.set_editor_property("parent_class", unreal.UserWidget)
    asset_tools = unreal.AssetToolsHelpers.get_asset_tools()
    asset = asset_tools.create_asset(name, folder, unreal.WidgetBlueprint, factory)
    if asset:
        unreal.EditorAssetLibrary.save_loaded_asset(asset)
        unreal.log(f"[Etherroad] Created Widget Blueprint: {asset_path}")
    else:
        unreal.log_error(f"[Etherroad] Failed to create widget: {asset_path}")
    return asset


def main():
    player_class = unreal.load_class(None, "/Script/Etherroad.ERPlayerCharacter")
    enemy_class = unreal.load_class(None, "/Script/ERCore.EREnemyCharacter")
    resource_class = unreal.load_class(None, "/Script/ERCore.ERResourceNode")
    loot_class = unreal.load_class(None, "/Script/ERCore.ERLootContainer")
    character_class = unreal.load_class(None, "/Script/Engine.Character")
    actor_class = unreal.load_class(None, "/Script/Engine.Actor")

    if not player_class:
        raise RuntimeError("ERPlayerCharacter was not found. Compile the EtherroadEditor target first.")
    if not enemy_class or not resource_class or not loot_class:
        raise RuntimeError("ERCore enemy, resource, or loot classes were not found. Compile the ERCore plugin first.")

    ensure_blueprint("BP_PlayerCharacter", f"{ROOT}/Blueprints/Characters", player_class)
    ensure_blueprint("BP_EnemyCharacter", f"{ROOT}/Blueprints/Characters", enemy_class)
    ensure_blueprint("BP_NPCCharacter", f"{ROOT}/Blueprints/Characters", character_class)
    ensure_blueprint("BP_ResourceNode", f"{ROOT}/Blueprints/World/Interactables", resource_class)
    ensure_blueprint("BP_LootContainer", f"{ROOT}/Blueprints/World/Interactables", loot_class)

    for widget in (
        "WBP_HUD", "WBP_Inventory", "WBP_Character", "WBP_QuestTracker",
        "WBP_WorldMap", "WBP_Login", "WBP_CharacterCreation", "WBP_Settings"
    ):
        ensure_widget(widget, f"{ROOT}/UI")

    for folder in (
        "Data/Items", "Data/Abilities", "Data/Classes", "Data/Quests",
        "Data/Enemies", "Data/LootTables", "Data/Biomes", "Data/Regions",
        "Maps/Startup", "Maps/Prototype", "Maps/World"
    ):
        ensure_folder(f"{ROOT}/{folder}")

    unreal.EditorAssetLibrary.save_directory(ROOT, only_if_is_dirty=False)
    unreal.log("[Etherroad] Starter asset generation complete. Configure graphs and validate each asset.")


if __name__ == "__main__":
    main()
