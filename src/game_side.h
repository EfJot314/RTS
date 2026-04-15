#pragma once

#include "building.h"

#include <godot_cpp/classes/control.hpp>

namespace godot {

class GameSide : public Control {
    GDCLASS(GameSide, Control)

private:
    int side = 0;
    TypedArray<Building> buildings;

protected:
    static void _bind_methods();

public:
    int get_side() const;
    void set_side(const int p_side);

    void add_building(Building* building);

    void on_building_button_pressed(String p_building_type);

	void _input(const Ref<InputEvent> &event) override;

    void _ready() override;

};

}
