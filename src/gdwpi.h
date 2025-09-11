#ifndef GDWPI
#define GDWPI

#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/node.hpp>

#include <frc/TimedRobot.h>
#include <frc/drive/DifferentialDrive.h>
//#include <frc/motorcontrol/PWMSparkMax.h>

namespace godot {

class GDExample : public Sprite2D {
    GDCLASS(GDExample, Sprite2D)

private:
    double time_passed;

protected:
    static void _bind_methods();

public:
    GDExample();
    ~GDExample();

    void _process(double delta) override;
};

class GDWPINode : public Node {
    GDCLASS(GDWPINode, Node)

private:
    frc::TimedRobot robot;

protected:
    static void _bind_methods();

public:
    GDWPINode();
    ~GDWPINode();

};
}

#endif