This is the actual GDExtension implementation, there's some documentation listed in-engine (or directly in the doc_classes folder)

camera_handler: CameraHandler class, recieves UDP camera data and displays it to a texture rect. Reimplementation of the `node_2d.gd` script in `demo`, redone in C++ to try and have apriltag through it
gdwpi: GDNetworkTable class, interfaces with the wpilib NetworkTables interface
register_types: necessary for GDExtension to register the custom classes with the engine
