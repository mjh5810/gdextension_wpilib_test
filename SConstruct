#!/usr/bin/env python
import os
import sys

env = SConscript("godot-cpp/SConstruct")

# For reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

# tweak this if you want to use different folders, or more folders, to store your source code in.
env.Append(CPPPATH=["src/",
                    "allwpilib/wpilibc/src/main/native/include/",
                    "allwpilib/hal/src/main/native/include/",
                    "allwpilib/wpiutil/src/main/native/include",
                    "allwpilib/wpiutil/src/main/native/thirdparty/nanopb/include",
                    "allwpilib/wpiutil/src/main/native/thirdparty/llvm/include",
                    "allwpilib/wpiutil/src/main/native/thirdparty/fmtlib/include",
                    "allwpilib/wpiutil/src/main/native/thirdparty/json/include",
                    "allwpilib/wpimath/src/main/native/include",
                    "allwpilib/wpimath/src/main/native/thirdparty/gcem/include/",
                    "allwpilib/ntcore/src/main/native/include/",
                    "allwpilib/ntcore/src/generated/main/native/include/",
                    "allwpilib/wpinet/src/main/native/include/"],
            CXXFLAGS="/std:c++20")
sources = Glob("src/*.cpp")

if env["platform"] == "macos":
    library = env.SharedLibrary(
        "demo/bin/libgdwpi.{}.{}.framework/libgdwpi.{}.{}".format(
            env["platform"], env["target"], env["platform"], env["target"]
        ),
        source=sources,
    )
elif env["platform"] == "ios":
    if env["ios_simulator"]:
        library = env.StaticLibrary(
            "demo/bin/libgdwpi.{}.{}.simulator.a".format(env["platform"], env["target"]),
            source=sources,
        )
    else:
        library = env.StaticLibrary(
            "demo/bin/libgdwpi.{}.{}.a".format(env["platform"], env["target"]),
            source=sources,
        )
else:
    library = env.SharedLibrary(
        "demo/bin/libgdwpi{}{}".format(env["suffix"], env["SHLIBSUFFIX"]),
        source=sources,
    )

Default(library)
