cmake_minimum_required(VERSION 3.10)
project(ess-console-app-setup)

# Generate application version file generation
#
configure_file (
  "${PROJECT_SOURCE_DIR}/setup_defs.iss.in"
  "${PROJECT_SOURCE_DIR}/setup_defs.iss"
)
