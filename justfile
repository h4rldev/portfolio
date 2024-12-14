backend_path := "." / "backend"
frontend_path := "." / "frontend"
scripts_path := "." / "scripts"

backend_build_script := backend_path / "build" / "build.sh"
scripts_bootstrap := scripts_path / "frontend-bootstrap.sh"

@default:
  just --list

@build-backend name="flscio":
  {{backend_build_script}} -c
  {{backend_build_script}} -l {{name}}

@build-frontend:
  {{scripts_bootstrap}} build

@build-backend-move name="flscio":
  rm -fr dist/{{name}} || true
  mkdir -p dist/site >/dev/null 2>&1 || true
  just build-backend {{name}} 
  mv backend/build/bin/{{name}} dist/

@build-frontend-move:
  rm -fr dist/site/* || true
  mkdir -p dist/site >/dev/null 2>&1 || true
  just build-frontend
  mv frontend/build/* dist/site/


@build-both name="flscio":
  just build-backend-move {{name}}
  just build-frontend-move

@generate_database:
  {{backend_build_script}} -cd

@dev-frontend:
  {{scripts_bootstrap}} dev

@clear_cores:
  {{backend_build_script}} -vg
