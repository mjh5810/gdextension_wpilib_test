This is a collection of programs and scripts used for developing an integration between the XRP robot system and the Godot game engine.

allwpilib: a library provided by FIRST that can interact with and control the XRP, all custom things have been written in developerRobot C++
demo: the Godot project (worked on in Godot 4.5)
    /bin: all GDExtension libraries and needed shared libraries
doc_classes: GDExtension documentation that you can find in engine
godot-cpp: C++ bindings for GDExtension
python_src: various python scripts for testing
src: GDExtension C++ source code

Relevant commands:
- `scons platform=[linux|windows]` compiles GDExtension library; run in project root
- `cmake --preset default` generates build files for allwpilib in the `build-cmake` directory; run in `allwpilib`
- `cmake --build <path to allwpilib/build-cmake>` compiles allwpilib; can be run from anywhere
    - You may need to copy the compiled libraries from the build-cmake folder to `demo/bin` to have them be properly linked

**Of note**: this is currently only extensively tested on Linux, using Nix to create a development environment. Some work needs to be done to make building consistent on Windows, largely owing to the fact that cmake has been used to compile allwpilib which is only fully supported on Linux, and I could not figure out a consistent way to access the resulting libraries when built with Gradle. If they can be found and copied to `demo/bin` then scons should be able to handle it.
