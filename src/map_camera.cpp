#include "map_camera.h"

#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event_mouse_button.hpp>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>

using namespace godot;


double MapCamera::get_speed() const {
    return speed;
}

void MapCamera::set_speed(const double p_speed) {
    speed = p_speed;
}

void MapCamera::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_speed"), &MapCamera::get_speed);
    ClassDB::bind_method(D_METHOD("set_speed", "p_speed"), &MapCamera::set_speed);

    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "speed"), "set_speed", "get_speed");
}

void MapCamera::clamp_position() {
    Vector2 viewport_size = get_viewport_rect().size;
    Vector2 view_size = viewport_size * get_zoom();
    Vector2 half_view = view_size / 2.0f;

    Vector2 pos = get_position();

    float clamped_x = CLAMP(pos.x, (float)get_limit(SIDE_LEFT)+half_view.x, (float)get_limit(SIDE_RIGHT)-half_view.x);
    float clamped_y = CLAMP(pos.y, (float)get_limit(SIDE_TOP)+half_view.y, (float)get_limit(SIDE_BOTTOM)-half_view.y);

    set_position(Vector2(clamped_x, clamped_y));
}

void MapCamera::_process(double delta) {
    // moving camera using arrows
    Input* input = Input::get_singleton();
    Vector2 velocity = Vector2(0, 0);

    if (input->is_action_pressed("ui_right")) velocity.x += 1;
    if (input->is_action_pressed("ui_left"))  velocity.x -= 1;
    if (input->is_action_pressed("ui_down"))  velocity.y += 1;
    if (input->is_action_pressed("ui_up"))    velocity.y -= 1;

    if (velocity.length() > 0) {
        velocity = velocity.normalized() * speed;
    }

    set_position(get_position() + velocity * (float)delta);
    clamp_position();
}

void MapCamera::_unhandled_input(const Ref<InputEvent> &event) {
    // moving camera using mouse
    Ref<InputEventMouseMotion> mouse_motion = event;
    Input* input = Input::get_singleton();

    if (mouse_motion.is_valid() && input->is_mouse_button_pressed(MOUSE_BUTTON_RIGHT)) {
        set_position(get_position() - mouse_motion->get_relative() * get_zoom());
        clamp_position();
    }
}
