cmake_minimum_required(VERSION 3.10)
project(ess-console-app-setup)

# Lookup required MSVC redistributable package
set(CMAKE_INSTALL_DEBUG_LIBRARIES FALSE)
set(CMAKE_INSTALL_UCRT_LIBRARIES FALSE)
set(CMAKE_INSTALL_MFC_LIBRARIES FALSE)
include(InstallRequiredSystemLibraries)

string(
  REGEX MATCH
  "[/]([0-9][0-9][0-9][0-9])[/]"
  MSVC_REDIST_YEAR
  ${MSVC_REDIST_DIR}
)
set(MSVC_REDIST_YEAR ${CMAKE_MATCH_1})

# Generate application version file generation
#
configure_file (
  "${PROJECT_SOURCE_DIR}/setup_defs.iss.in"
  "${PROJECT_SOURCE_DIR}/setup_defs.iss"
)

if(${CMAKE_FORCE_WIN64})
  set(SETUP_BITS 64)
else()
  set(SETUP_BITS 32)
endif()

set(SETUP_OUTPUT_DIR  ${binaryRoot}/setup)
set(SETUP_OUTPUT_NAME ${applicationFileName}.${application_VER_MAJOR}.${application_VER_MINOR}.${application_BUILD_NUM}.setup${SETUP_BITS}.exe)

if( NOT DEFINED ENV{ISS_ROOT} )
  message(
    SEND_ERROR 
    "Inno Setup Script binary root environment variable ISS_ROOT not found!"
  )
endif()

set(ISCC $ENV{ISS_ROOT}/iscc.exe)

add_custom_target(
  setup
  ${ISCC} /DSETUP_BITS=${SETUP_BITS} ${PROJECT_SOURCE_DIR}/setup.iss
  COMMENT "Building ${applicationFileName} setup file: ${SETUP_OUTPUT_DIR}/${SETUP_OUTPUT_NAME}"
)

add_custom_target(
  documentation
  ${ESFWX_SOURCE_ROOT}/build_docs.bat
  WORKING_DIRECTORY ${ESFWX_SOURCE_ROOT}
  COMMENT "Building and preparing documentation..."
)

add_dependencies(
  setup
  ${ess_console_Exe}
  ${documentation}
)

#ES_CMAKEVARS_DUMP()
