{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs";
    flake-utils.url = "github:numtide/flake-utils";
  };
  outputs = {
    flake-utils,
    nixpkgs,
    ...
  }:
    flake-utils.lib.eachDefaultSystem (system: let
      pkgs = import nixpkgs {inherit system;};
    in {
      devShells.default = with pkgs;
        mkShell {
          nativeBuildInputs = [];
          packages = [
            clang_20
            clang-tools
            platformio
            cmake
          ];
          shellHook = ''
            export Arduino_DIR="${arduino-core}"
            export SDL2_INCLUDE_PATH="${SDL2.dev}/include"
            export SDL2_LIBRARY_PATH="${SDL2}/lib"
            export CXXFLAGS="$CXXFLAGS -I$SDL2_INCLUDE_PATH -L$SDL2_LIBRARY_PATH"
          '';
        };
    });
}
