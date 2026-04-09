#include "selection_manager.h"

#include <cmath>

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event_mouse_button.hpp>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>
#include <godot_cpp/core/memory.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/window.hpp>


using namespace godot;

void SelectionManager::_bind_methods() {}

void SelectionManager::add_to_selected(Minion* p_minion) {
    if (p_minion && !selected_minions.has(p_minion)) {
        selected_minions.append(p_minion);
        p_minion->highlight(true);
    }
}

void SelectionManager::select_minions() {
    TypedArray<Node> all_minions = get_tree()->get_nodes_in_group("minions");

    for (int i = 0; i < all_minions.size(); i++) {
        Minion *minion = Object::cast_to<Minion>(all_minions[i]);

        if (minion && minion->get_side() == side) {
            if (selection.has_point(minion->get_global_position())) {
                add_to_selected(minion);
            }
        }
    }
}

void SelectionManager::clear_selected() {
    for (int i = 0; i < selected_minions.size(); i++) {
        Minion *minion = Object::cast_to<Minion>(selected_minions[i]);
        if (minion) {
            minion->highlight(false);
        }
    }
    selected_minions.clear();
}

TypedArray<Minion> SelectionManager::get_selected_minions() const {
    return selected_minions;
}

TypedArray<Vector2> SelectionManager::get_destinations(int n) {
    TypedArray<Vector2> result;
    Vector2 dest = destination.value();

    double r = 150.0;

    double a = 0;
    double curr_r = 0;
    double dphi = 0;
    for (int i = 0; i < n; i++) {
        if (i > a) {
            a += 4;
            curr_r = a * r / 4.0;
            dphi = 2 * M_PI / a;
        }
        double phi = (i - (a - 4)) * dphi;

        double x = dest.x + curr_r * std::cos(phi);
        double y = dest.y + curr_r * std::sin(phi);

        result.append(Vector2(x,y));
    }

    return result;
}

void SelectionManager::set_destinations() {
    if (destination.has_value()) {
        int n = selected_minions.size();
        TypedArray<Vector2> positions = get_destinations(n);
        for (int i = 0; i < n; i++) {
            Minion *minion = Object::cast_to<Minion>(selected_minions[i]);
            Vector2 position = positions[i];
            if (minion) {
                minion->set_destination(position);
            }
        }
    }
}

void SelectionManager::check_selecting_side() {
    Input *input = Input::get_singleton();
    if (input->is_key_pressed(KEY_SHIFT) && input->is_key_pressed(KEY_1)) {
        side = 1;
    } else if (input->is_key_pressed(KEY_SHIFT) && input->is_key_pressed(KEY_2)) {
        side = 2;
    } else if (input->is_key_pressed(KEY_SHIFT) && input->is_key_pressed(KEY_3)) {
        side = 3;
    } else if (input->is_key_pressed(KEY_SHIFT) && input->is_key_pressed(KEY_4)) {
        side = 4;
    } else if (input->is_key_pressed(KEY_SHIFT) && input->is_key_pressed(KEY_5)) {
        side = 5;
    } else if (input->is_key_pressed(KEY_SHIFT) && input->is_key_pressed(KEY_6)) {
        side = 6;
    } else if (input->is_key_pressed(KEY_SHIFT) && input->is_key_pressed(KEY_7)) {
        side = 7;
    } else if (input->is_key_pressed(KEY_SHIFT) && input->is_key_pressed(KEY_8)) {
        side = 8;
    } else if (input->is_key_pressed(KEY_SHIFT) && input->is_key_pressed(KEY_9)) {
        side = 9;
    } else {
        // default -> Player
        side = 0;
    }
}

void SelectionManager::_input(const Ref<InputEvent> &event) {
    Ref<InputEventMouseButton> mouse_click = event;

    if (mouse_click.is_valid()) {
        if (mouse_click->get_button_index() == MOUSE_BUTTON_LEFT) {
            if (mouse_click->is_pressed()) {
                selecting = true;
                clear_selected();
                start = get_global_mouse_position();
                end = start;
                check_selecting_side();
            } else {
                selecting = false;
                select_minions();
                queue_redraw();
            }
        } else if (mouse_click->get_button_index() == MOUSE_BUTTON_RIGHT) {
            if (mouse_click->is_pressed()) {
                destination = get_global_mouse_position();
                set_destinations();
            }
        }
    }

    Ref<InputEventMouseMotion> mouse_motion = event;
    if (mouse_motion.is_valid() && selecting) {
        end = get_global_mouse_position();

        selection = Rect2(start, Vector2());
        selection.expand_to(end);

        queue_redraw();
    }
}


void SelectionManager::_draw() {
    Color color;
    if (side == 0) {
        color = Color(0, 1, 0, 0.8);
    } else {
        color = Color(1, 0, 0, 0.8);
    }

    if (selecting) {
        draw_rect(selection, color, false, 2.0);
    }
}
