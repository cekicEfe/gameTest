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
        jp = pkgs.callPackage ./nix-extras/joltphysics.nix { };
      in {
        devShell = pkgs.mkShell {

          # Dependencies for project
          buildInputs = [
            pkgs.gcc
            pkgs.cmake
            pkgs.valgrind
            pkgs.gf

            pkgs.stb
            pkgs.raylib
            pkgs.entt
            jp
          ];

          #links libraries to shell
          LD_LIBRARY_PATH = pkgs.lib.makeLibraryPath [
            #
            pkgs.stb
            pkgs.raylib
            pkgs.entt
            jp
          ];

          shellHook = ''
            PS1="[\\u@\\h && CPP-DEV-ENV:\\w]\$ "
          '';
        };
      });
}
