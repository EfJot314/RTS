#include "building.h"

#include <godot_cpp/classes/input_event_mouse_button.hpp>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>

using namespace godot;

int Building::get_side() const {
    return side;
}

void Building::set_side(const int p_side) {
    side = p_side;
}

double Building::get_health() const {
    return max_health;
}

void Building::set_health(const double p_health) {
    max_health = p_health;
}

void Building::_ready() {
    health = max_health;
}

void Building::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_side"), &Building::get_side);
    ClassDB::bind_method(D_METHOD("set_side", "p_side"), &Building::set_side);
    ClassDB::bind_method(D_METHOD("get_health"), &Building::get_health);
    ClassDB::bind_method(D_METHOD("set_health", "p_health"), &Building::set_health);

    ADD_PROPERTY(PropertyInfo(Variant::INT, "side", PROPERTY_HINT_ENUM, "Player,Enemy"), "set_side", "get_side");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "max_health"), "set_health", "get_health");
}

void Building::_input(const Ref<InputEvent> &event) {
    Ref<InputEventMouseButton> mouse_click = event;
    if (mouse_click.is_valid()) {
        if (mouse_click->get_button_index() == MOUSE_BUTTON_RIGHT && setting) {
            if (mouse_click->is_pressed()) {
                setting = false;
            }
        }
    }


    if (setting) {
        Ref<InputEventMouseMotion> mouse_motion = event;
        if (mouse_motion.is_valid()) {
            Vector2 current_position = get_global_mouse_position();
            set_position(current_position);
        }
    }

}



void Base::_bind_methods() {}
void Barracks::_bind_methods() {}
void Mine::_bind_methods() {}
void CrystalsMine::_bind_methods() {}
void GasMine::_bind_methods() {}
