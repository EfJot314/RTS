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

double Building::get_crystals_cost() const {
    return crystals_cost;
}

void Building::set_crystals_cost(const double p_crystals_cost) {
    crystals_cost = p_crystals_cost;
}

double Building::get_gas_cost() const {
    return gas_cost;
}

void Building::set_gas_cost(const double p_gas_cost) {
    gas_cost = p_gas_cost;
}

bool Building::get_setting() const {
    return setting;
}

void Building::_ready() {
    health = max_health;

    // configure setting
    setting = true;
    Color green_transparent_tint = Color(0.4f, 1.0f, 0.4f, 0.3f);
    set_modulate(green_transparent_tint);
}

void Building::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_side"), &Building::get_side);
    ClassDB::bind_method(D_METHOD("set_side", "p_side"), &Building::set_side);
    ClassDB::bind_method(D_METHOD("get_health"), &Building::get_health);
    ClassDB::bind_method(D_METHOD("set_health", "p_health"), &Building::set_health);
    ClassDB::bind_method(D_METHOD("get_crystals_cost"), &Building::get_crystals_cost);
    ClassDB::bind_method(D_METHOD("set_crystals_cost", "p_crystals_cost"), &Building::set_crystals_cost);
    ClassDB::bind_method(D_METHOD("get_gas_cost"), &Building::get_gas_cost);
    ClassDB::bind_method(D_METHOD("set_gas_cost", "p_gas_cost"), &Building::set_gas_cost);

    ADD_PROPERTY(PropertyInfo(Variant::INT, "side", PROPERTY_HINT_ENUM, "Player,Enemy"), "set_side", "get_side");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "max_health"), "set_health", "get_health");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "crystals_cost"), "set_crystals_cost", "get_crystals_cost");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "gas_cost"), "set_gas_cost", "get_gas_cost");
}

void Building::_input(const Ref<InputEvent> &event) {
    Ref<InputEventMouseButton> mouse_click = event;
    if (mouse_click.is_valid()) {
        if (setting) {
            if (mouse_click->get_button_index() == MOUSE_BUTTON_LEFT) {
                if (mouse_click->is_pressed()) {
                    setting = false;
                    set_modulate(Color("white"));
                }
            } else if (mouse_click->get_button_index() == MOUSE_BUTTON_RIGHT) {
                if (mouse_click->is_pressed()) {
                    this->queue_free();
                }
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

double Mine::get_rps() const {
    return rps;
}

void Mine::set_rps(const double p_rps) {
    rps = p_rps;
}

void Mine::_bind_methods() {
    Building::_bind_methods();

    ClassDB::bind_method(D_METHOD("get_rps"), &Mine::get_rps);
    ClassDB::bind_method(D_METHOD("set_rps", "p_rps"), &Mine::set_rps);

    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "rps"), "set_rps", "get_rps");
}

void Base::_bind_methods() {}
void Barracks::_bind_methods() {}
void CrystalsMine::_bind_methods() {}
void GasMine::_bind_methods() {}
