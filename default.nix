{pkgs ? import <nixpkgs> {
 }}:
pkgs.mkShell {
  buildInputs = with pkgs; [
    cmake
    gnumake
    sfml
  ];
  shellHook = ''
    zsh
  '';
}
