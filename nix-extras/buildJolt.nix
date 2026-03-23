{ lib, stdenv, fetchFromGitHub, cmake, ninja, clang }:

stdenv.mkDerivation rec {
  pname = "joltphysics";
  version = "5.5.0";

  src = fetchFromGitHub {
    owner = "jrouwe";
    repo = "JoltPhysics";
    rev = "v${version}";
    hash = "sha256-OQ3kqpd0NBKA0e/YRNCKaSR0wKIto1mcZ+X93CuJ+Dc=";
  };

  nativeBuildInputs = [ cmake ninja clang ];

  cmakeFlags = [
    "-DCMAKE_BUILD_TYPE=debug"
    "-DJPH_BUILD_SHARED_LIBRARY=ON"
    "-DJPH_BUILD_STATIC_LIBRARY=ON"
    "-DJPH_BUILD_TESTS=ON"
    "-DJPH_BUILD_SAMPLES=ON"

    "-DCMAKE_CXX_COMPILER=clang++"

    "-DJPH_ENABLE_ASSERTS=ON"
    "-DJPH_DEBUG_RENDERER=ON"
    "-DJPH_PROFILE_ENABLED=ON"
    "-DJPH_OBJECT_STREAM=ON"
  ];

  sourceRoot = "${src.name}/Build";

  # installPhase = ''
  #   mkdir -p $out/lib

  #   cp -r ${src}/Jolt/ $out/

  #   find . -name "*.so" -exec cp {} $out/lib/ \;
  #   find . -name "*.a" -exec cp {} $out/lib/ \;

  #   runHook postInstall
  # '';

  meta = with lib; {
    description = "Jolt Physics rigid body physics engine";
    homepage = "https://github.com/jrouwe/JoltPhysics";
    license = licenses.mit;
    platforms = platforms.linux;
  };
}
