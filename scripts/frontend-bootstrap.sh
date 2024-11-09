#!/usr/bin/env bash

# Frontend BOOTSTRAP
# run just but allow building npm projects from project root if they're in subroots

__NAME__="FLSC-portfolio: scripts/frontend-bootstrap"
__DESCRIPTION__="Allows running required build scripts from the comfort of a just file without path issues"
__LICENSE__="BSD 3-Clause License"

if [[ -n $2 ]]; then
  DIR=$2
else
  DIR=frontend
fi

pushd "$DIR" >/dev/null || handle_failure "Failed to pushd to $DIR"

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

    help,  --help,  -h  Prints this message
    dev,   --dev,   -d  Runs the builtin dev command (if available)
    build, --build, -b  Builds the site or webapp c:

Made with <3 by h4rl
Licensed under the ${__LICENSE__}
EOF
}

build() {
  pnpm run build
}

dev() {
  pnpm run dev
}

case $1 in
"build" | "--build" | "-b")
  build
  ;;

"dev" | "--dev" | "-d")
  dev
  ;;

"help" | "--help" | "-h" | *)
  print_help
  ;;

esac

popd >/dev/null || handle_failure "Failed to popd"
