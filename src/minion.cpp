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

void Minion::set_health(const double p_health) {
    max_health = p_health;
}

double Minion::get_health() const {
    return max_health;
}

void Minion::set_side(const int p_side) {
    side = p_side;
}

int Minion::get_side() const {
    return side;
}

void Minion::set_destination(Vector2 target) {
    destination = target;
    navigation->set_target_position(target);
}

void Minion::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_speed"), &Minion::get_speed);
    ClassDB::bind_method(D_METHOD("set_speed", "p_speed"), &Minion::set_speed);

    ClassDB::bind_method(D_METHOD("get_side"), &Minion::get_side);
    ClassDB::bind_method(D_METHOD("set_side", "p_side"), &Minion::set_side);

    ClassDB::bind_method(D_METHOD("get_health"), &Minion::get_health);
    ClassDB::bind_method(D_METHOD("set_health", "p_health"), &Minion::set_health);

    ClassDB::bind_method(D_METHOD("get_crystals_cost"), &Minion::get_crystals_cost);
    ClassDB::bind_method(D_METHOD("set_crystals_cost", "p_crystals_cost"), &Minion::set_crystals_cost);
    ClassDB::bind_method(D_METHOD("get_gas_cost"), &Minion::get_gas_cost);
    ClassDB::bind_method(D_METHOD("set_gas_cost", "p_gas_cost"), &Minion::set_gas_cost);

    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "speed"), "set_speed", "get_speed");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "side", PROPERTY_HINT_ENUM, "Player,Enemy"), "set_side", "get_side");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "max_health"), "set_health", "get_health");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "crystals_cost"), "set_crystals_cost", "get_crystals_cost");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "gas_cost"), "set_gas_cost", "get_gas_cost");
}


void Minion::_input(const Ref<InputEvent> &event) {}

void Minion::_ready() {
    add_to_group("minions");
    selection_circle = get_node<Sprite2D>("Selection");
    health_bar = get_node<ProgressBar>("Health");
    if (health_bar) {
        health_bar->set_max(max_health);
        health = max_health;
        update_health_bar();
    }
    // get navigation agent
    navigation = get_node<NavigationAgent2D>("NavigationAgent2D");
}

void Minion::update_health_bar() {
    if (health_bar) {
        health_bar->set_value(health);
    }

    // TODO -> change to more 'continous' color change
    Color bar_color;
    if (health / max_health > 0.7) {
        bar_color = Color(0, 1, 0);
    } else if (health / max_health > 0.3) {
        bar_color = Color(1, 1, 0);
    } else {
        bar_color = Color(1, 0, 0);
    }
    health_bar->set_modulate(bar_color);
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
        if (navigation->is_navigation_finished()) {
            destination = std::nullopt;
            return;
        }

        Vector2 next_path_pos = navigation->get_next_path_position();
        Vector2 current_pos = get_global_position();

        Vector2 velocity = (next_path_pos - current_pos).normalized() * speed;

        Vector2 position = get_global_position();
        Vector2 position_delta = velocity * delta;
        Vector2 new_position = position + position_delta;
        set_position(new_position);
    }
    // Jeśli dotarliśmy do celu, nie rób nic
    if (navigation->is_navigation_finished()) {
        return;
    }

    Vector2 next_path_pos = navigation->get_next_path_position();
    Vector2 current_pos = get_global_position();

    Vector2 velocity = (next_path_pos - current_pos).normalized() * speed;

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

double Minion::get_crystals_cost() const {
    return crystals_cost;
}

void Minion::set_crystals_cost(const double p_crystals_cost) {
    crystals_cost = p_crystals_cost;
}

double Minion::get_gas_cost() const {
    return gas_cost;
}

void Minion::set_gas_cost(const double p_gas_cost) {
    gas_cost = p_gas_cost;
}
