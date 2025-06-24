backend_path := "." / "backend"
frontend_path := "." / "frontend"
scripts_path := "." / "scripts"

scripts_bootstrap := scripts_path / "bootstrap.sh"

@default:
  just --list

@build-backend:
  {{scripts_bootstrap}} build-backend

@build-frontend:
  {{scripts_bootstrap}} build-frontend

@build-backend-move:
  rm -fr dist/toast || true
  mkdir -p dist/site >/dev/null 2>&1 || true
  just build-backend
  mv backend/target/release/creme-brulee dist/

@build-frontend-move:
  rm -fr dist/site/* || true
  mkdir -p dist/site >/dev/null 2>&1 || true
  just build-frontend
  mv frontend/build/* dist/site/

@build-both:
  just build-backend-move
  just build-frontend-move

@dev-frontend:
  {{scripts_bootstrap}} dev-frontend

@generate-compilation-database:
  {{scripts_bootstrap}} generate-compilation-database

@update-submodules:
  git submodule update --init --recursive
  git submodule foreach git pull origin axum
