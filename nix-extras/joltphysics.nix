{ lib, stdenv, fetchFromGitHub, cmake, ninja, clang }:

stdenv.mkDerivation rec {
  pname = "joltphysics";
  version = "5.5.0"; # change to desired tag

  # outputs = [ "out" ];

  src = fetchFromGitHub {
    owner = "jrouwe";
    repo = "JoltPhysics";
    rev = "v${version}";
    hash = "sha256-OQ3kqpd0NBKA0e/YRNCKaSR0wKIto1mcZ+X93CuJ+Dc=";
    # run once with fake hash to get real one
  };

  nativeBuildInputs = [ cmake ninja clang ];

  cmakeFlags = [ "-DCMAKE_BUILD_TYPE=Release" "-DJPH_BUILD_SHARED_LIBRARY=ON" ];

  # Jolt builds inside Build/ normally
  sourceRoot = "${src.name}/Build";

  installPhase = ''
    mkdir -p $out/include
    mkdir -p $out/lib

    cp -r ${src}/Jolt $out/include/

    find . -name "libjolt*.so" -exec cp {} $out/lib/ \;
    find . -name "libJolt*.a" -exec cp {} $out/lib/ \;

    runHook postInstall
  '';

  meta = with lib; {
    description = "Jolt Physics rigid body physics engine";
    homepage = "https://github.com/jrouwe/JoltPhysics";
    license = licenses.mit;
    platforms = platforms.linux;
  };
}
