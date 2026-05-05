#pragma once

#include "building.h"
#include "minion.h"

#include <optional>

#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/label.hpp>


namespace godot {

class GameSide : public Control {
    GDCLASS(GameSide, Control)

private:
    int side = 0;
    bool base_exists = false;
    TypedArray<Barracks> barracks;
    TypedArray<CrystalsMine> crystals_mines;
    double crystals = 100;
    TypedArray<GasMine> gas_mines;
    double gas = 100;

    bool setting_flag = false;
    std::optional<Vector2> flag_position = std::nullopt;

    // ui
    Label* crystals_label = nullptr;
    Label* gas_label = nullptr;

    bool flag_position_ok(Vector2 position);

protected:
    static void _bind_methods();

public:
    int get_side() const;
    void set_side(const int p_side);

    void on_building_button_pressed(String p_building_type);
    void on_minion_button_pressed(String p_minion_type);

	void _input(const Ref<InputEvent> &event) override;

    void _ready() override;

    void _process(double delta) override;

    void update_ui();

    Minion* spawn_minion(String path);

    template <typename T>
    T* spawn_building(String path) {
        Ref<PackedScene> building_scene = ResourceLoader::get_singleton()->load(path);

        if (building_scene.is_null()) {
            return nullptr;
        }

        Node* scene_instance = building_scene->instantiate();

        T* building = Object::cast_to<T>(scene_instance);

        // Add created building to the current scene and decrease resources
        if (building != nullptr
            && building->get_crystals_cost() <= crystals
            && building->get_gas_cost() <= gas) {
            Node *current_scene = get_tree()->get_current_scene();
            if (current_scene != nullptr) {
                crystals -= building->get_crystals_cost();
                gas -= building->get_gas_cost();
                current_scene->add_child(building);
            }

            // basic building setup
            building->set_side(side);

        }

        return building;
    }

};

}
