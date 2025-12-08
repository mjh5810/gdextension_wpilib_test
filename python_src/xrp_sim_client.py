import socket, struct

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
PORT_RECIEVE = 3540

motorID = ["Left Motor", "Right Motor", "Motor 3", "Motor 4"]

def parse_xrp_packet(packet):
    state = {
        "motor"    : 0,
        "servo"    : 0,
        "dio"      : 0,
        "analogIn" : 0,
        "xrpGyro"  : 0,
        "accel"    : 0,
        "encoder"  : 0
    }

    seq = packet[0:2]
    print(int.from_bytes(seq))
    ctrl = bool(packet[2]) # TODO: add handling for enable/disable
    data = packet[3:]
    while len(data) != 0:
        #print(type(data))
        #size = int.from_bytes(data[0])
        size = data[0]
        tagID = data[1]
        if size == 1:
            continue
        payload = data[2:2+size]
        match tagID:
            case b'\x12': # XRPMotor
                if state["motor"] == 0:
                    print(f"MotorID: {motorID[int.from_bytes(payload)]}")
                    state["motor"] += 1
                else:
                    print(f"Motor Value: {struct.unpack('>f',payload)[0]}")
            case b'\x13': # XRPServo
                print("servo")
            case b'\x14': # DIO
                print("DIO")
            case b'\x14': # AnalogIn
                print("AnalogIn")
            case b'\x17': # BuiltInAccel
                print("accel")
            case b'\x18': # Encoder
                print("Encoder")
            case _:
                print(f"Other packet of type: {tagID}")
        data = data[1+size:]


if __name__ == "__main__":
    sock.bind(("localhost",3540))
    #for _ in range(100):
    while True:
        packet = sock.recvfrom(65535)[0]
        #print(packet.hex('_'))
        parse_xrp_packet(packet)
