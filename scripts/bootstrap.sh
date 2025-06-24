#!/usr/bin/env bash

# BOOTSTRAP
# Run just but allow building projects from project root if they're in subroots

__NAME__="FLSC-portfolio: scripts/bootstrap"
__DESCRIPTION__="Allows running required build scripts from the comfort of a just file without path issues"
__LICENSE__="BSD 3-Clause License"

handle_failure() {
  echo "$1"
  exit 1
}

print_help() {
  cat <<EOF
${__NAME__} 
${__DESCRIPTION__}
USAGE: ${0} [FLAGS/OPTIONS]

FLAGS/OPTIONS:

    help,           --help,    -h                     Prints this message
    build-frontend, --build-f, --build-frontend, -bf  Builds the frontend
    build-backend,  --build-b, --build-backend,  -bb  Builds the backend
    dev-frontend,   --dev-f,   --dev-frontend,   -df  Starts the frontend dev server

Made with <3 by h4rl
Licensed under the ${__LICENSE__}
EOF
}

build-frontend() {
  pushd "frontend" >/dev/null || handle_failure "Failed to pushd to frontend"
  pnpm run build
  popd >/dev/null || handle_failure "Failed to popd"
}

build-backend() {
  pushd "backend" >/dev/null || handle_failure "Failed to pushd to backend"
  just build-release
  popd >/dev/null || handle_failure "Failed to popd"
}

dev-frontend() {
  pushd "frontend" >/dev/null || handle_failure "Failed to pushd to frontend"
  pnpm run dev
  popd >/dev/null || handle_failure "Failed to popd"
}

case $1 in
"build-frontend" | "--build-f" | "--build-frontend" | "-bf")
  build-frontend
  ;;

"build-backend" | "--build-b" | "--build-backend" | "-bb")
  build-backend
  ;;

"dev-frontend" | "--dev-f" | "--dev-frontend" | "-df")
  dev-frontend
  ;;

"help" | "--help" | "-h" | *)
  print_help
  ;;

esac
