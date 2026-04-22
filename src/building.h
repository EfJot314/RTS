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
    double rps = 1.0;             // resource per second
    double max_health = 500.0;
    double health = 500.0;
    double crystals_cost = 20;
    double gas_cost = 10;
    static void _bind_methods();

public:
    int get_side() const;
    void set_side(const int p_side);
    double get_health() const;
    void set_health(const double p_health);

    double get_crystals_cost() const;
    void set_crystals_cost(const double p_crystals_cost);
    double get_gas_cost() const;
    void set_gas_cost(const double p_gas_cost);

    bool get_setting() const;

    void _ready() override;
    void _input(const Ref<InputEvent> &event) override;

};



class Mine : public Building {
    GDCLASS(Mine, Building)
protected:
    double rps = 1.0;            // resource per second
    static void _bind_methods();
public:
    double get_rps() const;
    void set_rps(const double p_rps);
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

}
