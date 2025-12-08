#ifndef GDCAMHAND
#define GDCAMHAND

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/udp_server.hpp>
#include <godot_cpp/classes/texture_rect.hpp>

#include <apriltag/apriltag.h>
#include <apriltag/common/image_u8.h>
#include <apriltag/apriltag_pose.h>

#include <thread>

namespace godot {

class CameraHandler : public Node {
    GDCLASS(CameraHandler, Node)

public:
    CameraHandler();
    ~CameraHandler();

    void _ready() override;
    void _process(float delta);

    TextureRect* displaySurface = nullptr;

    std::mutex mut;

    TextureRect *get_displaysurface() const;
    void set_displaysurface(TextureRect* p_displaysurface);

private:
    UDPServer* server;

    apriltag_detector_t* td = nullptr;

    static image_u8_t* jpeg_buffer_to_image_u8(PackedByteArray packet);
    static void detect_position(image_u8_t* im, apriltag_detector_t* td);
    static apriltag_detector_t* create_detector();

protected:
    static void _bind_methods();

};
}
#endif
