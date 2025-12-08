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
      pkgs = import nixpkgs { inherit system; config.allowUnfree = true; config.microsoftVisualStudioLicenseAccepted = true;};
    in {
      devShell = pkgs.mkShell { # nix shell
        packages = with pkgs; [
          scons
          cmake
          libgcc
          #libgccjit
          (enableDebugging godotPackages_4_5.godot)
          ninja
          protobuf
          libssh
          zlib
          libatomic_ops
          #xorg.libX11.dev
          xorg.libXrandr
          xorg.libXinerama
          xorg.libXcursor
          xorg.libXi
          glfw
          opencv
          wayland
          wayland-scanner
          wayland-protocols
          gradle
          openjdk17
          pkgsCross.mingwW64.buildPackages.gcc
          #pkgsCross.mingwW64.windows.mcfgthreads
          #pkgsCross.mingwW64.windows.mingw_w64_pthreads
          #pkgsCross.mingwW64.windows.mingw_w64_headers
          #pkgsCross.mingw32.threads
          #windows.sdk
          #windows.mingw_w64
          libdatachannel.dev
          ccls
          pyright
          (pkgs.python313.withPackages (python-pkgs: with python-pkgs; [
            opencv4
            numpy
            imutils
          ]))
          (pkgsCross.mingwW64.windows.mcfgthreads.overrideAttrs {
            dontDisableStatic = true;
          })
          apriltag
          gdb
        ];
        buildInputs = with pkgs; [
          xorg.libX11
          xorg.libX11.dev
          xorg.libXrandr
          xorg.libXinerama
          xorg.libXcursor
          xorg.libXi
          glfw
          apriltag
        ];
        LD_LIBRARY_PATH = pkgs.lib.makeLibraryPath [ pkgs.xorg.libX11 pkgs.libGL ];
        hardeningDisable = ["all"];
      };
    }
  );
}

