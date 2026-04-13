#pragma once

#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/camera2d.hpp>

namespace godot {

class MapCamera : public Camera2D {
    GDCLASS(MapCamera, Camera2D)

private:
    double speed = 200.0;

    void clamp_position();

protected:
    static void _bind_methods();

public:
    double get_speed() const;
    void set_speed(const double p_speed);

    void _process(double delta) override;
    void _unhandled_input(const Ref<InputEvent> &event) override;
};

}
