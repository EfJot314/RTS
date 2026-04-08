#pragma once

#include <optional>

#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/input_event.hpp>

namespace godot {

class Minion : public Sprite2D {
	GDCLASS(Minion, Sprite2D)

private:
    int side;
    bool selected = false;
    Sprite2D* selection_circle = nullptr;
	double speed;
    std::optional<Vector2> destination;

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

    void highlight(bool highlight);

    void set_destination(Vector2 target);

	void _input(const Ref<InputEvent> &event) override;
	void _ready() override;
	void _process(double delta) override;
};

}
