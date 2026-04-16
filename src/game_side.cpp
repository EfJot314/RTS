#include "game_side.h"
#include "building.h"


#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/input_event_mouse_button.hpp>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>
#include <godot_cpp/classes/input_event_key.hpp>

using namespace godot;

int GameSide::get_side() const {
    return side;
}

void GameSide::set_side(const int p_side) {
    side = p_side;
}

void GameSide::_ready() {
    Button* btn_base = get_node<Button>("PanelContainer/HBoxContainer/BuildingButtons/BaseButton/Button");
    Button* btn_crystal = get_node<Button>("PanelContainer/HBoxContainer/BuildingButtons/CrystalsMineButton/Button");
    Button* btn_gas = get_node<Button>("PanelContainer/HBoxContainer/BuildingButtons/GasMineButton/Button");
    Button* btn_barracks = get_node<Button>("PanelContainer/HBoxContainer/BuildingButtons/BarracsButton/Button");

    if (btn_base) {
        btn_base->connect("pressed", Callable(this, "on_building_button_pressed").bind("Base"));
    }
    if (btn_crystal) {
        btn_crystal->connect("pressed", Callable(this, "on_building_button_pressed").bind("CrystalsMine"));
    }
    if (btn_gas) {
        btn_gas->connect("pressed", Callable(this, "on_building_button_pressed").bind("GasMine"));
    }
    if (btn_barracks) {
        btn_barracks->connect("pressed", Callable(this, "on_building_button_pressed").bind("Barracks"));
    }
}

void GameSide::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_side"), &GameSide::get_side);
    ClassDB::bind_method(D_METHOD("set_side", "p_side"), &GameSide::set_side);

    ClassDB::bind_method(D_METHOD("on_building_button_pressed", "p_building_type"), &GameSide::on_building_button_pressed);

    ADD_PROPERTY(PropertyInfo(Variant::INT, "side", PROPERTY_HINT_ENUM, "Player,Enemy"), "set_side", "get_side");
}

void GameSide::on_building_button_pressed(String p_building_type) {
    // TODO -> maybe do sth with these buildings later
    if (p_building_type == "Base") {
        Base* building = spawn_building<Base>("res://base.tscn");
    } else if (p_building_type == "CrystalsMine") {
        CrystalsMine* building = spawn_building<CrystalsMine>("res://crystals_mine.tscn");
    } else if (p_building_type == "GasMine") {
        GasMine* building = spawn_building<GasMine>("res://gas_mine.tscn");
    } else if (p_building_type == "Barracks") {
        Barracks* building = spawn_building<Barracks>("res://barracks.tscn");
    }

}

void GameSide::_input(const Ref<InputEvent> &event) {
    Ref<InputEventKey> key_event = event;

    if (key_event.is_valid() && key_event->is_pressed() && !key_event->is_echo()) {
        // Meta (alt) pressed
        if (key_event->is_alt_pressed()) {
            if (key_event->get_keycode() == Key::KEY_1) {
                // TODO -> instantiate building class (for example main base)
            } else if (key_event->get_keycode() == Key::KEY_2) {
                // TODO -> instantiate building class (for example crystal mine)
            } else if (key_event->get_keycode() == Key::KEY_3) {
                // TODO -> instantiate building class (for example gas mine)
            }
        }
    }
}
