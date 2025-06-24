{pkgs ? import <nixpkgs> {}}:
pkgs.mkShell {
  allowUnfree = true;
  name = "portfolio";
  packages = with pkgs; [
    # for generating ssl certs and keys
    certbot

    # frontend
    bun
  ];
  shellHook = ''
    export PATH="./frontend/node_modules/.bin/:$PATH"
    mkdir -p ./tmp
    export TMPDIR=$(realpath ./tmp)
  '';
}
