{
  description = "Cpp development environment";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs { inherit system; };
      in {
        devShell = pkgs.mkShell {

          # Dependencies for project
          buildInputs = [
            pkgs.gcc
            pkgs.clang

            pkgs.ninja
            pkgs.cmake
            pkgs.valgrind
            pkgs.gf
            pkgs.pkg-config

            pkgs.stb
            pkgs.raylib
            pkgs.entt

            pkgs.glfw
            pkgs.xorg.libX11
            pkgs.xorg.libXcursor
            pkgs.xorg.libXinerama
            pkgs.xorg.libXrandr
            pkgs.xorg.libXi
          ];

          #links libraries to shell
          LD_LIBRARY_PATH = pkgs.lib.makeLibraryPath [
            pkgs.stb
            pkgs.raylib
            pkgs.entt

            pkgs.glfw
            pkgs.xorg.libX11
            pkgs.xorg.libXcursor
            pkgs.xorg.libXinerama
            pkgs.xorg.libXrandr
            pkgs.xorg.libXi
          ];

          shellHook = ''
            PS1="[\\u@\\h && CPP-DEV-ENV:\\w]\$ "
            export CC=${pkgs.clang}
            export CXX=${pkgs.clang}
          '';
        };
      });
}
