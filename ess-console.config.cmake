# Global policies
cmake_policy(SET CMP0043 NEW) # Ignore OLD COMPILE_DEFINITIONS_<Config> properties

# Application definitions
set(applicationVendor       "ECO-Electronics" CACHE INTERNAL "")
set(applicationVendorShort  "ECO-E" CACHE INTERNAL "")
set(applicationName   		  "ECO-E Scripting Console" CACHE INTERNAL "")
set(applicationFileName   	"ess-console" CACHE INTERNAL "")
set(applicationCopyright	  "Copyright 2009-2018" CACHE INTERNAL "")
set(application_VER_MAJOR	  1 CACHE INTERNAL "")
set(application_VER_MINOR	  15 CACHE INTERNAL "")
set(application_BUILD_NUM	  0 CACHE INTERNAL "")	
set(applicationURL          "http://vgromov.ru" CACHE INTERNAL "")
set(applicationVendorEmail  "gromov.vsevolod@yandex.ru" CACHE INTERNAL "")
set(applicationVendorPhone  "+7 (903) 597-52-60" CACHE INTERNAL "")
set(applicationAuthor       "Vsevolod V Gromov" CACHE INTERNAL "")

set(applicationMutex64      "746ADDD3-ABB4-4112-B0F5-59EEEC941281" CACHE INTERNAL "")
set(applicationMutex        "8C7A32A9-ABB4-4112-B0F5-59EEEC941281" CACHE INTERNAL "")

# ES Framework is configured as a part of the external project, skip its local config includes, use ours
set(ESFWX_IS_PART_OF_PROJECT 1 CACHE INTERNAL "")

# ES Framework is not a standalone build, it's being configured as a part of our project
set(ESFWXCONFIG_STANDALONE_BUILD 0 CACHE INTERNAL "")

# ES Framework components use dynamic runtime && are configured to produce shared libraries
set(ESFWXCONFIG_USE_DYNAMIC_RUNTIME 1 CACHE INTERNAL "")
set(ESFWXCONFIG_BUILD_SHARED_LIBS 1 CACHE INTERNAL "")

# Use virtual target folders grouping, basically for MSVC
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# For each subproject, add project current source and build dirs to the include directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Select which parts of ESFWX framework to use. We use all by default
set(ESFWXCONFIG_BUILD_MATH 1 CACHE INTERNAL "")
set(ESFWXCONFIG_BUILD_COMM 1 CACHE INTERNAL "")
set(ESFWXCONFIG_BUILD_SCRIPT 1 CACHE INTERNAL "")

# Set-up ESS Console binary version naming
#
set(ESSCONSOLE_VERSION_SUFFIX "v${application_VER_MAJOR}_${application_VER_MINOR}_${application_BUILD_NUM}" CACHE INTERNAL "")
message(
  STATUS
  "ESSCONSOLE_VERSION_SUFFIX=>${ESSCONSOLE_VERSION_SUFFIX}"
)
