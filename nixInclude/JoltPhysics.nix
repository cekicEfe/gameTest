{ lib
, stdenv
, fetchFromGitHub
, cmake
}:

stdenv.mkDerivation rec {
  pname = "jolt-physics";
  version = "5.5.0";

  src = fetchFromGitHub {
    owner = "jrouwe";
    repo = "JoltPhysics";
    rev = "v${version}";
    hash = ""; 
  };

  nativeBuildInputs = [
    cmake
  ];

  cmakeFlags = [
    "-DBUILD_SHARED_LIBS=ON"
    "-DTARGET_SAMPLES=OFF"
    "-DTARGET_UNIT_TESTS=OFF"
    "-DTARGET_HELLO_WORLD=OFF"
    "-DTARGET_PERFORMANCE_TEST=OFF"
  ] ++ lib.optionals stdenv.isx86_64 [
    "-DUSE_SSE4_2=ON"
    "-DUSE_AVX2=ON"
  ];

  cmakeDir = "Build";

  meta = with lib; {
    description = "A multi core friendly rigid body physics and collision detection library";
    homepage = "https://github.com/jrouwe/JoltPhysics";
    license = licenses.mit;
    platforms = platforms.all;
    maintainers = [ ]; 
  };
}
