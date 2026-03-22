{ stdenv, lib, cmake,  fetchFromGitHub, }:

stdenv.mkDerivation rec {
  pname = "flecs";
  version = "4.1.5";
  outputs = [ "out" "lib" ];

  src = fetchFromGitHub {
    owner = "SanderMertens";
    repo = "flecs";
    tag = "v${version}";
    hash = "sha256-FqYIXpbYYRFEUL9enK+BWhuHIgvzO3dc2cd5CTYveag=";
  };

  nativeBuildInputs = [ cmake ];

  meta = {
    homepage = "https://github.com/SanderMertens/flecs";
    license = lib.licenses.mit;
    maintainers = with lib.maintainers; [ ];
    platforms = lib.platforms.all;
  };
}
