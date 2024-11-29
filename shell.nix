{pkgs ? import <nixpkgs> {}}:
pkgs.mkShell {
  allowUnfree = true;
  name = "FLSC Portfolio c:";
  packages = with pkgs; [
    clang-tools
    bash-language-server
    valgrind
    alejandra
    cbfmt
    mdformat
    beautysh
    libmicrohttpd
    uncrustify
    shfmt
    gdb
    pnpm
    file
    cmake
    nodePackages_latest.svelte-language-server
    nodePackages_latest.typescript-language-server
    zlib-ng
    jansson
    # only for finding linker/c flags
    pkg-config
    certbot
  ];
  shellHook = ''
    export PATH="./frontend/node_modules/.bin/:$PATH"
    mkdir frontend/TMP || true
    export TMPDIR="./TMP"
  '';
}
