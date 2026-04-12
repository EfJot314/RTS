#include "game_side.h"

#include <godot_cpp/classes/input.hpp>
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

void GameSide::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_side"), &GameSide::get_side);
    ClassDB::bind_method(D_METHOD("set_side", "p_side"), &GameSide::set_side);

    ADD_PROPERTY(PropertyInfo(Variant::INT, "side", PROPERTY_HINT_ENUM, "Player,Enemy"), "set_side", "get_side");
}

void GameSide::add_building(Building* building) {
    buildings.append(building);
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
