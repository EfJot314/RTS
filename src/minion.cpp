#include <optional>

#include "minion.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/input_event_mouse_button.hpp>

using namespace godot;


Minion::Minion() {
	speed = 20.0;
    destination = std::nullopt;
}

Minion::~Minion() {
}

void Minion::set_speed(const double p_speed) {
    speed = p_speed;
}

double Minion::get_speed() const {
    return speed;
}

void Minion::set_destination(Vector2 target) {
    destination = target;
}

void Minion::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_speed"), &Minion::get_speed);
    ClassDB::bind_method(D_METHOD("set_speed", "p_speed"), &Minion::set_speed);

    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "speed"), "set_speed", "get_speed");
}


void Minion::_input(const Ref<InputEvent> &event) {}

void Minion::_ready() {
    add_to_group("minions");
    UtilityFunctions::print("Added to group");
    selection_circle = get_node<Sprite2D>("Selection");
}

void Minion::highlight(bool highlight) {
    UtilityFunctions::print("Highlighted");
    selected = highlight;
    if (selection_circle) {
        selection_circle->set_visible(selected);
    }
}

void Minion::move(double delta) {
    if (destination.has_value()) {
        Vector2 position = get_global_position();
        Vector2 direction = (destination.value() - position).normalized();
        Vector2 velocity = speed * direction;
        Vector2 new_position = position + velocity * delta;
        set_position(new_position);
    }
}

void Minion::_process(double delta) {
    move(delta);
}
