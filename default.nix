{ pkgs ? import <nixpkgs> {} }:
  pkgs.mkShell {
    nativeBuildInputs = with pkgs.buildPackages; [ cmake gnumake sfml ];
    shellHook = ''
        zsh
    '';
}
