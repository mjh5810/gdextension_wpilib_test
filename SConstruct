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
                    "allwpilib/wpinet/src/main/native/include/",
                    "/nix/store/driw4hf80fjn09ly2gxiky58yrm5kv7m-apriltags-3.4.5/include"],
            LIBPATH=["demo/bin/"],
            LIBS=["libntcore", "libwpilibc", "libwpiutil", "libwpimath", "libwpinet", "libwpiHal", "libapriltag"])
            #CXXFLAGS = os.environ["NIX_CFLAGS_COMPILE"])
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

if env["platform"] == "linux":
    env.Append(CXXFLAGS=["-std=c++20", "-fexceptions"])
elif env["platform"] == "windows":
    env.Append(CXXFLAGS=["/std:c++20"])
    #env.Append(CXXFLAGS=["-std=c++20", "-fexceptions"])

if env["target"] in ["editor", "template_debug"]:
    try:
        doc_data = env.GodotCPPDocData("src/gen/doc_data.gen.cpp", source=Glob("doc_classes/*.xml"))
        sources.append(doc_data)
    except AttributeError:
        print("Not including class reference as we're targeting a pre-4.3 baseline.")

env.Append(COMPILATIONDB_USE_ABSPATH=True)
env.Tool('compilation_db')
cdb = env.CompilationDatabase()
Alias('cdb', cdb)

Default(library)
