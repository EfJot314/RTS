#pragma once

#include "building.h"

#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/scene_tree.hpp>


namespace godot {

class GameSide : public Control {
    GDCLASS(GameSide, Control)

private:
    int side = 0;

protected:
    static void _bind_methods();

public:
    int get_side() const;
    void set_side(const int p_side);

    void on_building_button_pressed(String p_building_type);

	void _input(const Ref<InputEvent> &event) override;

    void _ready() override;

    template <typename T>
    T* spawn_building(String path) {
        Ref<PackedScene> building_scene = ResourceLoader::get_singleton()->load(path);

        if (building_scene.is_null()) {
            return nullptr;
        }

        Node* scene_instance = building_scene->instantiate();

        T* building = Object::cast_to<T>(scene_instance);

        // Add created building to the current scene
        if (building != nullptr) {
            Node *current_scene = get_tree()->get_current_scene();
            if (current_scene != nullptr) {
                current_scene->add_child(building);
            }
        }

        return building;
    }

};

}
