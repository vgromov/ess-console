cmake_minimum_required(VERSION 3.7)
project(ess-console-app)

# wxWidgets dependencies
set(wxWidgets_USE_LIBS base core adv aui stc)
find_package(wxWidgets 3.1.1 REQUIRED)
set(ES_WXWIDGETS_VER_STRING ${wxWidgets_VERSION_STRING} CACHE INTERNAL "" FORCE)

include(${wxWidgets_USE_FILE})

# set-up link directories for wxWidgets
link_directories(
  ${wxWidgets_LIB_DIR}
)

# Generate application version file generation
#
configure_file (
  "${PROJECT_SOURCE_DIR}/product_version.h.in"
  "${PROJECT_SOURCE_DIR}/product_version.h"
)

# Generate Resource version file
#
configure_file (
  "${PROJECT_SOURCE_DIR}/res/version.rc.in"
  "${PROJECT_SOURCE_DIR}/res/version.rc"
)

# project top-level build directory
# ADD HERE

# project source files
set(ess_console_DocMgr
  EsDocument.cpp
  EsDocument.h
  EsDocumentManagerIntf.h
  EsDocumentManager.cpp
  EsDocumentManager.h
  EsScriptDocument.cpp
  EsScriptDocument.h
  EsCompiledScriptDocument.cpp
  EsCompiledScriptDocument.h
  EsTextDocument.cpp
  EsTextDocument.h
)
source_group(doc_mgr FILES ${ess_console_DocMgr})

set(ess_console_SynPrefs
  EsSyntaxHighlighterPreferences.cpp
  EsSyntaxHighlighterPreferences.h
)
source_group(synprefs FILES ${ess_console_SynPrefs})

set(ess_console_Views
  EsTextEditorViewBase.cpp
  EsTextEditorViewBase.h
  EsTextEditorView.cpp
  EsTextEditorView.h
  EsScriptEditorView.cpp
  EsScriptEditorView.h
  EsCompiledScriptView.cpp
  EsCompiledScriptView.h
  EsSconsoleOutputBase.cpp
  EsSconsoleOutputBase.h
  EsSconsoleCompilerOutput.cpp
  EsSconsoleCompilerOutput.h
  EsSconsoleScriptOutput.cpp
  EsSconsoleScriptOutput.h
  EsOpenedDocumentList.cpp
  EsOpenedDocumentList.h
  EsCodeInsightView.cpp
  EsCodeInsightView.h
)
source_group(views FILES ${ess_console_Views})

set(ess_console_Main
  EsPathsListDlg.cpp
  EsPathsListDlg.h
  EsSconsoleApp.cpp
  EsSconsoleApp.h
  EsSconsoleEvtDefs.h
  EsSconsoleMain.cpp
  EsSconsoleMain.h
  EsSconsoleParams.cpp
  EsSconsoleParams.h
)
source_group(main FILES ${ess_console_Main})

set(ess_console_SRCS
  #ess_console.cpp is included from precompiled header configuration section
  ${ess_console_DocMgr}
  ${ess_console_SynPrefs}
  ${ess_console_Views}
  ${ess_console_Main}
)

set(ess_console_RES
	res/ess_console_Icon.ico
)
if(WIN32)
	set(ess_console_RES ${ess_console_RES} 
	  res/res.rc
		res/version.rc
  )
  source_group(res FILES ${ess_console_RES})						
endif(WIN32)						

# targets
set(ess_console_Exe ess-console_${ESSCONSOLE_VERSION_SUFFIX}_${ESCOMMON_BIN_SUFFIX}${ESCOMMON_COMPILER_VERSION} CACHE INTERNAL "" FORCE)

ES_SPECIFY_PRECOMPILED_HEADER("ess_console_pch.h" "ess_console.cpp" ess_console_SRCS)
ES_SPECIFY_HEADER_FILES(ess_console_SRCS ${ES_HEADER_EXTENSIONS})

if(WIN32)
  add_executable( 
    ${ess_console_Exe} 
    WIN32 
    ${ess_console_RES}
    ${ess_console_SRCS}
  )
elseif(MACOSX_BUNDLE)
  add_executable( 
    ${ess_console_Exe} 
    MACOSX_BUNDLE 
    ${ess_console_RES}
    ${ess_console_SRCS}
  )
else()
  add_executable( 
    ${ess_console_Exe} 
    ${ess_console_RES}
    ${ess_console_SRCS}
  )
endif()

# Show current WX linkage status
message(
  STATUS
  "${ess_console_Exe} is linking to WX: ${wxWidgets_LIBRARIES}"
)

target_link_libraries( 
  ${ess_console_Exe} 
	${wxWidgets_LIBRARIES} 
	${escoreLib}
	${escommLib} 
	${esmathLib} 
	${esscriptLib}
  ${escoreguiLib}
)

# Set-up definitions and options
if( ES_BUILD_SHARED_LIBS )
  list(
    APPEND 
    ESSCON_DEFS ${ES_USEDLL_PREPROC_FOR_EXE}
  )
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
  if(NOT MINGW AND (CMAKE_BUILD_TYPE STREQUAL "Debug"))
    set(ESSCON_OPTS "-rdynamic")
  endif()
endif()
if(MINGW)
  if(ESSCON_OPTS)
    set(
      ESSCON_OPTS
      "${ESSCON_OPTS} -mwindows -municode"
    )
  else()
    set(
      ESSCON_OPTS
      "-windows -municode"
    )
  endif()
endif()

if( BORLAND OR EMBARCADERO )
  set(
    ESSCON_OPTS
    "${ESSCON_OPTS} ${CMAKE_CREATE_EXE}"
  )
endif()

set_target_properties(
  ${ess_console_Exe}
  PROPERTIES
  LINK_FLAGS "${ESSCON_OPTS}"
  COMPILE_DEFINITIONS "${ESSCON_DEFS}"
)

message(
  STATUS
  "${targetName} ESSCON_DEFS=>${ESSCON_DEFS} ESSCON_OPTS=>${ESSCON_OPTS}"
)
