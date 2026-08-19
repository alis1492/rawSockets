{ pkgs ? import <nixpkgs> {} }:
pkgs.mkShell {
  packages = with pkgs; [
    gcc
    cmake
    fmt
    pkg-config
  ];

  shellHook = "
    code .
  ";
}
