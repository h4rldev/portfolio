{pkgs ? import <nixpkgs> {}}:
pkgs.mkShell {
  allowUnfree = true;
  name = "FLSC Portfolio c:";
  packages = with pkgs; [
    # backend

    # clangd
    clang-tools

    # libraries
    file
    libmicrohttpd
    zlib-ng
    jansson

    # ssl
    libgcrypt
    gnutls

    # debugging
    valgrind
    gdb

    # only needed to keep clangd happy me thinks
    bear

    # only for finding linker/c flags
    pkg-config

    # for generating ssl certs and keys
    certbot

    # frontend
    pnpm
  ];
  shellHook = ''
    export PATH="./frontend/node_modules/.bin/:$PATH"
    mkdir ./TMP || true
    mkdir ./frontend/TMP || true
    mkdir ./backend/TMP || true
    export TMPDIR="./TMP"
  '';
}
