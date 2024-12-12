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

@generate_database:
  {{backend_build_script}} -cd

@dev-frontend:
  {{scripts_bootstrap}} dev

@clear_cores:
  {{backend_build_script}} -vg
