{
  description = "RevEngine";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
    systems.url = "github:nix-systems/default";
  };

  outputs = {
    self,
    nixpkgs,
    systems,
    ...
  }: let
    forEachSystem = f:
      nixpkgs.lib.genAttrs (import systems) (system:
        f {
          pkgs = import nixpkgs {
            inherit system;
          };
        });
  in {
    formatter = forEachSystem ({pkgs, ...}: pkgs.alejandra);

    devShells = forEachSystem ({pkgs, ...}: {
      default = pkgs.mkShell {
        packages = with pkgs; [
          libllvm
          cmake
          gtest
        ];
      };
    });

    packages = forEachSystem ({pkgs, ...}: {
      default = pkgs.stdenv.mkDerivation {
        pname = "RevEngine";
        version = "0.1.0";
        src = ./.;

        nativeBuildInputs = with pkgs; [
          cmake
        ];
        buildInputs = with pkgs; [
          # gtest
        ];
      };
    });

    apps = forEachSystem ({pkgs, ...}: {
      default = {
        type = "app";
        program = "${self.packages.${pkgs.system}.default}/bin/RevEngine";
      };
    });
  };
}
