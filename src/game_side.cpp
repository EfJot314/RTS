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
    // labels
    crystals_label = get_node<Label>("PanelContainer/HBoxContainer/VBoxContainer/CrystalsLabel");
    gas_label = get_node<Label>("PanelContainer/HBoxContainer/VBoxContainer/GasLabel");

    // buttons
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

void GameSide::update_ui() {
    String crystals_text = "Crystals: " + String::num((int)crystals);
    String gas_text = "Gas: " + String::num((int)gas);

    crystals_label->set_text(crystals_text);
    gas_label->set_text(gas_text);
}

void GameSide::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_side"), &GameSide::get_side);
    ClassDB::bind_method(D_METHOD("set_side", "p_side"), &GameSide::set_side);

    ClassDB::bind_method(D_METHOD("on_building_button_pressed", "p_building_type"), &GameSide::on_building_button_pressed);

    ADD_PROPERTY(PropertyInfo(Variant::INT, "side", PROPERTY_HINT_ENUM, "Player,Enemy"), "set_side", "get_side");
}

void GameSide::on_building_button_pressed(String p_building_type) {
    if (p_building_type == "Base") {
        Base* building = spawn_building<Base>("res://base.tscn");
        if (building != nullptr)
            base_exists = true;
    } else if (!base_exists) {
        return;
    } else if (p_building_type == "CrystalsMine") {
        CrystalsMine* building = spawn_building<CrystalsMine>("res://crystals_mine.tscn");
        if (building != nullptr) {
            crystals_mines.append(building);
        }
    } else if (p_building_type == "GasMine") {
        GasMine* building = spawn_building<GasMine>("res://gas_mine.tscn");
        if (building != nullptr) {
            gas_mines.append(building);
        }
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
                on_building_button_pressed("Base");
            } else if (key_event->get_keycode() == Key::KEY_2) {
                on_building_button_pressed("CrystalsMine");
            } else if (key_event->get_keycode() == Key::KEY_3) {
                on_building_button_pressed("GasMine");
            } else if (key_event->get_keycode() == Key::KEY_4) {
                on_building_button_pressed("Barracks");
            }
        }
    }
}

void GameSide::_process(double delta) {
    // increase resources
    double cps = 0;
    for(int i = 0 ; i < crystals_mines.size() ; i++) {
        Variant v =  crystals_mines[i];
        CrystalsMine* m = Object::cast_to<CrystalsMine>(v);
        if (!m->get_setting())
            cps += m->get_rps();
    }
    double gps = 0;
    for(int i = 0 ; i < gas_mines.size() ; i++) {
        Variant v =  gas_mines[i];
        GasMine* m = Object::cast_to<GasMine>(v);
        if (!m->get_setting())
            gps += m->get_rps();
    }

    crystals += cps * delta;
    gas += gps * delta;

    update_ui();
}
