# top-level cmakefile for ekosfera framework
cmake_minimum_required(VERSION 3.14)
project(ess-console)

include(${PROJECT_SOURCE_DIR}/escmake/escommon.defs.cmake)

# Must be placed here, after escommon.defs, but before other stuff
include(ess-console.config.cmake)

include(${PROJECT_SOURCE_DIR}/escmake/escompiler.defs.cmake)
include(${PROJECT_SOURCE_DIR}/escmake/eslinker.defs.cmake)

include(${ES_PROJECT_ROOT}/escmake/cmakevars.print.cmake)

#ES_CMAKEVARS_DUMP()

# wxWidgets dependencies, clear wxWidgets cache
set(wxWidgets_DEFINITIONS "" CACHE INTERNAL "" FORCE)
set(wxWidgets_FOUND 0 CACHE INTERNAL "" FORCE)
set(wxWidgets_LIB_DIR "NOTFOUND" CACHE PATH "" FORCE)

# global directories
set(binaryRoot ${ES_PROJECT_ROOT}/bin CACHE INTERNAL "Build binary root")
set(EXECUTABLE_OUTPUT_PATH ${binaryRoot})
set(LIBRARY_OUTPUT_PATH ${binaryRoot})

# wxWidgets tune-up.
#
# We use our own i18n implementation, as long as '_' macro
add_definitions(-DWXINTL_NO_GETTEXT_MACRO)

# add framework && embedded framework directories to the include list
include_directories(	
  ${PROJECT_SOURCE_DIR} 
  ${wxWidgets_ROOT_DIR}/include
	${PROJECT_SOURCE_DIR}/esfwx 
	${PROJECT_SOURCE_DIR}/esfwx/compatibility-headers						
	${PROJECT_SOURCE_DIR}/esfwx/external
  ${PROJECT_SOURCE_DIR}/esfwx-gui
)

# help and manual compiler
#ES_USE_HELP_AND_MANUAL()
# reset i18n aggregation variables
ESI18N_RESET() 

# localization integration variables
set(i18nLanguages "" CACHE INTERNAL "" FORCE)
set(i18nComponents "" CACHE INTERNAL "" FORCE)
set(poPattern ".+[.]([a-z][a-z]_[A-Z][A-Z])[.]po" CACHE INTERNAL "" FORCE)

# meta-project structure
#

# ESFWX framework projects
#

# core libs
add_subdirectory(esfwx)

# core gui libs
add_subdirectory(esfwx-gui)

# Main application
add_subdirectory(main)

# Get WX version string concatenated, to use in setup
string(
  REPLACE 
  "." 
  ""
  ES_WXWIDGETS_VERSION 
  "${ES_WXWIDGETS_VER_STRING}"
)
message(
  STATUS
  "ES_WXWIDGETS_VERSION=>${ES_WXWIDGETS_VERSION}"
)

# overall i18 project
#add_subdirectory(i18n)

add_subdirectory(setup)
