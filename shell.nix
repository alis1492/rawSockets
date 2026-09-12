{ pkgs ? import <nixpkgs> {} }:
pkgs.mkShell {
  packages = with pkgs; [
    gcc16
    cmake
    fmt
    pkg-config
  ];

  shellHook = "
    code .
  ";
}
