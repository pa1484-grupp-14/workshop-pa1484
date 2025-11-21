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
            clang-tools
            platformio
            cmake
            just
          ];
          Arduino_DIR = "${arduino-core}";
          SDL2_INCLUDE_PATH = "${SDL2.dev}/include";
          SDL2_LIBRARY_PATH = "${SDL2}/lib";
          CXXFLAGS = "$CXXFLAGS -I$SDL2_INCLUDE_PATH -L$SDL2_LIBRARY_PATH";
          NIX_LD_LIBRARY_PATH = lib.makeLibraryPath [
            stdenv.cc.cc
          ];
          NIX_LD = lib.fileContents "${stdenv.cc}/nix-support/dynamic-linker";
        };
    });
}
