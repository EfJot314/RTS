#pragma once

#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/input_event.hpp>

namespace godot {

class Building : public Sprite2D {
    GDCLASS(Building, Sprite2D)

protected:
    bool setting = true;
    int side = 0;
    double max_health = 500.0;
    double health = 500.0;
    static void _bind_methods();

public:
    int get_side() const;
    void set_side(const int p_side);
    double get_health() const;
    void set_health(const double p_health);

    void _ready() override;
    void _input(const Ref<InputEvent> &event) override;

};


class Base : public Building {
    GDCLASS(Base, Building)
protected:
    static void _bind_methods();
};

class Barracks : public Building {
    GDCLASS(Barracks, Building)
protected:
    static void _bind_methods();
};

class Mine : public Building {
    GDCLASS(Mine, Building)
protected:
    static void _bind_methods();
};

class CrystalsMine : public Mine {
    GDCLASS(CrystalsMine, Mine)
protected:
    static void _bind_methods();
};

class GasMine : public Mine {
    GDCLASS(GasMine, Mine)
protected:
    static void _bind_methods();
};

}
