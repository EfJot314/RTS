#pragma once

#include <optional>

#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/progress_bar.hpp>

namespace godot {

class Minion : public Area2D {
	GDCLASS(Minion, Area2D)

private:
    int side;
    bool selected = false;
    double damage_per_second = 10;
    double health = 100;
	double speed;
    std::optional<Vector2> destination;
    Sprite2D* selection_circle = nullptr;
    ProgressBar* health_bar = nullptr;

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

    void hit_all(double delta);
    void hit(const double dmg);

    void highlight(bool highlight);
    void update_health_bar();

    void set_destination(Vector2 target);

	void _input(const Ref<InputEvent> &event) override;
	void _ready() override;
	void _process(double delta) override;
};

}
