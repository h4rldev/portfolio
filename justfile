backend_path := "." / "backend"
frontend_path := "." / "frontend"

backend_build_script := backend_path / "build" / "build.sh"

@default:
  just --list

@build-backend name="backend":
  {{backend_build_script}} -c
  {{backend_build_script}} -l {{name}}
