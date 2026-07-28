{
  description = "RevEngine";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
    systems.url = "github:nix-systems/default";
  };

  outputs = { self, nixpkgs, systems, ... }:
    let
      forEachSystem = f:
        nixpkgs.lib.genAttrs (import systems)
        (system: f { pkgs = import nixpkgs { inherit system; }; });

    in {

      formatter = forEachSystem ({ pkgs, ... }: pkgs.alejandra);

      packages = forEachSystem ({ pkgs }: {
        ogre-debug = pkgs.ogre.overrideAttrs
          (old: { buildInputs = (old.buildInputs or [ ]) ++ [ pkgs.assimp ]; });
      });

      devShells = forEachSystem ({ pkgs, ... }:
        let
          JOLT_REPO = pkgs.fetchgit {
            url = "https://github.com/jrouwe/JoltPhysics";
            tag = "v5.5.0";
            hash = "sha256-OQ3kqpd0NBKA0e/YRNCKaSR0wKIto1mcZ+X93CuJ+Dc=";
          };

          ogre-with-assimp = pkgs.ogre.overrideAttrs (old: {
            buildInputs = (old.buildInputs or [ ]) ++ [ pkgs.assimp ];
            cmakeFlags = (old.cmakeFlags or [ ])
              ++ [ (pkgs.lib.cmakeBool "OGRE_BUILD_PLUGIN_ASSIMP" true) ];
          });

        in {
          default = pkgs.mkShell {

            C_COMPILER = "${pkgs.gcc}/bin/gcc";
            CXX_COMPILER = "${pkgs.gcc}/bin/g++";
    
            JOLT_REPO = JOLT_REPO;

            nativeBuildInputs = with pkgs; [
              SDL2
              spirv-tools
              boost
    
              ogre-with-assimp
              raylib
              gdb
              cmake
              ninja
              clang
              valgrind
              gcc
              doxygen
              python3
              perf
              clang-uml

              pkg-config
              vulkan-loader
              vulkan-tools
              vulkan-validation-layers
              directx-shader-compiler
            ];

            buildInputs = with pkgs; [
              JOLT_REPO

              ogre-with-assimp
              recastnavigation
              SDL2
              spirv-tools
              raylib

              entt
              glm
              glfw
              vulkan-headers
              vulkan-utility-libraries
              xorg.libX11
              xorg.libXcursor
              xorg.libXinerama
              xorg.libXrandr
              xorg.libXi
            ];

            LD_LIBRARY_PATH = pkgs.lib.makeLibraryPath [    
              ogre-with-assimp
              pkgs.boost    
              pkgs.pkg-config
              pkgs.vulkan-loader
              pkgs.vulkan-tools
              pkgs.vulkan-validation-layers
              pkgs.directx-shader-compiler
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

          };
        });
    };
}
