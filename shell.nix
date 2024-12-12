{pkgs ? import <nixpkgs> {}}:
pkgs.mkShell {
  allowUnfree = true;
  name = "FLSC Portfolio c:";
  packages = with pkgs; [
    # backend

    # libraries
    file
    libmicrohttpd
    zlib-ng
    jansson

    # ssl
    libgcrypt
    gnutls

    # clangd and clang-format
    clang-tools

    # C beautifier
    uncrustify

    # bash language server and formatters
    bash-language-server
    beautysh
    shfmt

    # nix formatter
    alejandra

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
    nodePackages_latest.svelte-language-server
    nodePackages_latest.typescript-language-server

    # markdown formatting
    mdformat
    cbfmt
  ];
  shellHook = ''
    export PATH="./frontend/node_modules/.bin/:$PATH"
    mkdir ./TMP || true
    export TMPDIR="./TMP"
  '';
}
