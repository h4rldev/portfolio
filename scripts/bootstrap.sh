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
    clear-cores,    --clear-c, --clear-cores     -c   Clears all vgcores
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
  just build-all
  popd >/dev/null || handle_failure "Failed to popd"
}

generate-compilation-database() {
  pushd "backend" >/dev/null || handle_failure "Failed to pushd to backend"
  just generate-compilation-database
  mv compile_commands.json ..
  popd >/dev/null || handle_failure "Failed to popd"
}

dev-frontend() {
  pushd "frontend" >/dev/null || handle_failure "Failed to pushd to frontend"
  pnpm run dev
  popd >/dev/null || handle_failure "Failed to popd"
}

clear_cores() {
  local -a FILES
  local FILE

  FILES=$(find "${PWD}" -type f -name "vgcore.*")

  if [[ -z ${FILES} ]]; then
    echo -e "! No files found :("
    return
  fi

  for FILE in ${FILES}; do
    if [[ -f ${FILE} ]]; then
      rm "${FILE}"
      echo -e "✓ Deleted file \"${FILE}\""
    else
      echo -e "! File does not exist :("
    fi
  done
}

case $1 in
"build-frontend" | "--build-f" | "--build-frontend" | "-bf")
  build-frontend
  ;;

"build-backend" | "--build-b" | "--build-backend" | "-bb")
  build-backend
  ;;

"generate-compilation-database" | "--gen-c" | "--generate-compilation-database" | "-gc")
  generate-compilation-database
  ;;

"dev-frontend" | "--dev-f" | "--dev-frontend" | "-df")
  dev-frontend
  ;;

"clear-cores" | "--clear-c" | "--clear-cores" | "-c")
  clear_cores
  ;;

"help" | "--help" | "-h" | *)
  print_help
  ;;

esac
