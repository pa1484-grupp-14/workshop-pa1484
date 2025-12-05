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
          CXXFLAGS = "-I${SDL2.dev}/include -L${SDL2}/lib";
          NIX_LD_LIBRARY_PATH = lib.makeLibraryPath [
            stdenv.cc.cc
          ];
          NIX_LD = lib.fileContents "${stdenv.cc}/nix-support/dynamic-linker";
        };
    });
}
