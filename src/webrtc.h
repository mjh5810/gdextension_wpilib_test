#ifndef GDWEBRTC
#define GDWEBRTC

#include <godot_cpp/classes/node.hpp>

namespace godot {

class WebRTCCamera : public Node {
    GDCLASS(WebRTCCamera, Node)

public:
    WebRTCCamera()
    ~WebRTCCamera()

private:

protected:
    static void _bind_methods();

};
}
#endif
