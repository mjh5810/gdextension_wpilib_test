{
  inputs = {
    #nixpkgs.url = "nixpkgs";
    systems.url = "github:nix-systems/default";
    flake-utils = {
      url = "github:numtide/flake-utils";
      inputs.systems.follows = "systems";
    };
  };

  outputs = { self, nixpkgs, flake-utils, ... }:
  flake-utils.lib.eachDefaultSystem ( system:
    let
      pkgs = import nixpkgs { inherit system; config.allowUnfree = true;};
    in {
      devShell = pkgs.mkShell { # nix shell
      packages = with pkgs; [
          # directly required
          scons
          cmake
          libgcc
          (enableDebugging godotPackages_4_5.godot)
          ninja
          protobuf
          apriltag
          libdatachannel.dev

          # for other things like building allwpilib
          libssh
          zlib
          libatomic_ops
          #xorg.libX11.dev
          xorg.libXrandr
          xorg.libXinerama
          xorg.libXcursor
          xorg.libXi
          glfw
          wayland
          wayland-scanner
          wayland-protocols
          gradle
          #openjdk17

          # for the python scripts
          opencv
          (pkgs.python313.withPackages (python-pkgs: with python-pkgs; [
            opencv4
            numpy
            imutils
          ]))

          # for dev environment
          ccls
          pyright
        ];
        buildInputs = with pkgs; [
          xorg.libX11
          xorg.libX11.dev
          xorg.libXrandr
          xorg.libXinerama
          xorg.libXcursor
          xorg.libXi
          glfw
        ];
        LD_LIBRARY_PATH = pkgs.lib.makeLibraryPath [ pkgs.xorg.libX11 pkgs.libGL ];
        hardeningDisable = ["all"];
      };
    }
  );
}

