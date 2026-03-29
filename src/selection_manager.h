#pragma once

#include "minion.h"

#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/classes/node2d.hpp>

namespace godot {

class SelectionManager : public Node2D {
    GDCLASS(SelectionManager, Node2D)

private:
    bool selecting = false;
    Vector2 start;
    Vector2 end;
    Rect2 selection;
    TypedArray<Minion> selected_minions;
    std::optional<Vector2> destination;

protected:
    static void _bind_methods();

public:
    void set_destinations();
    void add_to_selected(Minion* p_minion);
    void select_minions();
    void clear_selected();
    void _input(const Ref<InputEvent> &event) override;
    void _draw() override;
    TypedArray<Minion> get_selected_minions() const;
};

}
