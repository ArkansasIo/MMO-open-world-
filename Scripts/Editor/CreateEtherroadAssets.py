"""Idempotently create Etherroad starter Blueprint and Widget Blueprint assets.

Run from Unreal Editor with the Python Editor Script Plugin enabled.
This creates asset shells only; graphs, layout, materials, and data must be configured
and validated in the editor. Do not run as a standalone Python script.
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
    # Custom native classes should be loaded after a successful C++ editor build.
    player_class = unreal.load_class(None, "/Script/Etherroad.ERPlayerCharacter")
    character_class = unreal.load_class(None, "/Script/Engine.Character")
    actor_class = unreal.load_class(None, "/Script/Engine.Actor")

    if not player_class:
        raise RuntimeError("ERPlayerCharacter was not found. Compile the EtherroadEditor target first.")

    ensure_blueprint("BP_PlayerCharacter", f"{ROOT}/Blueprints/Characters", player_class)
    ensure_blueprint("BP_EnemyCharacter", f"{ROOT}/Blueprints/Characters", character_class)
    ensure_blueprint("BP_NPCCharacter", f"{ROOT}/Blueprints/Characters", character_class)
    ensure_blueprint("BP_ResourceNode", f"{ROOT}/Blueprints/World/Interactables", actor_class)
    ensure_blueprint("BP_LootContainer", f"{ROOT}/Blueprints/World/Interactables", actor_class)

    for widget in (
        "WBP_HUD", "WBP_Inventory", "WBP_Character", "WBP_QuestTracker",
        "WBP_WorldMap", "WBP_Login", "WBP_CharacterCreation", "WBP_Settings"
    ):
        ensure_widget(widget, f"{ROOT}/UI")

    for folder in (
        "Data/Items", "Data/Abilities", "Data/Classes", "Data/Quests",
        "Data/Enemies", "Data/Biomes", "Data/Regions", "Maps/Startup",
        "Maps/Prototype", "Maps/World"
    ):
        ensure_folder(f"{ROOT}/{folder}")

    unreal.EditorAssetLibrary.save_directory(ROOT, only_if_is_dirty=False)
    unreal.log("[Etherroad] Starter asset generation complete. Configure graphs and validate each asset.")

if __name__ == "__main__":
    main()
