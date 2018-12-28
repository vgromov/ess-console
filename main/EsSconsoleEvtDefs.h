#ifndef _es_console_evt_defs_h_
#define _es_console_evt_defs_h_

/// Script compiler thread events definitions
///
#define ES_EVTC_COMPILER_THREAD esT("esscompiler_thread")

/// Script compiler thread events
///
enum class EsScriptCompilerEvt : ulong {
  Started,                  ///< Script compilation started. Payload - input name/source file name
  Aborted,                  ///< Script compilation aborted. Payload - [input name/source file name]
  Finished                  ///< Script compilation ended. Payload - [input name/source file name, compilation time, null, if not compiled/compiled script instance]
};

/// Script non-debug runner events definitions
///
#define ES_EVTC_SCRIPT_THREAD   esT("essrunner_thread")

/// Script non-debug runner events
///
enum class EsScriptRunnerEvt : ulong {
  Started,                  ///< Script executor starts running. Payload - [binary file key, optional entry or nullstr, optional params or nullvar]
  Aborted,                  ///< Script executor aborted. Payload - [binary file key]
  Finished                  ///< Script executor finished. Payload - [binary file key, optional entry or nullstr, optional params or nullvar, optional execution errors]
};

/// Application events
///
#define ES_EVTC_APPLICATION     esT("application")

enum class EsSconsoleEvt : ulong {
  DocViewCloseRequest,      ///< Request to close document view, payload - view pointer (wxWindow*)
  DocListCloseRequest,      ///< Request to close document list, payload - collection of keys of documents to be closed
  ApplicationCloseRequest,  ///< Request to close an application. Payload - force unconditional close, true|false
  CompiledScriptChanged,    ///< Compiled binary script singleton document has changed. Payload - compiled script document singleton
  CompiledScriptClosed,     ///< Compiled binary script singleton document has been closed.
  ScriptBrkChangeRequested, ///< Breakpoint state change requested by Script source view. Payload - [script key, source hash, source line, desired state]
  ScriptBtkChangeResponse,  ///< Breakpoint state change response. Payload - [script key, source line, result state]
  ScriptOpenAndSetPosition, ///< Open file and ste position in there. Payload: [file, line, col, isInExecMode]
  DocumentActivate          ///< Opened document activation request. PAyload: file
};

/// Application-specific options
///
#define ES_APP_OPT_TAB_IMG_WH  esT("app.tab.imgwh")
#define ES_APP_OPT_PANE_MIN_WIDTH esT("app.pane.minw")
#define ES_APP_OPT_PANE_MIN_HEIGHT esT("app.pane.minh")

#if defined(__WXMSW__)
# define ES_APP_OPT_AUTO_UPDATE_URL esT("app.au_url")
#endif

/// Custom Command IDs
///
namespace EsSconsoleCmds 
{

  enum {
    /// Event pump timer
    usrID_TMR_EVT_PUMP = escoreguiID_HIGHEST,
    usrID_TMR_EVT_PARSE,
    usrID_TMR_EVT_AUTOCOMP,
    /// Editor Notebook
    usrID_NB_EDITOR,
    /// File commands
    usrID_SAVE_ALL,
    usrID_MRU_CLEAR,
    /// Edit commands
    usrID_EDIT_BOOKMARK_CLEAR_ALL,
    usrID_EDIT_BOOKMARK,
    usrID_EDIT_BOOKMARK0,
    usrID_EDIT_BOOKMARK1,
    usrID_EDIT_BOOKMARK2,
    usrID_EDIT_BOOKMARK3,
    usrID_EDIT_BOOKMARK4,
    usrID_EDIT_BOOKMARK5,
    usrID_EDIT_BOOKMARK6,
    usrID_EDIT_BOOKMARK7,
    usrID_EDIT_BOOKMARK8,
    usrID_EDIT_BOOKMARK9,
    usrID_EDIT_BOOKMARK_NEXT,
    usrID_EDIT_BOOKMARK_PREV,
    usrID_EDIT_GOTO_BOOKMARK0,
    usrID_EDIT_GOTO_BOOKMARK1,
    usrID_EDIT_GOTO_BOOKMARK2,
    usrID_EDIT_GOTO_BOOKMARK3,
    usrID_EDIT_GOTO_BOOKMARK4,
    usrID_EDIT_GOTO_BOOKMARK5,
    usrID_EDIT_GOTO_BOOKMARK6,
    usrID_EDIT_GOTO_BOOKMARK7,
    usrID_EDIT_GOTO_BOOKMARK8,
    usrID_EDIT_GOTO_BOOKMARK9,
    usrID_EDIT_GOTO_CLOSING_BRACE,
    usrID_EDIT_GOTO_OPENING_BRACE,
    usrID_EDIT_CUSTOM_CTX_MENU,
    /// Script commands
    usrID_COMPILE_BREAK,
    usrID_RUN,
    usrID_DEBUG,
    usrID_DEBUG_STEP,
    usrID_RUN_ABORT,
    /// Script editor custom commands
    usrID_SEDIT_FILE_OPEN_AT_CURSOR,
    usrID_SEDIT_FILE_LOCATION_OPEN_AT_CURSOR,
    usrID_SEDIT_LINE_COMMENT_TOGGLE,
    usrID_SEDIT_BLOCK_COMMENT_TOGGLE,
    usrID_SEDIT_CODE_INSIGHT,
    /// Window commands
    usrID_WND_LIST,
    usrID_WND_APPLOG,
    usrID_WND_COMPILELOG,
    /// Options
    usrID_OPT_INCLUDE_DEBUG,
    usrID_OPT_GENERATE_TRANSLATABLES,
    usrID_OPT_INC_PATHS,
    usrID_OPT_LINK_PATHS,
    /// Help
    usrID_HLP_ESCORE,
    usrID_HLP_ESCOMM,
    usrID_HLP_ESMATH,
    usrID_HLP_ESSCRIPT,
    usrID_HLP_ESSCRIPTING,
    usrID_HLP_AUTO_UPDATE,
    usrID_HLP_UPDATE,
    /// Lang ID base idx - MB! must be the last among user IDs item!
    usrID_LANG_ID_BASE,

    // Specific item - highest main frame ID
    usrConsoleMainIdMax = usrID_LANG_ID_BASE + 255
  };

}

#endif // _es_console_evt_defs_h_
