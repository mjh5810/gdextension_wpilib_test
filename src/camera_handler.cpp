#include "camera_handler.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/packet_peer_udp.hpp>
#include <godot_cpp/classes/image_texture.hpp>
#include <godot_cpp/classes/image.hpp>
#include <godot_cpp/classes/texture_rect.hpp>

#include <apriltag/common/pjpeg.h>
#include <apriltag/apriltag.h>
#include <apriltag/tag25h9.h>
#include <apriltag/common/zarray.h>
#include <apriltag/common/matd.h>

using namespace godot;

CameraHandler::CameraHandler() {}

CameraHandler::~CameraHandler() {}

void CameraHandler::_ready() {
    // a lot of this is done here rather than in constructor
    // to have it only do on game start/init
    server = memnew(UDPServer); // don't forget the memnew
    server->listen(5436);

    td = create_detector();
}

apriltag_detector_t* CameraHandler::create_detector() {

    apriltag_detector_t* td = apriltag_detector_create();
    apriltag_family_t* tf = nullptr;
    tf = tag25h9_create();
    apriltag_detector_add_family_bits(td, tf, 1);
    td->quad_decimate = 2.0;
    td->quad_sigma = 0.0;
    td->nthreads = 1;
    td->refine_edges = 1;
    return td;
}

void CameraHandler::_process(float delta) {
    server->poll();
    //print_line("did process");
    if(server->is_connection_available()) {
        // print_line("a");
        Ref<PacketPeerUDP> peer = server->take_connection(); // ref is a smart pointer?
        PackedByteArray packet = peer->get_packet();
        // print_line("b");
        Image* im = memnew(Image);
        im->load_jpg_from_buffer(packet);
        // print_line("c");
        Ref<ImageTexture> imTex = ImageTexture::create_from_image(im);
        displaySurface->set_texture(imTex);
        image_u8_t* im_u8 = jpeg_buffer_to_image_u8(packet);
        // print_line("d");
        if(mut.try_lock()) {
            print_line("t");
            //std::thread t(&CameraHandler::detect_position, im_u8, td, std::ref(mut));
            detect_position(im_u8, td);
        }
    }
}

void CameraHandler::set_displaysurface(TextureRect* p_displaysurface) {
    if(p_displaysurface != nullptr) {
        displaySurface = p_displaysurface;
    }
}

TextureRect* CameraHandler::get_displaysurface() const {
    return displaySurface;
}

image_u8_t* CameraHandler::jpeg_buffer_to_image_u8(PackedByteArray packet) {
    uint8_t* a = &packet[0]; // evil, nefarious, diabolical Vector->array
    int64_t size = packet.size();
    int err = 0;
    pjpeg_t* pjpeg = pjpeg_create_from_buffer(a, size, 0, &err);
    //pjpeg_t* pjpeg = nullptr;
    if(pjpeg == nullptr) {
        print_line("pjpeg failed to load jpeg");
        return nullptr;
    }
    image_u8_t* im = pjpeg_to_u8_baseline(pjpeg);
    pjpeg_destroy(pjpeg);
    return im;
}

void CameraHandler::detect_position(image_u8_t* im, apriltag_detector_t* td) {
    printf("z");
    zarray_t* detections = apriltag_detector_detect(td, im);
    apriltag_detection_t* first;
    if(zarray_size(detections) == 0) {
        return;
    }
    zarray_get(detections, 0, &first);
    apriltag_detections_destroy(detections);
    apriltag_detection_info_t info;
    info.det = first;
    info.tagsize = 0.078; // tag size in meters
    //double fl = 4.74 / 0.0014; // raspberry pi camera 3 (focal length / pixel size)
    double fl = 1.05 / 0.0014; // framework webcam module 
    info.fx = fl * 1920; // focal length x
    info.fy = fl * 1080; // focal length y
    info.cx = 1920/2; // focal center x
    info.cy = 1080/2; // focal center y

    apriltag_pose_t pose;
    double err = estimate_tag_pose(&info, &pose);
    double x = matd_get(pose.t, 0, 0);
    double y = matd_get(pose.t, 0, 1);
    double z = matd_get(pose.t, 0, 2);
    UtilityFunctions::print("x: %s, y: %s, z: %s", x, y, z);
    //mut.unlock();
    return;
    //return pose;
}

void CameraHandler::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_displaysurface"), &CameraHandler::get_displaysurface);
    ClassDB::bind_method(D_METHOD("set_displaysurface", "p_displaysurface"), &CameraHandler::set_displaysurface);

    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "display_surface", PROPERTY_HINT_NODE_TYPE, "TextureRect"), "set_displaysurface", "get_displaysurface");
}
