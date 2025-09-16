{
  inputs = {
    nixpkgs.url = "nixpkgs";
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
          godot_4_4
          ninja
          protobuf
          pkgsCross.mingwW64.buildPackages.gcc
          pkgsCross.mingwW64.windows.mcfgthreads
          pkgsCross.mingwW64.windows.mingw_w64_pthreads
          pkgsCross.mingwW64.windows.mingw_w64_headers
          #pkgsCross.mingw32.threads
          windows.sdk
          #windows.mingw_w64
        ];
      };
    }
  );
}

