#pragma once

#include <optional>

#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/progress_bar.hpp>
#include <godot_cpp/classes/navigation_agent2d.hpp>

namespace godot {

class Minion : public Area2D {
	GDCLASS(Minion, Area2D)

private:
    int side = 0;
    double crystals_cost = 10;
    double gas_cost = 5;
    bool selected = false;
    double damage_per_second = 10;
    double max_health = 100;
    double health = 100.0;
    Sprite2D* selection_circle = nullptr;
    ProgressBar* health_bar = nullptr;
    NavigationAgent2D* navigation;
	double speed = 100.0;
    std::optional<Vector2> destination;     //obosolete, but may be useful in the future

protected:
	void move(double delta);

    static void _bind_methods();

public:
	Minion();
	~Minion();

    void set_speed(const double p_speed);
    double get_speed() const;

    void set_side(const int p_side);
    int get_side() const;

    void set_health(const double p_health);
    double get_health() const;

    void hit_all(double delta);
    void hit(const double dmg);

    void highlight(bool highlight);
    void update_health_bar();

    void set_destination(Vector2 target);

	void _input(const Ref<InputEvent> &event) override;
	void _ready() override;
	void _process(double delta) override;

    double get_crystals_cost() const;
    void set_crystals_cost(const double p_crystals_cost);
    double get_gas_cost() const;
    void set_gas_cost(const double p_gas_cost);
};

}
