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

      devShells = forEachSystem ({ pkgs, ... }:
        let
          JOLT_REPO = pkgs.fetchgit {
            url = "https://github.com/jrouwe/JoltPhysics";
            tag = "v5.5.0";
            hash = "sha256-OQ3kqpd0NBKA0e/YRNCKaSR0wKIto1mcZ+X93CuJ+Dc=";
          };
          
        in {
          default = pkgs.mkShell {

            C_COMPILER = "${pkgs.gcc}/bin/gcc";
            CXX_COMPILER = "${pkgs.gcc}/bin/g++";
            
            JOLT_REPO = JOLT_REPO;
            
            packages = with pkgs; [
              gdb
              cmake
              ninja
              clang
              valgrind
              gcc
              doxygen
              python3
              
              JOLT_REPO

              pkg-config
              vulkan-loader
              vulkan-tools
              vulkan-validation-layers
              directx-shader-compiler
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
            
          };
        });

      packages = forEachSystem ({ pkgs }:
        let
          JOLT_REPO = pkgs.fetchgit {
            url = "https://github.com/jrouwe/JoltPhysics";
            tag = "v5.5.0";
            hash = "sha256-OQ3kqpd0NBKA0e/YRNCKaSR0wKIto1mcZ+X93CuJ+Dc=";
          };
          
        in {
          default = pkgs.stdenv.mkDerivation {
            pname = "RevEngine";
            version = "0.1.0";
            src = ./.;

            C_COMPILER = "${pkgs.gcc}/bin/gcc";
            CXX_COMPILER = "${pkgs.gcc}/bin/g++";
            
            JOLT_REPO = JOLT_REPO;
            
            nativeBuildInputs = with pkgs; [ cmake ninja clang gcc];
            buildInputs = with pkgs; [
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
          };
        });

      apps = forEachSystem ({ pkgs, ... }: {
        default = {
          type = "app";
          program = "${self.packages.${pkgs.system}.default}/bin/RevEngine";
        };
      });
    };
}
