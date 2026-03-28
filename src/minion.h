#pragma once

#include <godot_cpp/classes/sprite2d.hpp>

namespace godot {

class Minion : public Sprite2D {
	GDCLASS(Minion, Sprite2D)

private:
	double time_passed;

protected:
	static void _bind_methods();

public:
	Minion();
	~Minion();

	void _process(double delta) override;
};

} // namespace godot

