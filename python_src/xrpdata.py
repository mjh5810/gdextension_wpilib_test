from XRPLib.defaults import *
import socket
import struct
import math
import time

# WiFi configuration
SSID = "CornellCup-Web"
PASSWORD = "disneyworld!"
HOST_IP = "192.168.4.126"  # Your computer's IP address
HOST_PORT = 4242

def connect_wifi():
    import network
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    wlan.connect(SSID, PASSWORD)

    while not wlan.isconnected():
        print("Connecting to WiFi...")
        time.sleep(1)

    print(f"Connected! IP: {wlan.ifconfig()[0]}")
    return wlan

def calculate_position():
    # Connect to WiFi
    connect_wifi()

    # Create UDP socket
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    filtered_roll = imu.get_roll()

    prev_encoder = 0;
    prev_x = 0;
    prev_y = 0;

    while True:
        current_roll = imu.get_roll()
        filtered_roll = 0.1 * current_roll + (1 - 0.1) * filtered_roll
        display_roll = filtered_roll % 360

        encoder_average = (drivetrain.get_left_encoder_position() + 
                          drivetrain.get_right_encoder_position()) / 2

        encoder_difference = encoder_average - prev_encoder

        new_x = prev_x + (encoder_difference * math.cos(math.radians(display_roll)))
        new_y = prev_y + (encoder_difference * math.sin(math.radians(display_roll)))

        # Pack as 3 floats (x, y, angle) - 12 bytes total
        # Using little-endian format
        packet = struct.pack('<fff', new_x, new_y, display_roll)

        try:
            sock.sendto(packet, (HOST_IP, HOST_PORT))
        except Exception as e:
            print(f"Send error: {e}")

        print(f"x: {new_x}, y: {new_y}, angle: {display_roll}")

        prev_x = new_x
        prev_y = new_y

        prev_encoder = encoder_average

        time.sleep(0.1)
calculate_position()



