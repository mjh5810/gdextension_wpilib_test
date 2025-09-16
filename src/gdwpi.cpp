#include "gdwpi.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include <fmt/format.h>
#include <networktables/NetworkTableInstance.h>
#include <networktables/NetworkTable.h>

using namespace godot;

void GDExample::_bind_methods() {
    
}

GDExample::GDExample() {
    time_passed = 0.0;
}

GDExample::~GDExample() {
}

void GDExample::_process(double delta) {
    time_passed += delta;
    Vector2 new_position = Vector2(10.0 + (10.0 * sin(time_passed * 2.0)), 10.0 + (10.0 * cos(time_passed * 1.5)));
    set_position(new_position);
}

void GDWPINode::_bind_methods() {

}

GDWPINode::GDWPINode() {
    ntInst = nt::NetworkTableInstance::GetDefault();
    auto table = ntInst.GetTable("datatable");

    print_line("test");
}

GDWPINode::~GDWPINode() {

}
