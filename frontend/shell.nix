{pkgs ? import <nixpkgs> {}}:
with pkgs;
  mkShell {
    allowUnfree = true;
    name = "portfolio";
    packages = with pkgs; [
      # for generating ssl certs and keys
      certbot

      just

      # frontend
      bun
      biome
      rustywind
      svelte-language-server
    ];
    shellHook = ''
      export PATH="./node_modules/.bin/:$PATH"
    '';
  }
