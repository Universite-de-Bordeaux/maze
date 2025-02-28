{ pkgs ? import <nixpkgs> {} }:
  pkgs.mkShell {
    nativeBuildInputs = with pkgs.buildPackages; [ cmake gnumake sfml nixd nil ];
    shellHook = ''
        zsh
    '';
}
