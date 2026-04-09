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

void Minion::set_side(const int p_side) {
    side = p_side;
}

int Minion::get_side() const {
    return side;
}

void Minion::set_destination(Vector2 target) {
    destination = target;
}

void Minion::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_speed"), &Minion::get_speed);
    ClassDB::bind_method(D_METHOD("set_speed", "p_speed"), &Minion::set_speed);

    ClassDB::bind_method(D_METHOD("get_side"), &Minion::get_side);
    ClassDB::bind_method(D_METHOD("set_side", "p_side"), &Minion::set_side);

    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "speed"), "set_speed", "get_speed");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "side", PROPERTY_HINT_ENUM, "Player,Enemy"), "set_side", "get_side");
}


void Minion::_input(const Ref<InputEvent> &event) {}

void Minion::_ready() {
    add_to_group("minions");
    selection_circle = get_node<Sprite2D>("Selection");
    health_bar = get_node<ProgressBar>("Health");
    if (health_bar) {
        UtilityFunctions::print("Health found");
        health_bar->set_max(health);
        health_bar->set_value(health);
    }
}

void Minion::update_health_bar() {
    if (health_bar) {
        health_bar->set_value(health);
    }
}

void Minion::hit(const double dmg) {
    health -= dmg;

    update_health_bar();

    if (health <= 0) {
        queue_free();
    }
}

void Minion::highlight(bool highlight) {
    selected = highlight;
    if (selection_circle) {
        selection_circle->set_visible(selected);
    }
}

void Minion::move(double delta) {
    if (destination.has_value()) {
        Vector2 position = get_global_position();
        Vector2 destination_vector = destination.value() - position;
        Vector2 direction = destination_vector.normalized();
        Vector2 velocity = speed * direction;
        Vector2 position_delta = velocity * delta;
        Vector2 new_position = position + position_delta;
        set_position(new_position);

        if (destination_vector.length() < position_delta.length()) {
            destination = std::nullopt;
        }
    }
}

void Minion::hit_all(double delta) {
    TypedArray<Area2D> overlaps = get_overlapping_areas();

    for (int i = 0; i < overlaps.size(); i++) {
        Area2D *area = Object::cast_to<Area2D>(overlaps[i]);
        Minion *other = Object::cast_to<Minion>(area);

        if (other && other->get_side() != side) {
            double damage = damage_per_second * delta;
            other->hit(damage);
        }
    }
}

void Minion::_process(double delta) {
    move(delta);
    hit_all(delta);
}
