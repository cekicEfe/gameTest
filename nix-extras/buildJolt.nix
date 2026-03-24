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

  sourceRoot = "${src.name}/Build";

  configurePhase = ''
    mkdir Linux_Release
    cmake -S . -B Linux_Release -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=g++ -DJPH_BUILD_SHARED_LIBRARY=ON -DJPH_BUILD_STATIC_LIBRARY=ON
  '';

  buildPhase = ''
    cd Linux_Release
    make -j8
  '';

  installPhase = ''
    runHook preInstall

    mkdir -p $out/lib
    mkdir -p $out/include

    cp -r ${src}/Jolt/ $out/include

    find . -name "*.so" -exec cp {} $out/lib/ \;
    find . -name "*.a" -exec cp {} $out/lib/ \;
    cp Linux_Release/JoltConfig.cmake $out/lib 

    runHook postInstall
  '';

  meta = with lib; {
    description = "Jolt Physics rigid body physics engine";
    homepage = "https://github.com/jrouwe/JoltPhysics";
    license = licenses.mit;
    platforms = platforms.linux;
  };
}
