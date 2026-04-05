{
  description = "Cpp development environment";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let pkgs = import nixpkgs { inherit system; };
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

            pkgs.vulkan-loader
            pkgs.vulkan-tools
            pkgs.vulkan-validation-layers
            pkgs.directx-shader-compiler

            pkgs.raylib
            pkgs.entt
            pkgs.glm
            pkgs.glfw
            pkgs.vulkan-headers
            pkgs.vulkan-utility-libraries
            pkgs.xorg.libX11
            pkgs.xorg.libXcursor
            pkgs.xorg.libXinerama
            pkgs.xorg.libXrandr
            pkgs.xorg.libXi
          ];

          #links libraries to shell
          LD_LIBRARY_PATH = pkgs.lib.makeLibraryPath [
            pkgs.raylib
            pkgs.entt
            pkgs.glm
            pkgs.glfw
            pkgs.vulkan-headers
            pkgs.vulkan-utility-libraries
            pkgs.xorg.libX11
            pkgs.xorg.libXcursor
            pkgs.xorg.libXinerama
            pkgs.xorg.libXrandr
            pkgs.xorg.libXi
          ];

          VULKAN_SDK = "${pkgs.vulkan-headers}";
          VK_LAYER_PATH =
            "${pkgs.vulkan-validation-layers}/share/vulkan/explicit_layer.d";

          shellHook = ''
            export CC=${pkgs.clang}
            export CXX=${pkgs.clang}
          '';
        };
      });
}
