#pragma once

#include "building.h"

#include <godot_cpp/classes/node2d.hpp>

namespace godot {

class GameSide : public Node2D {
    GDCLASS(GameSide, Node2D)

private:
    int side = 0;
    TypedArray<Building> buildings;

protected:
    static void _bind_methods();

public:
    int get_side() const;
    void set_side(const int p_side);

    void add_building(Building* building);

};

}
