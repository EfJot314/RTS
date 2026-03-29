#include "selection_manager.h"

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

    UtilityFunctions::print("Selecting...");

    for (int i = 0; i < all_minions.size(); i++) {
        Minion *minion = Object::cast_to<Minion>(all_minions[i]);

        if (minion) {
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

void SelectionManager::set_destinations() {
    for (int i = 0; i < selected_minions.size(); i++) {
        Minion *minion = Object::cast_to<Minion>(selected_minions[i]);
        if (minion && destination.has_value()) {
            minion->set_destination(destination.value());
        }
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
            } else {
                selecting = false;
                select_minions();
                queue_redraw();
            }
        } else if (mouse_click->get_button_index() == MOUSE_BUTTON_RIGHT) {
            if (mouse_click->is_pressed()) {
                UtilityFunctions::print("Setting target");
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
    if (selecting) {
        draw_rect(selection, Color(0, 1, 0, 0.8), false, 2.0);
    }
}
