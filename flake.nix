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

      #      JOLT_REPO = 

    in {

      formatter = forEachSystem ({ pkgs, ... }: pkgs.alejandra);

      devShells = forEachSystem ({ pkgs, ... }: {
        default =
          pkgs.mkShell { packages = with pkgs; [ libllvm cmake gtest ]; };
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

            JOLT_REPO = JOLT_REPO;

            nativeBuildInputs = with pkgs; [ cmake ninja clang ];
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
