#pragma once

#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/input_event.hpp>

namespace godot {

class Building : public Sprite2D {
    GDCLASS(Building, Sprite2D)

private:
    int side = 0;

protected:
    static void _bind_methods();

public:
    int get_side() const;
    void set_side(const int p_side);

};


}
