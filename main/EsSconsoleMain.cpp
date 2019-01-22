#include "ess_console_pch.h"
#pragma hdrstop

#include <wx/aboutdlg.h>
#include <wx/mimetype.h>

#include "EsSconsoleMain.h"

#if ES_OS != ES_OS_WINDOWS
# include "res/appicon.xpm"
#endif

// Custom art
#include "res/bookmark_16x16.xpm"
#include "res/script_file_16x16.xpm"
#include "res/bmgeneric_16x16.xpm"
#include "res/bm0_16x16.xpm"
#include "res/bm1_16x16.xpm"
#include "res/bm2_16x16.xpm"
#include "res/bm3_16x16.xpm"
#include "res/bm4_16x16.xpm"
#include "res/bm5_16x16.xpm"
#include "res/bm6_16x16.xpm"
#include "res/bm7_16x16.xpm"
#include "res/bm8_16x16.xpm"
#include "res/bm9_16x16.xpm"
#include "res/execline_16x16.xpm"
#include "res/brk_16x16.xpm"
#include "res/brk_inactive_16x16.xpm"
#include "res/brk_invalid_16x16.xpm"

#include "res/ac_attrs_16x16.xpm"
#include "res/ac_consts_16x16.xpm"
#include "res/ac_enumItems_16x16.xpm"
#include "res/ac_enums_16x16.xpm"
#include "res/ac_globfuncs_16x16.xpm"
#include "res/ac_gvars_16x16.xpm"
#include "res/ac_keywords_16x16.xpm"
#include "res/ac_objects_16x16.xpm"
#include "res/ac_ofields_16x16.xpm"
#include "res/ac_ofuncs_16x16.xpm"
#include "res/ac_oprops_16x16.xpm"
#include "res/ac_ovars_16x16.xpm"
#include "res/ac_svcs_16x16.xpm"
#include "res/ac_varsvcs_16x16.xpm"

#include "res/save_16x16.xpm"
#include "res/save_as_16x16.xpm"
#include "res/save_all_16x16.xpm"
#include "res/select_all_16x16.xpm"
#include "res/compile_16x16.xpm"
#include "res/execute_16x16.xpm"
#include "res/debug_16x16.xpm"
#include "res/debug_pause_16x16.xpm"
#include "res/debug_step_16x16.xpm"
#include "res/abort_16x16.xpm"
#include "res/close_16x16.xpm"
#include "res/close_all_16x16.xpm"
#include "res/close_window_16x16.xpm"
#include "res/help_16x16.xpm"
#include "res/info_16x16.xpm"
#include "res/module_help_16x16.xpm"
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
// Custom wxArtProvider
//
class EsSconsoleArtProvider : public wxArtProvider
{
protected:
  virtual wxBitmap CreateBitmap(const wxArtID& id, const wxArtClient& client, const wxSize& ES_UNUSED(sze)) ES_OVERRIDE
  {
    if( esART_STC_MARGIN == client )
    {
      if( esART_BOOKMARK == id )
        return wxBitmap(bmgeneric_16x16_xpm);
      if( esART_BOOKMARK_0 == id )
        return wxBitmap(bm0_16x16_xpm);
      if( esART_BOOKMARK_1 == id )
        return wxBitmap(bm1_16x16_xpm);
      if( esART_BOOKMARK_2 == id )
        return wxBitmap(bm2_16x16_xpm);
      if( esART_BOOKMARK_3 == id )
        return wxBitmap(bm3_16x16_xpm);
      if( esART_BOOKMARK_4 == id )
        return wxBitmap(bm4_16x16_xpm);
      if( esART_BOOKMARK_5 == id )
        return wxBitmap(bm5_16x16_xpm);
      if( esART_BOOKMARK_6 == id )
        return wxBitmap(bm6_16x16_xpm);
      if( esART_BOOKMARK_7 == id )
        return wxBitmap(bm7_16x16_xpm);
      if( esART_BOOKMARK_8 == id )
        return wxBitmap(bm8_16x16_xpm);
      if( esART_BOOKMARK_9 == id )
        return wxBitmap(bm9_16x16_xpm);
      if( esART_EXECLINE == id )
        return wxBitmap(execline_16x16_xpm);
      if( esART_BRK_ACTIVE == id )
        return wxBitmap(brk_16x16_xpm);
      if( esART_BRK_INACTIVE == id )
        return wxBitmap(brk_inactive_16x16_xpm);
      if( esART_BRK_INVALID == id )
        return wxBitmap(brk_invalid_16x16_xpm);
    }
    else if( esART_STC_AUTOCOMPL == client )
    {
      if( esART_AC_ATTRS == id )
        return wxBitmap(ac_attrs_16x16_xpm);
      if( esART_AC_CONSTS == id )
        return wxBitmap(ac_consts_16x16_xpm);
      if( esART_AC_ENUM_ITEMS == id )
        return wxBitmap(ac_enumItems_16x16_xpm);
      if( esART_AC_ENUMS == id )
        return wxBitmap(ac_enums_16x16_xpm);
      if( esART_AC_GLOBFUNCS == id )
        return wxBitmap(ac_globfuncs_16x16_xpm);
      if( esART_AC_GLOBVARS == id )
        return wxBitmap(ac_gvars_16x16_xpm);
      if( esART_AC_KEYWORDS == id )
        return wxBitmap(ac_keywords_16x16_xpm);
      if( esART_AC_OBJECTS == id )
        return wxBitmap(ac_objects_16x16_xpm);
      if( esART_AC_OBJFIELDS == id )
        return wxBitmap(ac_ofields_16x16_xpm);
      if( esART_AC_OBJFUNCS == id )
        return wxBitmap(ac_ofuncs_16x16_xpm);
      if( esART_AC_OBJPROPS == id )
        return wxBitmap(ac_oprops_16x16_xpm);
      if( esART_AC_OBJVARS == id )
        return wxBitmap(ac_ovars_16x16_xpm);
      if( esART_AC_SERVICES == id )
        return wxBitmap(ac_svcs_16x16_xpm);
      if( esART_AC_VARSVCS == id )   
        return wxBitmap(ac_varsvcs_16x16_xpm);
    }
    else
    {
      if(wxART_FILE_SAVE == id)
        return wxBitmap(save_16x16_xpm);
      if(wxART_FILE_SAVE_AS == id)
        return wxBitmap(save_as_16x16_xpm);
      if(esART_BOOKMARK == id)
        return wxBitmap(bookmark_16x16_xpm);
      if(esART_SCRIPT_FILE == id)
        return wxBitmap(script_file_16x16_xpm);
      if(esART_SELECT_ALL == id)
        return wxBitmap(select_all_16x16_xpm);
      if(esART_COMPILE == id)
        return wxBitmap(compile_16x16_xpm);
      if(esART_RUN == id)
        return wxBitmap(execute_16x16_xpm);
      if(esART_DEBUG_RUN == id)
        return wxBitmap(debug_16x16_xpm);
      if(esART_DEBUG_PAUSE == id)
        return wxBitmap(debug_pause_16x16_xpm);
      if(esART_DEBUG_STEP == id)
        return wxBitmap(debug_step_16x16_xpm);
      if(esART_ABORT == id)
        return wxBitmap(abort_16x16_xpm);
      if(esART_SAVE_ALL == id)
        return wxBitmap(save_all_16x16_xpm);
      if(esART_CLOSE == id)
        return wxBitmap(close_16x16_xpm);
      if(esART_CLOSE_ALL == id)
        return wxBitmap(close_all_16x16_xpm);
      if(wxART_CLOSE == id)
        return wxBitmap(close_window_16x16_xpm);
      if(wxART_HELP == id)
        return wxBitmap(help_16x16_xpm);
      if(esART_INFO == id)
        return wxBitmap(info_16x16_xpm);
      if (esART_HELP_MODULE == id)
        return wxBitmap(module_help_16x16_xpm);
    }

    return wxNullBitmap;
  }
};

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

EsSconsoleOptions::EsSconsoleOptions() :
  m_fntTxt(nullptr),
  m_fntLineNum(nullptr)
{
  init();
}
//--------------------------------------------------------------------------------

void EsSconsoleOptions::init()
{
  m_fntTxt = wxTheFontList->FindOrCreateFont(
    10,
    wxFONTFAMILY_MODERN,
    wxFONTSTYLE_NORMAL,
    wxFONTWEIGHT_NORMAL
  );
  ES_ASSERT(m_fntTxt);

  m_fntLineNum = wxTheFontList->FindOrCreateFont(
    8,
    wxFONTFAMILY_SWISS,
    wxFONTSTYLE_NORMAL,
    wxFONTWEIGHT_NORMAL
  );
  ES_ASSERT(m_fntLineNum);
}
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

EsSconsoleMain::EvtHandler::EvtHandler(EsSconsoleMain& owner) ES_NOTHROW :
EsEventSubscriber(
  ES_EVTC_APPLICATION EVTC_AND
  ES_EVTC_MDI EVTC_AND
  ES_EVTC_COMPILER_THREAD EVTC_AND
  ES_EVTC_SCRIPT_DEBUG_RSP EVTC_AND
  ES_EVTC_SCRIPT_THREAD EVTC_AND
  ES_EVTC_I18N
),
m_owner(owner)
{}
//--------------------------------------------------------------------------------

void EsSconsoleMain::EvtHandler::notify(const EsEventIntf::Ptr& evt)
{
  ES_ASSERT(evt);

  const EsString& cat = evt->categoryGet();
  ulong id = evt->idGet();
  const EsVariant& payload = evt->payloadGet();

  if(ES_EVTC_MDI == cat)
  {
    switch(as_<EsMdiEvt>(id))
    {
    case EsMdiEvt::DocumentChanged:
      m_owner.onDocumentChanged(
        payload[0].asString(),
        payload[1].asString(),
        payload[2].asPointer()
      );
      break;
    case EsMdiEvt::DocumentStateChanged:
      m_owner.onDocumentStateChanged(
        payload.asString()
      );
      break;
    case EsMdiEvt::DocumentCreated:
      m_owner.onDocumentCreated(
        payload[0].asString(),
        payload[1]
      );
      break;
    case EsMdiEvt::DocumentOpened:
      m_owner.onDocumentOpened(
        payload[0].asString(),
        payload[1]
      );
      break;
    case EsMdiEvt::DocumentClosed:
      m_owner.onDocumentClosed(
        payload[0].asString(),
        payload[1].asString()
      );
      break;
    case EsMdiEvt::DocumentKeyChanged:
      m_owner.onDocumentKeyChanged(
        payload[0].asString(),
        payload[1].asString()
      );
      break;
    case EsMdiEvt::AllDocumentsClosed:
      m_owner.onAllDocumentsClosed();
      break;
    }
  }
  else if(ES_EVTC_COMPILER_THREAD == cat)
  {
    switch(as_<EsScriptCompilerEvt>(id))
    {
    case EsScriptCompilerEvt::Started:
      m_owner.onCompilationStart();
      break;
    case EsScriptCompilerEvt::Aborted:
      m_owner.onCompilationAborted();
      break;
    case EsScriptCompilerEvt::Finished:
      m_owner.onCompilationEnd(
        payload[0].asString(),
        payload[2].isEmpty() ?            //< Compilation errors/compiled script
        EsVariant::nullObject() :
        payload[2].asExistingObject()
      );
      break;
    }
  }
  else if(ES_EVTC_SCRIPT_THREAD == cat)
  {
    switch(as_<EsScriptRunnerEvt>(id))
    {
    case EsScriptRunnerEvt::Finished:
      m_owner.onScriptFinished(
        0 < payload[3].countGet() //< Have some errors
      );
      break;
    case EsScriptRunnerEvt::Aborted:
      m_owner.onScriptAborted();
      break;
    }
  }
  else if( ES_EVTC_SCRIPT_DEBUG_RSP == cat )
  {
    switch( as_<EsScriptDebugEvt>(id) )
    {
    case EsScriptDebugEvt::Paused:
      m_owner.onScriptDebugPaused(
        payload[0].asString(),
        payload[1].asULong(),
        payload[2].asBool()
      );
    case EsScriptDebugEvt::Started:
    case EsScriptDebugEvt::Continued:
    case EsScriptDebugEvt::Aborted:
    case EsScriptDebugEvt::Finished:
      m_owner.scriptDebugLabelsAndIconsUpdate();
      break;
    }
  }
  else if(ES_EVTC_I18N == cat && EsEvtI18n::LocaleChanged == as_<EsEvtI18n>(id))
  {
    m_owner.onI18nLocaleChanged(
      evt->payloadGet().asString()
    );
  }
  else if(ES_EVTC_APPLICATION == cat)
  {
    switch(as_<EsSconsoleEvt>(id))
    {
    case EsSconsoleEvt::DocViewCloseRequest:
      m_owner.onDocumentViewCloseRequest(
        reinterpret_cast<wxWindow*>(payload.asPointer())
      );
      break;
    case EsSconsoleEvt::DocListCloseRequest:
      m_owner.onDocumentListCloseRequest(
        payload.asStringCollection()
      );
      break;
    case EsSconsoleEvt::ApplicationCloseRequest:
      m_owner.Close( payload.asBool() );
      break;
    case EsSconsoleEvt::ScriptOpenAndSetPosition:
      m_owner.documentOpenAndSetPosition(
        payload[0].asString(),
        payload[1],
        payload[2],
        payload[3].asBool()
      );
      break;
    case EsSconsoleEvt::DocumentActivate:
      m_owner.onDocumentActivate(
        payload.asString()
      );
      break;
    }
  }
}
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
// Script compiler worker thread
//

EsSconsoleMain::Compiler::Compiler(EsSconsoleMain& owner) :
  EsThread(),
  m_owner(owner),
  m_srcIsText(false),
  m_compiledOk(false)
{
  m_scriptBinary = EsScript::create();
  ES_ASSERT(m_scriptBinary);
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::Compiler::sourceSet(const EsString& src, bool isText)
{
  m_src = src;
  m_srcIsText = isText;
  m_srcTextName = EsString::null();
  m_compiledOk = false;
}
//--------------------------------------------------------------------------------

long EsSconsoleMain::Compiler::worker()
{
  EsBreakIntf::Ptr brk = threadStateProxyGet();

  if(m_srcIsText)
    m_compiledOk = m_scriptBinary->compileText(
      m_src,
      brk
    );
  else
    m_compiledOk = m_scriptBinary->compileFile(
      m_src,
      brk
    );

  return 0;
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::Compiler::onEnterWorker()
{
  m_start = EsDateTime::now();
  EsEventDispatcher::eventPost(
    ES_EVTC_COMPILER_THREAD,
    as_<ulong>(EsScriptCompilerEvt::Started),
    m_srcIsText ?
    m_srcTextName :
    m_src
  );
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::Compiler::onExitWorker()
{
  if(EsThreadState::Stopping == m_state)
  {
    EsEventDispatcher::eventPost(
      ES_EVTC_COMPILER_THREAD,
      as_<ulong>(EsScriptCompilerEvt::Aborted),
      m_srcIsText ?
      m_srcTextName :
      m_src
    );
  }
  else
  {
    const EsString::Array& errors = errorLogGet();
    EsVariant::Array payload = {
      m_srcIsText ?
        m_srcTextName :
        m_src,
      EsTimeSpan::toVariant(
        EsDateTime::now() - m_start
      )
    };

    if(errors.empty() && m_compiledOk)
    {
      payload.push_back(
        m_scriptBinary
      );
    }
    else
      payload.push_back(
        EsVariant::null()
      );

    EsEventDispatcher::eventPost(
      ES_EVTC_COMPILER_THREAD,
      as_<ulong>(EsScriptCompilerEvt::Finished),
      payload
    );
  }
}

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

EsString EsSconsoleMain::settingsPathGet()
{
  const EsPath& path = EsPath::create(
    EsSconsoleApp::settingsFolderGet(),
    esT("gui.settings"),
    esT("xml")
  );

  return path.pathGet();
}
//--------------------------------------------------------------------------------

EsString EsSconsoleMain::defaultEncKeyGet()
{
  static const GUID c_keyDef = {0xB7013BFB, 0xD65C, 0x5346, 0x93, 0xD0, 0x71, 0xF4, 0xF3, 0xC2, 0x8D, 0xD4};
  return EsUtilities::GUIDtoStr(c_keyDef);
}
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

using namespace EsSconsoleCmds;
//--------------------------------------------------------------------------------

EsSconsoleMain::EsSconsoleMain() :
wxFrame(
  nullptr,
  wxID_ANY,
  wxGetApp().GetAppDisplayName(),
  wxDefaultPosition,
  EsUtilities::appMainFrameMinSizeGet(),
  wxDEFAULT_FRAME_STYLE
),
#if ES_OS_WINDOWS == ES_OS
m_au(
  FRAMEWORK_VENDOR_SHORT,
  PRODUCT_NAME,
  PRODUCT_VER_STR
),
#endif
m_compiler(*this),
m_handler(*this),
m_tmrEvtPump(
  this,
  usrID_TMR_EVT_PUMP
),
m_mru(
  wxID_FILE9-wxID_FILE+1,
  wxID_FILE
),
m_mnu(nullptr),
m_mnuFile(nullptr),
m_mnuFileMRU(nullptr),
m_mnuEdit(nullptr),
m_mnuEditBm(nullptr),
m_mnuWindow(nullptr),
m_mnuScript(nullptr),
m_mnuOptions(nullptr),
m_mnuHelp(nullptr),
m_sb(nullptr),
m_tb(nullptr),
m_nbEditor(nullptr),
m_log(nullptr),
m_logComp(nullptr),
m_docList(nullptr),
m_batchCmds(nullptr),
m_activeView(nullptr),
m_dlgFr(nullptr),
m_initialized(false),
m_compiling(false),
m_compiledOk(false),
m_changingDocptrs(false)
{
  wxArtProvider::Push(
    new EsSconsoleArtProvider
  );

  SetIcon(wxICON(appicon));
  SetMinSize(
    EsUtilities::appMainFrameMinSizeGet()
  );

  m_dataFr.SetFlags(wxFR_DOWN);

  m_docPtrs.m_docPtrType = DocPtrType::None;
  m_docPtrs.m_rawPtr = nullptr;
  m_docPtrs.m_compiledDocPtr = nullptr;

  m_mgrAui.SetFlags(
    m_mgrAui.GetFlags() |
    wxAUI_MGR_LIVE_RESIZE
  );
  m_mgrAui.SetManagedWindow(this);
}
//--------------------------------------------------------------------------------

EsSconsoleMain::~EsSconsoleMain()
{
  wxDELETE(m_dlgFr);
  m_compiler.stopAndWait();
  evtHandlersUninit();
  m_mgrAui.UnInit();
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::init()
{
  if(m_initialized)
    return;

  mdiInit();
  layoutInit();
  evtHandlersInit();

  m_initialized = true;

  m_tmrEvtPump.StartOnce(evtPumpTmo);

#if ES_OS_WINDOWS == ES_OS
  m_au.updateCastUrlSet(
    wxSystemOptions::GetOption(ES_APP_OPT_AUTO_UPDATE_URL).t_str()
  );
  m_au.updateCheck(false);
#endif
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::batchExecute(const EsSconsoleCommandLineParams& cmds)
{
  ES_ASSERT(!cmds.m_empty);
  m_batchCmds = nullptr;

  if(!cmds.m_inFile.empty())
  {
    ES_DEBUG_TRACE(esT("EsSconsoleMain::batchExecute"));

    m_batchCmds = &cmds;

    const EsString& type = cmds.m_inFileIsBin ?
      EsCompiledScriptDocument::classNameGetStatic() :
      EsScriptDocument::classNameGetStatic();

    EsVariant params;

    if(!cmds.m_inFileIsEncrypted)
      params = cmds.m_inFile;
    else
    {
      params.setToNull(EsVariant::VAR_VARIANT_COLLECTION);
      params.addToVariantCollection(cmds.m_inFile);
      params.addToVariantCollection(
        settingsToCompiledScriptDocumentParams(
          defaultEncKeyGet()
        )
      );
    }

    EsDocumentIntf::Ptr doc = m_mgrMdi->documentOpen(
      type,
      params
    ).asObject();
    ES_ASSERT(doc);

    commonAppSettingsApply(false);

    if(!cmds.m_inFileIsBin)
      scriptCompile(doc);

    // The rest batch is done in response to document creation handler
  }
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::settingsLoad()
{
  if(!m_settings)
  {
    const EsString& path = settingsPathGet();
    m_settings = EsStreamXml::create(
      as_<ulong>(EsStreamFlag::Read)|
      as_<ulong>(EsStreamFlag::Write)|
      as_<ulong>(EsStreamFlag::File),
      path
    );
  }

  {
    EsStreamContextExistingScope mainScope(
      m_settings,
      esT("Main")
    );

    if(mainScope.isOk())
    {
      EsUtilities::windowPosLoad(
        m_settings,
        this,
        EsUtilities::appMainFrameMinSizeGet()
      );

      EsUtilities::windowStateLoad(
        m_settings,
        this
      );
    }
  }

  const EsString::Array& history = m_settings->valueRead(
    esT("History"),
    EsString::nullArray()
  ).asStringCollection();

  EsUtilities::esStringArrayToMru(
    m_mru,
    history
  );

  // Find-replace data
  {
    EsStreamContextExistingScope searchReplaceScope(
      m_settings,
      esT("SearchReplace")
    );

    if(searchReplaceScope.isOk())
    {
      EsUtilities::windowPosLoad(
        m_settings,
        m_posFr,
        wxPoint(0, 0)
      );

      m_dataFr.SetFindString(
        m_settings->valueRead(
          esT("Search"),
          EsString::null()
        ).asString().c_str()
      );

      m_dataFr.SetReplaceString(
        m_settings->valueRead(
          esT("Replace"),
          EsString::null()
        ).asString().c_str()
      );

      m_dataFr.SetFlags(
        m_settings->valueRead(
          esT("Flags"),
          wxFR_DOWN
        ).asULong()
      );
    }
  }

  // Workspace layout load
  const EsString& layout = m_settings->valueRead(
    esT("Workspace"),
    EsString::null()
  ).asString();

  if(!layout.empty())
    m_mgrAui.LoadPerspective(
      layout.c_str()
    );
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::settingsSave()
{
  if(!m_settings)
    return;

  {
    EsStreamContextExistingOrNewScope mainScope(
      m_settings,
      esT("Main")
    );

    if(mainScope.isOk())
    {
      EsUtilities::windowPosSave(
        m_settings,
        this
      );

      EsUtilities::windowStateSave(
        m_settings,
        this
      );
    }
  }

  EsString::Array history;
  EsUtilities::mruToEsStringArray(
    history,
    m_mru
  );

  m_settings->valueWrite(
    esT("History"),
    history
  );

  // Find-replace data
  {
    EsStreamContextExistingOrNewScope searchReplaceScope(
      m_settings,
      esT("SearchReplace")
    );

    if(searchReplaceScope.isOk())
    {
      EsUtilities::windowPosSave(
        m_settings,
        m_posFr
      );

      m_settings->valueWrite(
        esT("Search"),
        EsVariant(
          m_dataFr.GetFindString().t_str(),
          EsVariant::ACCEPT_STRING
        )
      );

      m_settings->valueWrite(
        esT("Replace"),
        EsVariant(
          m_dataFr.GetReplaceString().t_str(),
          EsVariant::ACCEPT_STRING
        )
      );

      m_settings->valueWrite(
        esT("Flags"),
        m_dataFr.GetFlags()
      );
    }
  }

  // Workspace layout save
  const wxString& layout = m_mgrAui.SavePerspective();
  m_settings->valueWrite(
    esT("Workspace"),
    EsVariant(
      layout.t_str(),
      EsVariant::ACCEPT_STRING
    )
  );

  m_settings.reset();
}
//--------------------------------------------------------------------------------

EsVariant EsSconsoleMain::documentParamsDeduceByDocTypeAndKey(const EsString& type, const EsString& key) const
{
  ES_ASSERT(!type.empty());

  const EsPath& fpath = EsPath::createFromFilePath(key);
  const EsString& ext = fpath.fileExtGet();

  const EsString& atype = m_mgrMdi->documentTypeFindByFileExt(
    ext
  );

  if(atype != type) //< Cannot deduce type by file ext - do nothing
    return EsVariant::null();

  if(EsCompiledScriptDocument::classNameGetStatic() == atype)
    return settingsToCompiledScriptDocumentParams(
      (esT("cesse") == ext) ?
        defaultEncKeyGet() :
        EsString::null()
    );

  return EsVariant::null();
}
//--------------------------------------------------------------------------------

EsAssocContainerIntf::Ptr EsSconsoleMain::settingsToCompiledScriptDocumentParams(const EsString& key /*= EsString::null()*/)
{
  EsAssocContainerIntf::Ptr aparams = EsAssocContainer::create();
  ES_ASSERT(aparams);

  aparams->newValueSet(
    esVT("retainDebug"),
    wxGetApp().settingsAccess().m_inclDebugInfo
  );

  aparams->newValueSet(
    esVT("translatablesSave"),
    wxGetApp().settingsAccess().m_translatablesSave
  );

  aparams->newValueSet(
    esVT("key"),
    key
  );

  return aparams;
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::menuInit()
{
  ES_ASSERT(!m_mnu);

  m_mnu = new wxMenuBar;
  ES_ASSERT(m_mnu);

  mnuFileInit();
  mnuEditInit();
  mnuScriptInit();
  mnuOptionsInit();
  mnuWindowInit();
  mnuHelpInit();

  SetMenuBar(m_mnu);
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::nbEditorEvtHandlersInit()
{
  Bind(wxEVT_AUINOTEBOOK_PAGE_CLOSE, &EsSconsoleMain::onViewClose, this, usrID_NB_EDITOR);
  Bind(wxEVT_AUINOTEBOOK_PAGE_CHANGED, &EsSconsoleMain::onActiveViewChanged, this, usrID_NB_EDITOR);
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::mnuFileInit()
{
  m_mnuFile = new wxMenu;
  ES_ASSERT(m_mnuFile);

  m_mnu->Append(
    m_mnuFile,
    _("&File")
  );

  m_mnuFile->Append(
    wxID_NEW,
    _("&New script file\tCTRL-N"),
    _("Create new script file")
  );

  m_mnuFile->Append(
    wxID_OPEN,
    _("&Open\tCTRL-O"),
    _("Open existing source or compiled script files")
  );
  m_mnuFile->AppendSeparator();
  m_mnuFile->Append(
    wxID_CLOSE,
    _("Close"),
    _("Close currently active file")
  );
  m_mnuFile->Append(
    wxID_CLOSE_ALL,
    _("Close all"),
    _("Close all open files")
  );
  m_mnuFile->AppendSeparator();
  m_mnuFile->Append(
    wxID_SAVE,
    _("&Save\tCTRL-S"),
    _("Save changes to the currently active file")
  );
  m_mnuFile->Append(
    wxID_SAVEAS,
    _("Save as..."),
    _("Save current file with different file name")
  );
  m_mnuFile->Append(
    usrID_SAVE_ALL,
    _("Save all\tCTRL-SHIFT-S"),
    _("Save all changes to opened files")
  );
  m_mnuFile->AppendSeparator();

  m_mnuFileMRU = new wxMenu;
  ES_ASSERT(m_mnuFileMRU);

  m_mnuFileMRU->Append(
    usrID_MRU_CLEAR,
    _("Clear history"),
    _("Empty recent files list")
  );

  m_mnuFile->AppendSubMenu(
    m_mnuFileMRU,
    _("Recent files")
  );
  m_mru.UseMenu(m_mnuFileMRU);

  m_mnuFile->AppendSeparator();
  m_mnuFile->Append(
    wxID_EXIT,
    _("Exit\tALT-F4"),
    _("Exit application")
  );

  const wxSize& mnuimgsze = EsUtilities::appSizePropertyGet(ES_APP_OPT_MENU_IMG_WH);

  EsUtilities::menuItemBitmapSet(
    m_mnuFile,
    wxID_NEW,
    mnuimgsze,
    wxART_OTHER,
    wxART_NEW
  );

  EsUtilities::menuItemBitmapSet(
    m_mnuFile,
    wxID_OPEN,
    mnuimgsze,
    wxART_OTHER,
    wxART_FILE_OPEN
  );

  EsUtilities::menuItemBitmapSet(
    m_mnuFile,
    wxID_SAVE,
    mnuimgsze,
    wxART_OTHER,
    wxART_FILE_SAVE
  );

  EsUtilities::menuItemBitmapSet(
    m_mnuFile,
    wxID_SAVEAS,
    mnuimgsze,
    wxART_OTHER,
    wxART_FILE_SAVE_AS
  );

  EsUtilities::menuItemBitmapSet(
    m_mnuFile,
    wxID_CLOSE,
    mnuimgsze,
    wxART_OTHER,
    esART_CLOSE
  );

  EsUtilities::menuItemBitmapSet(
    m_mnuFile,
    wxID_CLOSE_ALL,
    mnuimgsze,
    wxART_OTHER,
    esART_CLOSE_ALL
  );

  EsUtilities::menuItemBitmapSet(
    m_mnuFile,
    usrID_SAVE_ALL,
    mnuimgsze,
    wxART_OTHER,
    esART_SAVE_ALL
  );

  EsUtilities::menuItemBitmapSet(
    m_mnuFile,
    wxID_EXIT,
    mnuimgsze,
    wxART_OTHER,
    wxART_CLOSE
  );
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::mnuFileEvtHandlersInit()
{
  Bind(wxEVT_MENU, &EsSconsoleMain::onScriptNew, this, wxID_NEW);
  Bind(wxEVT_MENU, &EsSconsoleMain::onFileOpen, this, wxID_OPEN);
  Bind(wxEVT_MENU, &EsSconsoleMain::onFileClose, this, wxID_CLOSE);
  Bind(wxEVT_MENU, &EsSconsoleMain::onFileCloseAll, this, wxID_CLOSE_ALL);
  Bind(wxEVT_MENU, &EsSconsoleMain::onMainClose, this, wxID_EXIT);
  Bind(wxEVT_MENU, &EsSconsoleMain::onFileSave, this, wxID_SAVE);
  Bind(wxEVT_MENU, &EsSconsoleMain::onFileSaveAs, this, wxID_SAVEAS);
  Bind(wxEVT_MENU, &EsSconsoleMain::onFileSaveAll, this, usrID_SAVE_ALL);
  Bind(wxEVT_MENU, &EsSconsoleMain::onFileHistoryClear, this, usrID_MRU_CLEAR);
  Bind(wxEVT_MENU, &EsSconsoleMain::onFileHistoryOpen, this, wxID_FILE, wxID_FILE9);

  Bind(wxEVT_UPDATE_UI, &EsSconsoleMain::onFileUiUpdate, this, wxID_CLOSE);
  Bind(wxEVT_UPDATE_UI, &EsSconsoleMain::onFileUiUpdate, this, wxID_CLOSE_ALL);
  Bind(wxEVT_UPDATE_UI, &EsSconsoleMain::onFileUiUpdate, this, wxID_SAVE);
  Bind(wxEVT_UPDATE_UI, &EsSconsoleMain::onFileUiUpdate, this, wxID_SAVEAS);
  Bind(wxEVT_UPDATE_UI, &EsSconsoleMain::onFileUiUpdate, this, usrID_SAVE_ALL, usrID_MRU_CLEAR);
  Bind(wxEVT_UPDATE_UI, &EsSconsoleMain::onFileUiUpdate, this, wxID_EXIT);
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::mnuEditInit()
{
  m_mnuEdit = new wxMenu;
  ES_ASSERT(m_mnuEdit);

  m_mnu->Append(
    m_mnuEdit,
    _("&Edit")
  );

  m_mnuEdit->Append(
    wxID_UNDO,
    _("Undo"),
    _("Undo recent changes")
  );
  m_mnuEdit->Append(
    wxID_REDO,
    _("Redo"),
    _("Redo recent changes")
  );
  m_mnuEdit->AppendSeparator();
  m_mnuEdit->Append(
    wxID_SELECTALL,
    _("Select All\tCTRL-A"),
    _("Select All content in current document")
  );
  m_mnuEdit->Append(
    wxID_COPY,
    _("Copy\tCTRL-C"),
    _("Copy current selection to a clipboard")
  );
  m_mnuEdit->Append(
    wxID_CUT,
    _("Cut\tCTRL-X"),
    _("Cut current selection to clipboard")
  );
  m_mnuEdit->Append(
    wxID_PASTE,
    _("Paste\tCTRL-V"),
    _("Paste clipboard contents to current document")
  );
  m_mnuEdit->AppendSeparator();
  m_mnuEdit->Append(
    wxID_FIND,
    _("Find\tCTRL-F"),
    _("Find subject in documents")
  );
  m_mnuEdit->Append(
    wxID_REPLACE,
    _("Replace\tCTRL-R"),
    _("Find subject in documents and replace it with new content")
  );

  m_mnuEditBm = new wxMenu;
  ES_ASSERT(m_mnuEditBm);

  m_mnuEditBm->Append(
    usrID_EDIT_BOOKMARK_CLEAR_ALL,
    _("Clear all bookmarks\tCTRL-SHIFT-B"),
    _("Clear all bookmarks in current Document")
  );
  m_mnuEditBm->AppendSeparator();
  m_mnuEditBm->Append(
    usrID_EDIT_BOOKMARK,
    _("Bookmark\tCTRL-B"),
    _("Toggle bookmark")
  );
  m_mnuEditBm->AppendSeparator();
  for(int idx = usrID_EDIT_BOOKMARK0; idx <= usrID_EDIT_BOOKMARK9; ++idx)
  {
    int num = idx-usrID_EDIT_BOOKMARK0;
    m_mnuEditBm->AppendCheckItem(
      idx,
      wxString::Format(
        _("Bookmark %d\tALT-%d"),
        num,
        num
      ),
      wxString::Format(
        _("Toggle bookmark %d"),
        num
      )
    );
  }
  m_mnuEditBm->AppendSeparator();
  m_mnuEditBm->Append(
    usrID_EDIT_BOOKMARK_NEXT,
    _("Next Bookmark\tF2"),
    _("Goto next bookmark")
  );
  m_mnuEditBm->Append(
    usrID_EDIT_BOOKMARK_PREV,
    _("Previous Bookmark\tCTRL-SHIFT-F2"),
    _("Goto next bookmark")
  );
  m_mnuEditBm->AppendSeparator();
  for(int idx = usrID_EDIT_GOTO_BOOKMARK0; idx <= usrID_EDIT_GOTO_BOOKMARK9; ++idx)
  {
    int num = idx-usrID_EDIT_GOTO_BOOKMARK0;
    m_mnuEditBm->Append(
      idx,
      wxString::Format(
        _("Goto %d\tCTRL-%d"),
        num, num
      ),
      wxString::Format(
        _("Goto bookmark %d"),
        num
      )
    );
  }

  m_mnuEdit->AppendSeparator();
  m_mnuEdit->AppendSubMenu(
    m_mnuEditBm,
    _("Bookmarks"),
    _("Document bookmarks control and navigation")
  );

  const wxSize& mnuimgsze = EsUtilities::appSizePropertyGet(ES_APP_OPT_MENU_IMG_WH);

  EsUtilities::menuItemBitmapSet(
    m_mnuEdit,
    wxID_SELECTALL,
    mnuimgsze,
    wxART_OTHER,
    esART_SELECT_ALL
  );
  EsUtilities::menuItemBitmapSet(
    m_mnuEdit,
    wxID_UNDO,
    mnuimgsze,
    wxART_OTHER,
    wxART_UNDO
  );
  EsUtilities::menuItemBitmapSet(
    m_mnuEdit,
    wxID_REDO,
    mnuimgsze,
    wxART_OTHER,
    wxART_REDO
  );
  EsUtilities::menuItemBitmapSet(
    m_mnuEdit,
    wxID_COPY,
    mnuimgsze,
    wxART_OTHER,
    wxART_COPY
  );
  EsUtilities::menuItemBitmapSet(
    m_mnuEdit,
    wxID_CUT,
    mnuimgsze,
    wxART_OTHER,
    wxART_CUT
  );
  EsUtilities::menuItemBitmapSet(
    m_mnuEdit,
    wxID_PASTE,
    mnuimgsze,
    wxART_OTHER,
    wxART_PASTE
  );
  EsUtilities::menuItemBitmapSet(
    m_mnuEdit,
    wxID_FIND,
    mnuimgsze,
    wxART_OTHER,
    wxART_FIND
  );
  EsUtilities::menuItemBitmapSet(
    m_mnuEdit,
    wxID_REPLACE,
    mnuimgsze,
    wxART_OTHER,
    wxART_FIND_AND_REPLACE
  );
  EsUtilities::menuItemBitmapSet(
    m_mnuEdit,
    usrID_EDIT_BOOKMARK,
    mnuimgsze,
    wxART_OTHER,
    esART_BOOKMARK
  );
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::mnuEditEvtHandlersInit()
{
  Bind(wxEVT_MENU, &EsSconsoleMain::onEditUndo, this, wxID_UNDO);
  Bind(wxEVT_MENU, &EsSconsoleMain::onEditRedo, this, wxID_REDO);
  Bind(wxEVT_MENU, &EsSconsoleMain::onEditSelectAll, this, wxID_SELECTALL);
  Bind(wxEVT_MENU, &EsSconsoleMain::onEditCopy, this, wxID_COPY);
  Bind(wxEVT_MENU, &EsSconsoleMain::onEditCut, this, wxID_CUT);
  Bind(wxEVT_MENU, &EsSconsoleMain::onEditPaste, this, wxID_PASTE);
  Bind(wxEVT_MENU, &EsSconsoleMain::onEditFind, this, wxID_FIND);
  Bind(wxEVT_MENU, &EsSconsoleMain::onEditReplace, this, wxID_REPLACE);
  Bind(wxEVT_MENU, &EsSconsoleMain::onEditBookmarkClearAll, this, usrID_EDIT_BOOKMARK_CLEAR_ALL);
  Bind(wxEVT_MENU, &EsSconsoleMain::onEditBookmarkToggle, this, usrID_EDIT_BOOKMARK, usrID_EDIT_BOOKMARK9);
  Bind(wxEVT_MENU, &EsSconsoleMain::onEditBookmarkNext, this, usrID_EDIT_BOOKMARK_NEXT);
  Bind(wxEVT_MENU, &EsSconsoleMain::onEditBookmarkPrev, this, usrID_EDIT_BOOKMARK_PREV);
  Bind(wxEVT_MENU, &EsSconsoleMain::onEditBookmarkGoto, this, usrID_EDIT_GOTO_BOOKMARK0, usrID_EDIT_GOTO_BOOKMARK9);

  Bind(wxEVT_UPDATE_UI, &EsSconsoleMain::onEditUiUpdate, this, wxID_UNDO, wxID_REDO);
  Bind(wxEVT_UPDATE_UI, &EsSconsoleMain::onEditUiUpdate, this, wxID_CUT, wxID_REPLACE_ALL);
  Bind(wxEVT_UPDATE_UI, &EsSconsoleMain::onEditUiUpdate, this, usrID_EDIT_BOOKMARK_CLEAR_ALL, usrID_EDIT_GOTO_BOOKMARK9);
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::mnuScriptInit()
{
  m_mnuScript = new wxMenu;
  ES_ASSERT(m_mnuScript);

  m_mnu->Append(
    m_mnuScript,
    _("&Script")
  );

  m_mnuScript->Append(
    usrID_COMPILE_BREAK
  );
  m_mnuScript->AppendSeparator();
  m_mnuScript->Append(
    usrID_RUN,
    _("Run\tALT-F9"),
    _("Run compiled script")
  );
  m_mnuScript->AppendSeparator();
  m_mnuScript->Append(
    usrID_DEBUG
  );
  m_mnuScript->Append(
    usrID_DEBUG_STEP,
    _("Step\tF8"),
    _("Step-by-step script instruction execution in debugger")
  );
  m_mnuScript->AppendSeparator();
  m_mnuScript->Append(
    usrID_RUN_ABORT,
    _("Abort\tCTRL-F2"),
    _("Abort script execution")
  );

  const wxSize& mnuimgsze = EsUtilities::appSizePropertyGet(ES_APP_OPT_MENU_IMG_WH);

  EsUtilities::menuItemBitmapSet(
    m_mnuScript,
    usrID_COMPILE_BREAK,
    mnuimgsze,
    wxART_OTHER,
    esART_COMPILE
  );
  EsUtilities::menuItemBitmapSet(
    m_mnuScript,
    usrID_RUN,
    mnuimgsze,
    wxART_OTHER,
    esART_RUN
  );
  EsUtilities::menuItemBitmapSet(
    m_mnuScript,
    usrID_DEBUG,
    mnuimgsze,
    wxART_OTHER,
    esART_DEBUG_RUN
  );
  EsUtilities::menuItemBitmapSet(
    m_mnuScript,
    usrID_DEBUG_STEP,
    mnuimgsze,
    wxART_OTHER,
    esART_DEBUG_STEP
  );
  EsUtilities::menuItemBitmapSet(
    m_mnuScript,
    usrID_RUN_ABORT,
    mnuimgsze,
    wxART_OTHER,
    esART_ABORT
  );

  // Set-up dynamic text
  scriptCompiationTextUpdate();
  scriptDebugLabelsAndIconsUpdate();
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::mnuScriptEvtHandlersInit()
{
  Bind(wxEVT_MENU, &EsSconsoleMain::onScriptCompileBreak, this, usrID_COMPILE_BREAK);
  Bind(wxEVT_MENU, &EsSconsoleMain::onScriptRun, this, usrID_RUN);
  Bind(wxEVT_MENU, &EsSconsoleMain::onScriptDebug, this, usrID_DEBUG);
  Bind(wxEVT_MENU, &EsSconsoleMain::onScriptDebugStep, this, usrID_DEBUG_STEP);
  Bind(wxEVT_MENU, &EsSconsoleMain::onScriptAbort, this, usrID_RUN_ABORT);

  Bind(wxEVT_UPDATE_UI, &EsSconsoleMain::onScriptUiUpdate, this, usrID_COMPILE_BREAK, usrID_RUN_ABORT);
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::mnuOptionsInit()
{
  m_mnuOptions = new wxMenu;
  ES_ASSERT(m_mnuOptions);

  m_mnu->Append(
    m_mnuOptions,
    _("&Options")
  );

  m_mnuOptions->AppendCheckItem(
    usrID_OPT_INCLUDE_DEBUG,
    _("Include debug"),
    _("Include debug information, when saving compiled script document")
  );
  m_mnuOptions->AppendCheckItem(
    usrID_OPT_GENERATE_TRANSLATABLES,
    _("Generate translatables"),
    _("Generate translatable strings file, when saving compiled script document")
  );
  m_mnuOptions->AppendSeparator();
  m_mnuOptions->Append(
    usrID_OPT_INC_PATHS,
    _("Include paths..."),
    _("Set-up list of script include look-up directories for ##require(...) to search in")
  );
  m_mnuOptions->Append(
    usrID_OPT_LINK_PATHS,
    _("Link paths..."),
    _("Set-up list of binary look-up paths for script ##link(...) to search in")
  );

  m_mnuOptions->AppendSeparator();

  /// Create language selection menu
  wxMenu* mnuLangs = EsUtilities::menuLanguageSelectionCreate(
    EsStringI18n::instanceGet().availableLocalesGet(),
    usrID_LANG_ID_BASE
  );
  ES_ASSERT(mnuLangs);

  m_mnuOptions->AppendSubMenu(
    mnuLangs,
    _("Select language"),
    _("Select user interface language")
  );
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::mnuOptionsEvtHandlersInit()
{
  Bind(wxEVT_MENU, &EsSconsoleMain::onOptIncludeDebug, this, usrID_OPT_INCLUDE_DEBUG);
  Bind(wxEVT_MENU, &EsSconsoleMain::onOptGenTranslatables, this, usrID_OPT_GENERATE_TRANSLATABLES);
  Bind(wxEVT_MENU, &EsSconsoleMain::onOptIncludePaths, this, usrID_OPT_INC_PATHS);
  Bind(wxEVT_MENU, &EsSconsoleMain::onOptLinkPaths, this, usrID_OPT_LINK_PATHS);
  Bind(wxEVT_MENU, &EsSconsoleMain::onOptLangSelected, this, usrID_LANG_ID_BASE, usrID_LANG_ID_BASE+EsStringI18n::instanceGet().availableLocalesGet().size());

  Bind(wxEVT_UPDATE_UI, &EsSconsoleMain::onOptionsUiUpdate, this, usrID_OPT_INCLUDE_DEBUG, usrID_OPT_LINK_PATHS);
  Bind(wxEVT_UPDATE_UI, &EsSconsoleMain::onOptionsUiUpdate, this, usrID_LANG_ID_BASE, usrID_LANG_ID_BASE+EsStringI18n::instanceGet().availableLocalesGet().size());
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::mnuWindowInit()
{
  m_mnuWindow = new wxMenu;
  ES_ASSERT(m_mnuWindow);

  m_mnu->Append(
    m_mnuWindow,
    _("&Window")
  );

  m_mnuWindow->AppendCheckItem(
    usrID_WND_LIST,
    _("Document list"),
    _("Toggle document list pane visibility")
  );
  m_mnuWindow->AppendSeparator();
  m_mnuWindow->AppendCheckItem(
    wxID_CLOSE_ALL,
    _("Close all"),
    _("Close all open files")
  );
  m_mnuWindow->AppendSeparator();
  m_mnuWindow->AppendCheckItem(
    usrID_WND_APPLOG,
    _("Application Log"),
    _("Toggle application log pane visibility")
  );
  m_mnuWindow->AppendCheckItem(
    usrID_WND_COMPILELOG,
    _("Compiler Log"),
    _("Toggle script compiler log pane visibility")
  );

  const wxSize& mnuimgsze = EsUtilities::appSizePropertyGet(ES_APP_OPT_MENU_IMG_WH);

  EsUtilities::menuItemBitmapSet(
    m_mnuFile,
    wxID_CLOSE_ALL,
    mnuimgsze,
    wxART_OTHER,
    esART_CLOSE_ALL
  );
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::mnuWindowEvtHandlersInit()
{
  Bind(wxEVT_MENU, &EsSconsoleMain::onWndDoclistToggle, this, usrID_WND_LIST);
  Bind(wxEVT_MENU, &EsSconsoleMain::onWndAppLogToggle, this, usrID_WND_APPLOG);
  Bind(wxEVT_MENU, &EsSconsoleMain::onWndCompLogToggle, this, usrID_WND_COMPILELOG);

  Bind(wxEVT_UPDATE_UI, &EsSconsoleMain::onWindowUiUpdate, this, usrID_WND_LIST, usrID_WND_COMPILELOG);
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::mnuHelpInit()
{
  m_mnuHelp = new wxMenu;
  ES_ASSERT(m_mnuHelp);
  m_mnu->Append(
    m_mnuHelp,
    _("&Help")
  );

  m_mnuHelp->Append(
    wxID_ABOUT,
    _("About..."),
    wxString::Format(
      _("Show information about an '%s' application"),
      PRODUCT_NAME
    )
  );
  m_mnuHelp->Append(
    wxID_HELP,
    _("Help..."),
    wxString::Format(
      _("Show help on '%s' application"),
      PRODUCT_NAME
    )
  );
  m_mnuHelp->AppendSeparator();
  m_mnuHelp->Append(
    usrID_HLP_ESCORE,
    _("ES core"),
    _("Show ES core API documentation, including reflection")
  );
  m_mnuHelp->Append(
    usrID_HLP_ESCOMM,
    _("ES comm"),
    _("Show ES comm API documentation, including reflection")
  );
  m_mnuHelp->Append(
    usrID_HLP_ESMATH,
    _("ES math"),
    _("Show ES math API documentation, including reflection")
  );
  m_mnuHelp->Append(
    usrID_HLP_ESSCRIPT,
    _("ES script"),
    _("Show ES script API documentation, including reflection")
  );
  m_mnuHelp->Append(
    usrID_HLP_ESSCRIPTING,
    _("ES scripting cookbook"),
    _("Show documentation on ES script language basics, with small examples")
  );
#if defined(__WXMSW__)
  m_mnuHelp->AppendSeparator();
  m_mnuHelp->AppendCheckItem(
    usrID_HLP_AUTO_UPDATE,
    _("Auto update"),
    _("Toggle automatic regular checking for an application updates")
  );
  m_mnuHelp->Append(
    usrID_HLP_UPDATE,
    _("Check for update"),
    _("Check for online application updatesmanually")
  );
#endif

  const wxSize& mnuimgsze = EsUtilities::appSizePropertyGet(ES_APP_OPT_MENU_IMG_WH);

  EsUtilities::menuItemBitmapSet(
    m_mnuHelp,
    wxID_ABOUT,
    mnuimgsze,
    wxART_OTHER,
    esART_INFO
  );

  EsUtilities::menuItemBitmapSet(
    m_mnuHelp,
    wxID_HELP,
    mnuimgsze,
    wxART_OTHER,
    wxART_HELP
  );
  EsUtilities::menuItemBitmapSet(
    m_mnuHelp,
    usrID_HLP_ESCORE,
    mnuimgsze,
    wxART_OTHER,
    esART_HELP_MODULE
  );
  EsUtilities::menuItemBitmapSet(
    m_mnuHelp,
    usrID_HLP_ESCOMM,
    mnuimgsze,
    wxART_OTHER,
    esART_HELP_MODULE
  );
  EsUtilities::menuItemBitmapSet(
    m_mnuHelp,
    usrID_HLP_ESMATH,
    mnuimgsze,
    wxART_OTHER,
    esART_HELP_MODULE
  );
  EsUtilities::menuItemBitmapSet(
    m_mnuHelp,
    usrID_HLP_ESSCRIPT,
    mnuimgsze,
    wxART_OTHER,
    esART_HELP_MODULE
  );
  EsUtilities::menuItemBitmapSet(
    m_mnuHelp,
    usrID_HLP_ESSCRIPTING,
    mnuimgsze,
    wxART_OTHER,
    esART_HELP_MODULE
  );
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::mnuHelpEvtHandlersInit()
{
  Bind(wxEVT_MENU, &EsSconsoleMain::onHelp, this, wxID_HELP);
  Bind(wxEVT_MENU, &EsSconsoleMain::onHelpAbout, this, wxID_ABOUT);
  Bind(wxEVT_MENU, &EsSconsoleMain::onHelpDocument, this, usrID_HLP_ESCORE, usrID_HLP_ESSCRIPTING);

#if defined(__WXMSW__)
  Bind(wxEVT_MENU, &EsSconsoleMain::onAutoUpdate, this, usrID_HLP_AUTO_UPDATE);
  Bind(wxEVT_MENU, &EsSconsoleMain::onOnlineUpdate, this, usrID_HLP_UPDATE);
#endif

  Bind(wxEVT_UPDATE_UI, &EsSconsoleMain::onHelpUiUpdate, this, wxID_HELP);
  Bind(wxEVT_UPDATE_UI, &EsSconsoleMain::onHelpUiUpdate, this, wxID_ABOUT);
  Bind(wxEVT_UPDATE_UI, &EsSconsoleMain::onHelpUiUpdate, this, usrID_HLP_ESCORE, usrID_HLP_UPDATE);
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::toolbarInit()
{
  ES_ASSERT(!m_tb);

  m_tb = CreateToolBar(
    wxTB_FLAT|wxTB_HORIZONTAL|wxTB_HORZ_TEXT|wxTB_TOP,
    wxID_ANY
  );
  ES_ASSERT(m_tb);

  m_tb->SetToolBitmapSize(
    EsUtilities::appSizePropertyGet(ES_APP_OPT_TOOLBAR_IMG_WH)
  );

  EsUtilities::toolbarToolAddFromMenuItem(
    m_tb,
    m_mnuFile,
    wxID_NEW,
    wxART_TOOLBAR,
    wxART_NEW
  );
  EsUtilities::toolbarToolAddFromMenuItem(
    m_tb,
    m_mnuFile,
    wxID_OPEN,
    wxART_TOOLBAR,
    wxART_FILE_OPEN
  );
  EsUtilities::toolbarToolAddFromMenuItem(
    m_tb,
    m_mnuFile,
    wxID_SAVE,
    wxART_TOOLBAR,
    wxART_FILE_SAVE
  );
  EsUtilities::toolbarToolAddFromMenuItem(
    m_tb,
    m_mnuFile,
    usrID_SAVE_ALL,
    wxART_TOOLBAR,
    esART_SAVE_ALL
  );
  m_tb->AddSeparator();

  EsUtilities::toolbarToolAddFromMenuItem(
    m_tb,
    m_mnuEdit,
    wxID_UNDO,
    wxART_TOOLBAR,
    wxART_UNDO
  );
  EsUtilities::toolbarToolAddFromMenuItem(
    m_tb,
    m_mnuEdit,
    wxID_REDO,
    wxART_TOOLBAR,
    wxART_REDO
  );
  m_tb->AddSeparator();
  EsUtilities::toolbarToolAddFromMenuItem(
    m_tb,
    m_mnuScript,
    usrID_COMPILE_BREAK,
    wxART_TOOLBAR,
    esART_COMPILE
  );
  m_tb->AddSeparator();

  EsUtilities::toolbarToolAddFromMenuItem(
    m_tb,
    m_mnuScript,
    usrID_RUN,
    wxART_TOOLBAR,
    esART_RUN
  );
  EsUtilities::toolbarToolAddFromMenuItem(
    m_tb,
    m_mnuScript,
    usrID_DEBUG,
    wxART_TOOLBAR,
    esART_DEBUG_RUN
  );
  EsUtilities::toolbarToolAddFromMenuItem(
    m_tb,
    m_mnuScript,
    usrID_DEBUG_STEP,
    wxART_TOOLBAR,
    esART_DEBUG_STEP
  );
  EsUtilities::toolbarToolAddFromMenuItem(
    m_tb,
    m_mnuScript,
    usrID_RUN_ABORT,
    wxART_TOOLBAR,
    esART_ABORT
  );
  m_tb->AddStretchableSpace();

  m_tb->Realize();
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::statusbarInit()
{
  ES_ASSERT(!m_sb);

  m_sb = CreateStatusBar(
    sbFldCnt//< Tips filed, line field, column field, CAPS field, NUMLOCK field, INS-OVR field
  );
  ES_ASSERT(m_sb);

  m_sb->SetStatusText( //< Set default text for the 0th field
    _("Ready")
  );

  std::vector<int> widths;
  widths.push_back(-1);
  widths.push_back(100);
  widths.push_back(100);
  widths.push_back(60);
  widths.push_back(60);
  widths.push_back(60);

  ES_ASSERT( widths.size() == m_sb->GetFieldsCount() );

  m_sb->SetStatusWidths(
    widths.size(),
    widths.data()
  );

  Bind(wxEVT_IDLE, &EsSconsoleMain::onIdle, this);
}
//--------------------------------------------------------------------------------

/*void EsSconsoleMain::treeInit()
{
  ES_ASSERT(!m_tv);

  m_tv = new wxTreeCtrl(
    this
  );
  ES_ASSERT(m_tv);
}*/
//--------------------------------------------------------------------------------

void EsSconsoleMain::nbEditorInit()
{
  ES_ASSERT(!m_nbEditor);

  m_nbEditor = new wxAuiNotebook(
    this,
    usrID_NB_EDITOR,
    wxDefaultPosition,
    wxDefaultSize,
    wxAUI_NB_TOP |
    wxAUI_NB_TAB_SPLIT |
    wxAUI_NB_TAB_MOVE |
    wxAUI_NB_SCROLL_BUTTONS |
    wxAUI_NB_WINDOWLIST_BUTTON |
    wxAUI_NB_CLOSE_ON_ACTIVE_TAB |
    wxBORDER_NONE
  );
  ES_ASSERT(m_nbEditor);
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::layoutInit()
{
  //  treeInit();
  menuInit();
  toolbarInit();
  statusbarInit();
  nbEditorInit();
  applogPaneInit();
  compilerOutputPaneInit();
  documentListPaneInit();

  // Initialize panes
  m_mgrAui.AddPane(
    m_nbEditor,
    wxAuiPaneInfo().
    Name(wxT("pane_tabs")).
    CenterPane().
    MinSize(
      500,
      0
    )
  );

  m_mgrAui.AddPane(
    m_logComp,
    wxAuiPaneInfo().
    Name(wxT("pane_complog")).
    Layer(1).
    Caption(_("Compiler output log")).
    MinSize(
      wxSystemOptions::GetOptionInt(ES_APP_OPT_PANE_MIN_WIDTH),
      wxSystemOptions::GetOptionInt(ES_APP_OPT_PANE_MIN_HEIGHT)
    ).
    Bottom().
    TopDockable(false).
    BottomDockable(true).
    LeftDockable(false).
    RightDockable(false).
    CloseButton().
    PinButton().
    GripperTop().
    Floatable()
  );

  m_mgrAui.AddPane(
    m_log,
    wxAuiPaneInfo().
    Name(wxT("pane_applog")).
    Layer(1).
    Caption(_("Application Log")).
    MinSize(
      wxSystemOptions::GetOptionInt(ES_APP_OPT_PANE_MIN_WIDTH),
      wxSystemOptions::GetOptionInt(ES_APP_OPT_PANE_MIN_HEIGHT)
    ).
    Bottom().
    TopDockable(false).
    BottomDockable(true).
    LeftDockable(false).
    RightDockable(false).
    CloseButton().
    PinButton().
    GripperTop().
    Floatable()
  );

  m_mgrAui.AddPane(
    m_docList,
    wxAuiPaneInfo().
    Name(wxT("pane_doclist")).
    Layer(1).
    Caption(_("Open documents list")).
    MinSize(
      wxSystemOptions::GetOptionInt(ES_APP_OPT_PANE_MIN_WIDTH),
      wxSystemOptions::GetOptionInt(ES_APP_OPT_PANE_MIN_HEIGHT)
    ).
    Right().
    TopDockable(false).
    LeftDockable(true).
    RightDockable(true).
    BottomDockable(false).
    CloseButton().
    PinButton().
    GripperTop().
    Floatable().
    Hide()
  );

  m_mgrAui.Update(); //< Commit structureal changes
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::applogPaneInit()
{
  ES_ASSERT(!m_log);

  // Applog init
  m_log = new wxPanel(this);
  ES_ASSERT(m_log);

  EsAppLog* logList = new EsAppLog(m_log);
  ES_ASSERT(logList);

  wxToolBar* ptb = logList->toolBarGet(m_log);

  wxBoxSizer* contents = new wxBoxSizer(wxVERTICAL);
  ES_ASSERT(contents);

  m_log->SetSizer(contents);

  contents->Add(
    ptb,
    wxSizerFlags().Expand()
  );
  contents->Add(
    logList,
    wxSizerFlags(1).Expand()
  );
  contents->Layout();
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::compilerOutputPaneInit()
{
  ES_ASSERT(!m_logComp);

  // Compiler log init
  m_logComp = new wxPanel(this);
  ES_ASSERT(m_logComp);

  EsSconsoleCompilerOutput* plogComp = new EsSconsoleCompilerOutput(m_logComp);
  ES_ASSERT(plogComp);

  wxToolBar* ptb = plogComp->toolBarGet(m_logComp);

  wxBoxSizer* contents = new wxBoxSizer(wxVERTICAL);
  ES_ASSERT(contents);

  m_logComp->SetSizer(contents);

  contents->Add(
    ptb,
    wxSizerFlags().Expand()
  );
  contents->Add(
    plogComp,
    wxSizerFlags(1).Expand()
  );
  contents->Layout();
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::documentListPaneInit()
{
  ES_ASSERT(!m_docList);

  // Document listing panel initialization
  m_docList = new wxPanel(this);
  ES_ASSERT(m_docList);

  EsOpenedDocumentList* docList = new EsOpenedDocumentList(m_docList);

  wxToolBar* ptb = docList->toolBarGet(m_docList);

  wxBoxSizer* contents = new wxBoxSizer(wxVERTICAL);
  ES_ASSERT(contents);

  m_docList->SetSizer(contents);

  contents->Add(
    ptb,
    wxSizerFlags().Expand()
  );
  contents->Add(
    docList,
    wxSizerFlags(1).Expand()
  );
  contents->Layout();
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::dlgFindReplace(bool replace, wxString strSearch /*= wxEmptyString*/)
{
  bool needCreate = false;

  if(strSearch.IsEmpty())
    strSearch = m_dataFr.GetFindString();

  if(
    m_dlgFr &&
    (
      replace != m_dlgFr->HasFlag(wxFR_REPLACEDIALOG) ||
      m_dlgFr->GetData()->GetFindString() != strSearch
    )
  )
  {
    m_posFr = m_dlgFr->GetPosition();

    m_dlgFr->Destroy();
    m_dlgFr = nullptr;

    needCreate = true;
  }
  else if(!m_dlgFr)
    needCreate = true;

  if(needCreate)
  {
    ES_ASSERT(!m_dlgFr);

    m_dataFr.SetFindString(strSearch);

    if(replace)
      m_dlgFr = new wxFindReplaceDialog(
        this,
        &m_dataFr,
        _("Find and Replace text"),
        wxFR_REPLACEDIALOG
      );
    else
      m_dlgFr = new wxFindReplaceDialog(
        this,
        &m_dataFr,
        _("Find text")
      );
  }

  ES_ASSERT(m_dlgFr);
  m_dlgFr->Show();
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::mdiInit()
{
  m_mgrMdi = EsDocumentManager::NEW();
  ES_ASSERT(m_mgrMdi);

  EsDocumentManager::registerIn(
    m_mgrMdi,
    esT("EsScriptDocument"),
    esT("ess"),
    esT("script"),
    esT("ES script files (*.ess)|*.ess")
  );

  EsDocumentManager::registerIn(
    m_mgrMdi,
    esT("EsCompiledScriptDocument"),
    esT("cess"),
    esT("compiled script"),
    esT("ES compiled script files (*.cess)|*.cess|ES compiled encrypted files (*.cesse)|*.cesse"),
    true //< Singleton document type
  );

  EsDocumentManager::registerIn(
    m_mgrMdi,
    esT("EsTextDocument"),
    esT("txt"),
    esT("text/source"),
    esT("Text files (*.txt)|*.txt|C\\C++ files (*.c;*.cpp;*.h;*.hpp;*.cxx;*.cc)|*.c;*.cpp;*.h;*.hpp;*.cxx;*.cc")
  );
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::evtHandlersInit()
{
  nbEditorEvtHandlersInit();
  mnuFileEvtHandlersInit();
  mnuEditEvtHandlersInit();
  mnuScriptEvtHandlersInit();
  mnuWindowEvtHandlersInit();
  mnuOptionsEvtHandlersInit();
  mnuHelpEvtHandlersInit();

  // Search-reaplce
  Bind(wxEVT_FIND, &EsSconsoleMain::onDlgFindReplaceEvent, this);
  Bind(wxEVT_FIND_NEXT, &EsSconsoleMain::onDlgFindReplaceEvent, this);
  Bind(wxEVT_FIND_REPLACE, &EsSconsoleMain::onDlgFindReplaceEvent, this);
  Bind(wxEVT_FIND_REPLACE_ALL, &EsSconsoleMain::onDlgFindReplaceEvent, this);
  Bind(wxEVT_FIND_CLOSE, &EsSconsoleMain::onDlgFindReplaceEvent, this);

  // App main window close
  Bind(wxEVT_CLOSE_WINDOW, &EsSconsoleMain::onClose, this);

  // Attach evt pump as a last step
  Bind(wxEVT_TIMER, &EsSconsoleMain::onEsEvtPump, this, usrID_TMR_EVT_PUMP);
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::evtHandlersUninit()
{
  // Stop and detach evt pump timer as a last step
  if(m_tmrEvtPump.IsRunning())
    m_tmrEvtPump.Stop();

  m_tmrEvtPump.Unbind(
    wxEVT_TIMER,
    &EsSconsoleMain::onEsEvtPump,
    this,
    usrID_TMR_EVT_PUMP
  );
}
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

void EsSconsoleMain::scriptCompiationTextUpdate()
{
  wxMenuItem* item = m_mnuScript->FindItem(usrID_COMPILE_BREAK);
  ES_ASSERT(item);

  if( !m_compiling )
  {
    item->SetItemLabel(_("Compile\tCTRL-F9"));
    item->SetHelp(_("Compile currently active script file"));
  }
  else
  {
    item->SetItemLabel(_("Break\tCTRL-F9"));
    item->SetHelp(_("Break currently running compilation"));
  }

  // Update related TB item as well. This part is optional
  if( !m_tb )
    return;

  wxToolBarToolBase* tbitem = m_tb->FindById(usrID_COMPILE_BREAK);
  if( !tbitem )
    return;

  tbitem->SetLabel(
    item->GetItemLabelText()
  );
  tbitem->SetShortHelp(
    item->GetHelp()
  );
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::scriptDebugLabelsAndIconsUpdate()
{
  wxMenuItem* item = m_mnuScript->FindItem(usrID_DEBUG);
  ES_ASSERT(item);

  wxString lbl;
  wxString hlp;
  wxBitmap bm;

  if( binaryScriptIsContinuouslyDebugging() )
  {
    lbl = _("Pause\tF9");
    hlp = _("Pause debugger at current execution point");
    bm = wxArtProvider::GetBitmap(esART_DEBUG_PAUSE);
  }
  else if( binaryScriptIsDebugging() && !binaryScriptIsContinuouslyDebugging() )
  {
    lbl =_("Continue\tF9");
    hlp = _("Continue script execution in debugger");
    bm = wxArtProvider::GetBitmap(esART_DEBUG_RUN);
  }
  else
  {
    lbl = _("Debug\tF9");
    hlp = _("Run compiled script in debugger");
    bm = wxArtProvider::GetBitmap(esART_DEBUG_RUN);
  }

  item->SetItemLabel(lbl);
  item->SetHelp(hlp);
  item->SetBitmap(bm);

  // Update related TB item as well. This part is optional
  if( !m_tb )
    return;

  wxToolBarToolBase* tbitem = m_tb->FindById(usrID_DEBUG);
  if( !tbitem )
    return;

  wxWindowUpdateLocker lock(m_tb);

  lbl = item->GetItemLabelText();
  tbitem->SetLabel(
    lbl
  );
  tbitem->SetShortHelp(
    hlp
  );
  tbitem->SetNormalBitmap(
    bm
  );

  m_tb->Realize();
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::sbTextEditInfoUpdate()
{
  if(!m_sb)
    return;

  if(wxGetKeyState(WXK_NUMLOCK))
    SetStatusText(
       esT("NUM"),
      sbFldNumlock
    );
  else
    SetStatusText(
      wxEmptyString,
      sbFldNumlock
    );

  if(wxGetKeyState(WXK_CAPITAL))
    SetStatusText(
      esT("CAPS"),
      sbFldCaps
    );
  else
    SetStatusText(
      wxEmptyString,
      sbFldCaps
    );

  EsTextEditorViewBase* view = currentTextEditorGet();
  if( !view )
  {
    SetStatusText(
      _("Ln --"),
      sbFldLine
    );
    SetStatusText(
      _("Col --"),
      sbFldColumn
    );
    SetStatusText(
      wxEmptyString,
      sbFldInsOvr
    );
  }
  else
  {
    SetStatusText(
      wxString::Format(
        _("Ln %d"),
        view->GetCurrentLine()+1
      ),
      sbFldLine
    );
    SetStatusText(
      wxString::Format(
        _("Col %d"),
        view->GetColumn(
          view->GetCurrentPos()
        )+1
      ),
      sbFldColumn
    );
    if(view->GetOvertype())
      SetStatusText(
        esT("OVR"),
        sbFldInsOvr
      );
    else
      SetStatusText(
        esT("INS"),
        sbFldInsOvr
      );
  }
}
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
// WX events
//

void EsSconsoleMain::onFileUiUpdate(wxUpdateUIEvent& evt)
{
  if(m_changingDocptrs)
    return;

  int id = evt.GetId();

  switch(id)
  {
  case wxID_CLOSE:
  case wxID_SAVEAS:
    evt.Enable(
      nullptr != currentDocPtrGet()
    );
    break;
  case wxID_CLOSE_ALL:
    evt.Enable(
      haveAnyOpenDocuments()
    );
    break;
  case wxID_SAVE:
    evt.Enable(
      canSaveCurrentDocument()
    );
    break;
  case usrID_SAVE_ALL:
    evt.Enable(
      haveAnyModifiedDocuments()
    );
    break;
  case usrID_MRU_CLEAR:
    evt.Enable(
      0 < m_mru.GetCount()
    );
    break;
  case wxID_EXIT:
    break;
  }
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onEditUiUpdate(wxUpdateUIEvent& evt)
{
  if(m_changingDocptrs)
    return;

  int id = evt.GetId();
  EsTextEditorViewBase* view = currentTextEditorGet();

  switch(id)
  {
    case wxID_UNDO:
    {
      evt.Enable(
        view && view->CanUndo()
      );
    }
    break;
    case wxID_REDO:
    {
      evt.Enable(
        view && view->CanRedo()
      );
    }
    break;
    case wxID_COPY:
    {
      evt.Enable(
        view && view->CanCopy()
      );
    }
    break;
    case wxID_CUT:
    {
      evt.Enable(
        view && view->CanCut()
      );
    }
    break;
    case wxID_PASTE:
    {
      evt.Enable(
        view && view->CanPaste()
      );
    }
    break;
    case wxID_SELECTALL:
    case wxID_FIND:
    case wxID_REPLACE:
    case wxID_REPLACE_ALL:
      evt.Enable(nullptr != view);
      break;
    case usrID_EDIT_BOOKMARK_CLEAR_ALL:
      evt.Enable(
        nullptr != view &&
        view->hasBookmarks()
      );
      break;
    case usrID_EDIT_BOOKMARK0:
    case usrID_EDIT_BOOKMARK1:
    case usrID_EDIT_BOOKMARK2:
    case usrID_EDIT_BOOKMARK3:
    case usrID_EDIT_BOOKMARK4:
    case usrID_EDIT_BOOKMARK5:
    case usrID_EDIT_BOOKMARK6:
    case usrID_EDIT_BOOKMARK7:
    case usrID_EDIT_BOOKMARK8:
    case usrID_EDIT_BOOKMARK9:
      evt.Check(
        nullptr != view &&
        view->hasBookmark(id-usrID_EDIT_BOOKMARK0)
      );
    case usrID_EDIT_BOOKMARK:
      evt.Enable(nullptr != view);
      break;
    case usrID_EDIT_BOOKMARK_NEXT:
    case usrID_EDIT_BOOKMARK_PREV:
      evt.Enable(
        view &&
        view->hasBookmarks()
      );
      break;
    case usrID_EDIT_GOTO_BOOKMARK0:
    case usrID_EDIT_GOTO_BOOKMARK1:
    case usrID_EDIT_GOTO_BOOKMARK2:
    case usrID_EDIT_GOTO_BOOKMARK3:
    case usrID_EDIT_GOTO_BOOKMARK4:
    case usrID_EDIT_GOTO_BOOKMARK5:
    case usrID_EDIT_GOTO_BOOKMARK6:
    case usrID_EDIT_GOTO_BOOKMARK7:
    case usrID_EDIT_GOTO_BOOKMARK8:
    case usrID_EDIT_GOTO_BOOKMARK9:
      evt.Enable(
        view &&
        view->hasBookmark(id - usrID_EDIT_GOTO_BOOKMARK0)
      );
      break;
  }
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onScriptUiUpdate(wxUpdateUIEvent& evt)
{
  if(m_changingDocptrs)
    return;

  int id = evt.GetId();

  switch(id)
  {
  case usrID_COMPILE_BREAK:
    if(m_compiling)
      evt.Enable(true);
    else
      evt.Enable(
        currentDocumentCanCompile()
      );
    break;
  case usrID_RUN:
    evt.Enable(
      binaryScriptCanRun()
    );
    break;
  case usrID_DEBUG:
    evt.Enable(
      binaryScriptIsDebuggable() &&
      (
        !binaryScriptIsRunning() || 
        binaryScriptIsDebugging()
      )
    );
    break;
  case usrID_DEBUG_STEP:
    evt.Enable(
      binaryScriptCanStep()
    );
    break;
  case usrID_RUN_ABORT:
    evt.Enable(
      binaryScriptCanAbort()
    );
    break;
  }
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onOptionsUiUpdate(wxUpdateUIEvent& evt)
{
  int id = evt.GetId();

  if(id >= usrID_LANG_ID_BASE)
  {
    EsStringI18n& i18n = EsStringI18n::instanceGet();

    ES_ASSERT(id < static_cast<int>(usrID_LANG_ID_BASE+i18n.availableLocalesGet().size()));

    int locIdx = id-usrID_LANG_ID_BASE;
    const EsString& loc = i18n.availableLocalesGet()[locIdx];
    evt.Check(
      i18n.currentLocaleGet() == loc
    );

    return;
  }

  switch(id)
  {
  case usrID_OPT_GENERATE_TRANSLATABLES:
    evt.Enable(
      !m_compiling && !binaryScriptIsRunning()
    );
    evt.Check(
      wxGetApp().settingsAccess().m_translatablesSave
    );
    break;
  case usrID_OPT_INCLUDE_DEBUG:
    evt.Enable(
      !m_compiling && !binaryScriptIsRunning()
    );
    evt.Check(
      wxGetApp().settingsAccess().m_inclDebugInfo
    );
    break;
  case usrID_OPT_INC_PATHS:
    evt.Enable(
      !m_compiling && !binaryScriptIsRunning()
    );
    break;
  case usrID_OPT_LINK_PATHS:
    evt.Enable(
      !m_compiling && !binaryScriptIsRunning()
    );
    break;
  }
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onWindowUiUpdate(wxUpdateUIEvent& evt)
{
  int id = evt.GetId();

  switch(id)
  {
  case usrID_WND_LIST:
    evt.Check(
      m_mgrAui.GetPane(esT("pane_doclist")).IsShown()
    );
    break;
  case usrID_WND_APPLOG:
    evt.Check(
      m_mgrAui.GetPane(esT("pane_applog")).IsShown()
    );
    break;
  case usrID_WND_COMPILELOG:
    evt.Check(
      m_mgrAui.GetPane(esT("pane_complog")).IsShown()
    );
    break;
  }
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onHelpUiUpdate(wxUpdateUIEvent& evt)
{
#if defined(__WXMSW__)
  int id = evt.GetId();

  switch(id)
  {
  case usrID_HLP_AUTO_UPDATE:
    evt.Check(
      m_au.autoUpdateGet()
    );
    // NB! fall through
  case usrID_HLP_UPDATE:
    evt.Enable(
      m_au.canCheckUpdate()
    );
    break;
  }
#endif
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onIdle(wxIdleEvent& evt)
{
  sbTextEditInfoUpdate();
  evt.Skip();
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onClose(wxCloseEvent& evt)
{
  ES_DEBUG_TRACE(esT("EsSconsoleMain::onClose"));

  bool forced = !evt.CanVeto(); //< Forced closing - do not save anything

  // Check if we may Veto
  bool canClose = forced || documentsCloseAll();

  if(!canClose)
    evt.Veto();
  else
  {
    wxDELETE(m_dlgFr);

    settingsSave();

    Destroy();
  }
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onEsEvtPump(wxTimerEvent& WXUNUSED(evt))
{
  ulong chunk = 1000 / evtPumpTmo;
  while(EsEventDispatcher::process() && chunk--);

  m_tmrEvtPump.StartOnce(evtPumpTmo);
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onMainClose(wxCommandEvent& WXUNUSED(evt))
{
  ES_DEBUG_TRACE(esT("EsSconsoleMain::onMainClose"));

  Close();
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onScriptNew(wxCommandEvent& WXUNUSED(evt))
{
  ES_DEBUG_TRACE(esT("EsSconsoleMain::onScriptNew"));

  m_mgrMdi->documentOpen(
    EsScriptDocument::classNameGetStatic()
  );
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onFileOpen(wxCommandEvent& WXUNUSED(evt))
{
  ES_DEBUG_TRACE(esT("EsSconsoleMain::onFileOpen"));

  const EsString::Array& regTypes = m_mgrMdi->registeredDocumentTypesGet();

  // Concatenate filter string
  wxString filterStr;
  for(auto const& regType : regTypes)
  {
    const EsVariant& regInfo = m_mgrMdi->documentRegistrationPayloadGet(regType);

    if(!filterStr.empty())
      filterStr += esT("|");

    filterStr += regInfo[esVT("filterStr")][1].asString().c_str();
  }

  wxFileDialog dlgOpen(
    this,
    _("Open file"),
    wxEmptyString,
    wxEmptyString,
    filterStr,
    wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxFD_MULTIPLE | wxFD_CHANGE_DIR | wxFD_NO_FOLLOW,
    wxDefaultPosition,
    wxDefaultSize
  );

  if(wxID_OK != dlgOpen.ShowModal())
    return;

  wxArrayString files;
  dlgOpen.GetFilenames(files);

  const wxString& dir = dlgOpen.GetDirectory();

  std::set<EsString> banNextTime;
  for(auto const& file : files)
  {
    wxFileName fname(
      dir,
      file
    );
    fname.Normalize();

    documentFileOpenOrActivate(
      fname.GetFullPath().t_str(),
      EsVariant::null(),
      banNextTime
    );
  }
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onFileClose(wxCommandEvent& WXUNUSED(evt))
{
  ES_DEBUG_TRACE(esT("EsSconsoleMain::onFileClose"));

  wxWindow* view = m_nbEditor->GetCurrentPage();
  if(!view)
    return;

  EsEventDispatcher::eventPost(
    ES_EVTC_APPLICATION,
    as_<ulong>(EsSconsoleEvt::DocViewCloseRequest),
    EsVariant(
      view,
      EsVariant::ACCEPT_POINTER
    )
  );
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onFileCloseAll(wxCommandEvent& WXUNUSED(evt))
{
  ES_DEBUG_TRACE(esT("EsSconsoleMain::onFileCloseAll"));

  documentsCloseAll();
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onFileSave(wxCommandEvent& WXUNUSED(evt))
{
  ES_DEBUG_TRACE(esT("EsSconsoleMain::onFileSave"));

  EsDocumentIntf::Ptr doc = currentDocumentGet();
  ES_ASSERT(doc);

  documentSave(doc, false);
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onFileSaveAs(wxCommandEvent& WXUNUSED(evt))
{
  ES_DEBUG_TRACE(esT("EsSconsoleMain::onFileSaveAs"));

  EsDocumentIntf::Ptr doc = currentDocumentGet();
  ES_ASSERT(doc);

  documentSaveAs(doc);
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onFileHistoryOpen(wxCommandEvent& evt)
{
  int mruIdx = evt.GetId()-wxID_FILE;

  ES_ASSERT(mruIdx > -1);
  ES_ASSERT(mruIdx < static_cast<int>(m_mru.GetCount()));

  const wxString& fnameStr = m_mru.GetHistoryFile(mruIdx);
  wxFileName fname(fnameStr);
  fname.Normalize();

  std::set<EsString> banNextTime;

  documentFileOpenOrActivate(
    fname.GetFullPath().t_str(),
    EsVariant::null(),
    banNextTime
  );
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onFileHistoryClear(wxCommandEvent& ES_UNUSED(evt))
{
  ES_DEBUG_TRACE(esT("EsSconsoleMain::onFileHistoryClear"));

  while(m_mru.GetCount())
    m_mru.RemoveFileFromHistory(0);
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onEditUndo(wxCommandEvent& ES_UNUSED(evt))
{
  EsTextEditorViewBase* view = currentTextEditorGet();
  ES_ASSERT(view);

  view->Undo();
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onEditRedo(wxCommandEvent& ES_UNUSED(evt))
{
  EsTextEditorViewBase* view = currentTextEditorGet();
  ES_ASSERT(view);

  view->Redo();
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onEditSelectAll(wxCommandEvent& ES_UNUSED(evt))
{
  EsTextEditorViewBase* view = currentTextEditorGet();
  ES_ASSERT(view);

  view->SelectAll();
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onEditCopy(wxCommandEvent& ES_UNUSED(evt))
{
  EsTextEditorViewBase* view = currentTextEditorGet();
  ES_ASSERT(view);

  view->Copy();
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onEditCut(wxCommandEvent& ES_UNUSED(evt))
{
  EsTextEditorViewBase* view = currentTextEditorGet();
  ES_ASSERT(view);

  view->Cut();
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onEditPaste(wxCommandEvent& ES_UNUSED(evt))
{
  EsTextEditorViewBase* view = currentTextEditorGet();
  ES_ASSERT(view);

  view->Paste();
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onEditFind(wxCommandEvent& ES_UNUSED(evt))
{
  EsTextEditorViewBase* view = currentTextEditorGet();
  ES_ASSERT(view);

  const wxString& txt = view->GetSelectedText();
  dlgFindReplace(false, txt);
  view->textSearchReplacePositionSetCurrent();
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onEditReplace(wxCommandEvent& ES_UNUSED(evt))
{
  EsTextEditorViewBase* view = currentTextEditorGet();
  ES_ASSERT(view);

  const wxString& txt = view->GetSelectedText();
  dlgFindReplace(true, txt);
  view->textSearchReplacePositionSetCurrent();
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onEditBookmarkClearAll(wxCommandEvent & evt)
{
  EsTextEditorViewBase* view = currentTextEditorGet();
  ES_ASSERT(view);

  view->bookmarksClearAll();
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onEditBookmarkToggle(wxCommandEvent& evt)
{
  EsTextEditorViewBase* view = currentTextEditorGet();
  ES_ASSERT(view);

  if( usrID_EDIT_BOOKMARK == evt.GetId() )
    view->bookmarkToggle();
  else
  {
    view->bookmarkToggle(
      evt.GetId()-usrID_EDIT_BOOKMARK0
    );
  }
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onEditBookmarkNext(wxCommandEvent& ES_UNUSED(evt))
{
  EsTextEditorViewBase* view = currentTextEditorGet();
  ES_ASSERT(view);

  view->bookmarkGotoNext();
  //TODO: lookup other documents
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onEditBookmarkPrev(wxCommandEvent& ES_UNUSED(evt))
{
  EsTextEditorViewBase* view = currentTextEditorGet();
  ES_ASSERT(view);

  view->bookmarkGotoPrev();
  //TODO: lookup other documents
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onEditBookmarkGoto(wxCommandEvent& evt)
{
  EsTextEditorViewBase* view = currentTextEditorGet();
  ES_ASSERT(view);

  view->bookmarkGoto(evt.GetId()-usrID_EDIT_GOTO_BOOKMARK0);
  //TODO: lookup other documents
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onFileSaveAll(wxCommandEvent& WXUNUSED(evt))
{
  ES_DEBUG_TRACE(esT("EsSconsoleMain::onFileSaveAll"));

  const EsVariant::Array& docs = m_mgrMdi->documentsGet().asVariantCollection();
  for(auto const& vdoc : docs)
  {
    EsDocumentIntf::Ptr doc = vdoc.asExistingObject();
    ES_ASSERT(doc);

    if(!documentSave(doc, false)) //< Do not prompt for saving modified documents - just save these silently
      break;
  }
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onViewClose(wxAuiNotebookEvent& evt)
{
  ES_DEBUG_TRACE(esT("EsSconsoleMain::onViewClose"));

  evt.Veto(); // Perform actual close from ES event handler

  wxWindow* view = m_nbEditor->GetPage(
    evt.GetSelection()
  );
  ES_ASSERT(view);

  EsEventDispatcher::eventPost(
    ES_EVTC_APPLICATION,
    as_<ulong>(EsSconsoleEvt::DocViewCloseRequest),
    EsVariant(
      view,
      EsVariant::ACCEPT_POINTER
    )
  );
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onActiveViewChanged(wxAuiNotebookEvent& evt)
{
  ES_DEBUG_TRACE(esT("EsSconsoleMain::onActiveViewChanged"));

  int pageIdx = evt.GetSelection();
  ES_ASSERT(-1 < pageIdx);

  frameCaptionUpdateFromNbPage(pageIdx);
  currentDocViewChangeCheck();
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onScriptCompileBreak(wxCommandEvent& evt)
{
  if(!m_compiling)
    scriptCompile();
  else
    m_compiler.stopAndWait();
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onScriptRun(wxCommandEvent& ES_UNUSED(evt))
{
  ES_ASSERT(binaryScriptCanRun());
  binaryScriptGet()->run();
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onScriptDebug(wxCommandEvent& ES_UNUSED(evt))
{
  ES_ASSERT(binaryScriptCanRun() || binaryScriptIsDebugging());
  binaryScriptGet()->debugRun();
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onScriptDebugStep(wxCommandEvent& ES_UNUSED(evt))
{
  ES_ASSERT(binaryScriptCanRun() || binaryScriptIsDebugging());
  binaryScriptGet()->debugStep();
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onScriptAbort(wxCommandEvent& ES_UNUSED(evt))
{
  ES_ASSERT(binaryScriptIsRunning());
  binaryScriptGet()->abort();
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onWndAppLogToggle(wxCommandEvent& ES_UNUSED(evt))
{
  wxAuiPaneInfo& pane = m_mgrAui.GetPane(esT("pane_applog"));
  if(pane.IsShown())
  {
    pane.Hide();
  }
  else
  {
    pane.Show();
  }
  m_mgrAui.Update(); //< Commit structureal changes
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onWndCompLogToggle(wxCommandEvent& ES_UNUSED(evt))
{
  wxAuiPaneInfo& pane = m_mgrAui.GetPane(esT("pane_complog"));
  if(pane.IsShown())
  {
    pane.Hide();
  }
  else
  {
    pane.Show();
  }
  m_mgrAui.Update(); //< Commit structureal changes
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onWndDoclistToggle(wxCommandEvent& ES_UNUSED(evt))
{
  wxAuiPaneInfo& pane = m_mgrAui.GetPane(esT("pane_doclist"));
  if(pane.IsShown())
  {
    pane.Hide();
  }
  else
  {
    pane.Show();
  }
  m_mgrAui.Update(); //< Commit structureal changes
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onOptIncludeDebug(wxCommandEvent& ES_UNUSED(evt))
{
  ES_ASSERT(!binaryScriptIsRunning());

  wxGetApp().settingsAccess().m_inclDebugInfo = !wxGetApp().settingsAccess().m_inclDebugInfo;
  commonAppSettingsApply(true);
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onOptGenTranslatables(wxCommandEvent& ES_UNUSED(evt))
{
  ES_ASSERT(!binaryScriptIsRunning());

  wxGetApp().settingsAccess().m_translatablesSave = !wxGetApp().settingsAccess().m_translatablesSave;
  commonAppSettingsApply(true);
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onOptIncludePaths(wxCommandEvent& evt)
{
  ES_ASSERT(!binaryScriptIsRunning());

  EsPathsListDlg dlg(
    this,
    _i("Configure script include look-up directories"),
    _i("Select include directory"),
    _i("Include directories:")
  );

  dlg.foldersSet(
    wxGetApp().settingsAccess().m_includes
  );

  EsStreamContextExistingOrNewScope ctx(
    m_settings,
    esT("IncludesDlg")
  );
  if(ctx.isOk())
    EsUtilities::windowPosLoad(
      m_settings,
      &dlg,
      EsPathsListDlg::minSizeGet()
    );

  dlg.showModal(
    [this](const EsDlgBase& Sender, int modalResult)
  {
    if(wxID_OK == modalResult)
    {
      wxGetApp().settingsAccess().m_includes = static_cast<const EsPathsListDlg&>(Sender).foldersGet();
      commonAppSettingsApply(true);
    }
  }
  );

  if(ctx.isOk())
    EsUtilities::windowPosSave(
      m_settings,
      &dlg
    );
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onOptLinkPaths(wxCommandEvent& evt)
{
  ES_ASSERT(!binaryScriptIsRunning());

  EsPathsListDlg dlg(
    this,
    _i("Configure script link look-up directories"),
    _i("Select link directory"),
    _i("Link directories:")
  );

  dlg.foldersSet(
    wxGetApp().settingsAccess().m_linkPaths
  );

  EsStreamContextExistingOrNewScope ctx(
    m_settings,
    esT("LinksDlg")
  );
  if(ctx.isOk())
    EsUtilities::windowPosLoad(
      m_settings,
      &dlg,
      EsPathsListDlg::minSizeGet()
    );

  dlg.showModal(
    [this](const EsDlgBase& Sender, int modalResult)
  {
    if(wxID_OK == modalResult)
    {
      wxGetApp().settingsAccess().m_linkPaths = static_cast<const EsPathsListDlg&>(Sender).foldersGet();
      commonAppSettingsApply(true);
    }
  }
  );

  if(ctx.isOk())
    EsUtilities::windowPosSave(
      m_settings,
      &dlg
    );
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onOptLangSelected(wxCommandEvent& evt)
{
  ES_DEBUG_TRACE(esT("EsSconsoleMain::onOptLangSelected"));

  ulong langIdx = evt.GetId()-usrID_LANG_ID_BASE;

  ES_ASSERT(langIdx < EsStringI18n::instanceGet().availableLocalesGet().size());

  EsStringI18n& i18n = EsStringI18n::instanceGet();

  const EsString& loc = i18n.availableLocalesGet()[langIdx];
  i18n.currentLocaleSet(loc);
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onHelpAbout(wxCommandEvent& ES_UNUSED(evt))
{
  wxAboutDialogInfo aboutInfo;
  aboutInfo.SetName(PRODUCT_NAME);
  aboutInfo.SetVersion(PRODUCT_VERSION);
  aboutInfo.SetDescription(PRODUCT_DESCRIPTION);
  aboutInfo.SetCopyright(PRODUCT_COPYRIGHT);
  aboutInfo.SetWebSite(PRODUCT_URL);
  aboutInfo.AddDeveloper(PRODUCT_AUTHOR);

  wxAboutBox(aboutInfo);
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onHelp(wxCommandEvent& ES_UNUSED(evt))
{
  EsPath path = EsPath::createFromPath(
    EsSconsoleApp::docsFolderGet()
  );

  path.fileNameSet(esT("help"));
  path.fileExtSet(esT("pdf"));

  wxShell(
    path.pathGet().c_str()
  );
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onHelpDocument(wxCommandEvent& evt)
{
  ulong id = evt.GetId();

  EsPath path = EsPath::createFromPath(
    EsSconsoleApp::docsFolderGet()
  );

  switch(id)
  {
  case usrID_HLP_ESCORE:
    path.fileNameSet(esT("escore"));
    break;
  case usrID_HLP_ESCOMM:
    path.fileNameSet(esT("escomm"));
    break;
  case usrID_HLP_ESMATH:
    path.fileNameSet(esT("esmath"));
    break;
  case usrID_HLP_ESSCRIPT:
    path.fileNameSet(esT("esscript"));
    break;
  case usrID_HLP_ESSCRIPTING:
    path.fileNameSet(esT("ES Script cookbook"));
    break;
  }

  path.fileExtSet(esT("pdf"));

  const wxString& file = path.pathGet().c_str();

  wxMimeTypesManager mime;
  std::unique_ptr<wxFileType> type( mime.GetFileTypeFromExtension(esT("pdf")) );
  if(!type)
  {
    wxLogWarning(
      wxString::Format(
        _("Could not open help file '%s', no applicable viewer application is found for extension '%s'"),
        file,
        esT("PDF")
      )
    );
    return;
  }

  const wxString& cmd = type->GetOpenCommand(file);
  if(cmd.IsEmpty())
  {
    wxLogWarning(
      wxString::Format(
        _("Could not find OPEN verb for a help file '%s'"),
        file
      )
    );
    return;
  }

  wxExecute(cmd);
}
//--------------------------------------------------------------------------------

#if defined(__WXMSW__)
void EsSconsoleMain::onAutoUpdate(wxCommandEvent& ES_UNUSED(evt))
{
  m_au.autoUpdateSet(
    !m_au.autoUpdateGet()
  );
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onOnlineUpdate(wxCommandEvent& ES_UNUSED(evt))
{
  m_au.updateCheck(true);
}
#endif
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

static int scTxtFlagsFromSearchReplaceFlags(int flags)
{
  int txtFlags = 0;
  if(flags & wxFR_MATCHCASE)
    txtFlags |= wxSTC_FIND_MATCHCASE;
  if(flags & wxFR_WHOLEWORD)
    txtFlags |= wxSTC_FIND_WHOLEWORD;

  return txtFlags;
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onDlgFindReplaceEvent(wxFindDialogEvent& evt)
{
  wxEventType type = evt.GetEventType();
  EsTextEditorViewBase* view = currentTextEditorGet();

  if(
    type == wxEVT_FIND ||
    type == wxEVT_FIND_NEXT
  )
  {
    if(!view)
      return;

    int flags = evt.GetFlags();
    bool down = view->textSearchReplaceDirectionGet();
    if(down != (wxFR_DOWN == (flags & wxFR_DOWN)))
      view->textSearchReplaceDirectionSet(!down);

    if(
      view->textSearch(
        evt.GetFindString(),
        scTxtFlagsFromSearchReplaceFlags(flags)
      )
    )
    {
      view->GotoPos(
        view->textSearchReplacePosGet()
      );

      int from, to;
      view->textSearchReplaceCurrentRangeGet(from, to);
      view->SetSelection(from, to);
    }
  }
  else if(
    type == wxEVT_FIND_REPLACE ||
    type == wxEVT_FIND_REPLACE_ALL
  )
  {
    if(!view)
      return;

    int flags = evt.GetFlags();
    bool down = view->textSearchReplaceDirectionGet();
    if(down != (wxFR_DOWN == (flags & wxFR_DOWN)))
      view->textSearchReplaceDirectionSet(!down);

    if(
      view->textReplace(
        evt.GetFindString(),
        evt.GetReplaceString(),
        scTxtFlagsFromSearchReplaceFlags(flags),
        (type == wxEVT_FIND_REPLACE_ALL)
      )
    )
    {
      view->GotoPos(
        view->textSearchReplacePosGet()
      );
    }
  }
  else if(type == wxEVT_FIND_CLOSE)
  {
    wxFindReplaceDialog *dlg = evt.GetDialog();
    ES_ASSERT(dlg);

    m_posFr = dlg->GetPosition();
    dlg->Destroy();
    m_dlgFr = nullptr;
  }
#ifdef ES_DEBUG
  else
  {
    ES_FAIL_MSG(esT("Unknown wxFindDialog event type!"));
  }
#endif
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onI18nLocaleChanged(const EsString& lang)
{
#if defined(__WXMSW__)
  m_au.langSet(lang);
#endif
}
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
// ES events
//

void EsSconsoleMain::onDocumentCreated(const EsString& key, const EsVariant& params)
{
  ES_DEBUG_TRACE(esT("EsSconsoleMain::onDocumentCreated"));

  ES_ASSERT(!key.empty());

  EsDocumentIntf::Ptr doc = m_mgrMdi->documentFind(key).asExistingObject();
  ES_ASSERT(doc);

  documentViewCreate(
    key,
    doc
  );

  // Handle batch execution of the compiled|opened binary script
  if(
    doc->is(EsCompiledScriptDocument::classNameGetStatic()) &&
    isExecutingBatch()
    )
  {
    if(!m_batchCmds->m_ofile.empty())
      doc->write(
        m_batchCmds->m_ofile,
        settingsToCompiledScriptDocumentParams(
          m_batchCmds->m_encryptOutput ?
          defaultEncKeyGet() :
          EsString::null()
        )
      );

    if(m_batchCmds->m_runScript)
    {
      binaryScriptRun(
        doc,
        m_batchCmds->m_entry,
        m_batchCmds->m_params
      );
    }
    else
      batchComplete();
  }

  documentViewParamsHandle(
    key,
    params
  );
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onDocumentOpened(const EsString& key, const EsVariant& params)
{
  ES_DEBUG_TRACE(esT("EsSconsoleMain::onDocumentOpened"));

  ES_ASSERT(!key.empty());

  EsDocumentIntf::Ptr doc = m_mgrMdi->documentFind(key).asExistingObject();
  ES_ASSERT(doc);

  auto cit = m_views.find(key);
  if(cit != m_views.end())
    documentViewUpdate(
      (*cit).second,
      doc
    );
  else
    documentViewCreate(
      key,
      doc
    );

  documentViewParamsHandle(
    key,
    params
  );
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onDocumentClosed(const EsString& key, const EsString& type)
{
  ES_DEBUG_TRACE(esT("EsSconsoleMain::onDocumentClosed"));

  wxWindow* view = documentViewByKeyGet(key);
  if(view)
    documentViewClose(view);

  if(
    !isExecutingBatch() &&
    EsPath::fileExists(
      key,
      EsString::null()
    )
  )
    m_mru.AddFileToHistory(
      key.c_str()
    );

  if( type == EsCompiledScriptDocument::classNameGetStatic() )
  {
    binDocPtrUpdateInternal(nullptr);
    EsEventDispatcher::eventPost(
      ES_EVTC_APPLICATION,
      as_<ulong>(EsSconsoleEvt::CompiledScriptClosed)
    );
  }
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onDocumentChanged(const EsString& key, const EsString& subj, void* sender)
{
  ES_DEBUG_TRACE(
    esT("EsSconsoleMain::onDocumentChanged(key=%s, subj=%s, sender=%p)"),
    key,
    subj,
    EsVariant(
      sender,
      EsVariant::ACCEPT_POINTER
    )
  );

  const EsVariant& vdoc = m_mgrMdi->documentFind(key);
  if(vdoc.isEmpty())
    return;

  EsDocumentIntf::Ptr doc = vdoc.asObject();
  if(!doc)
    return;

  wxWindow* view = documentViewByKeyGet(key);

  documentViewUpdate(
    view,
    doc
  );

  if( doc->is(EsCompiledScriptDocument::classNameGetStatic()) )
  {
    ES_DEBUG_TRACE(esT("Issue EsSconsoleEvt::CompiledScriptChanged event"));

    EsEventDispatcher::eventPost(
      ES_EVTC_APPLICATION,
      as_<ulong>(EsSconsoleEvt::CompiledScriptChanged),
      doc
    );
  }
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onDocumentStateChanged(const EsString& key)
{
  ES_DEBUG_TRACE(esT("EsSconsoleMain::onDocumentStateChanged"));

  EsDocumentIntf::Ptr doc = m_mgrMdi->documentFind(key).asObject();
  if(!doc)
    return;

  wxWindow* view = documentViewByKeyGet(key);

  documentViewUpdate(
    view,
    doc
  );
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onDocumentViewCloseRequest(wxWindow* view)
{
  ES_DEBUG_TRACE(esT("EsSconsoleMain::onDocumentViewCloseRequest"));
  ES_ASSERT(view);

  // Find key by view
  const EsString& key = keyByDocumentViewGet(view);
  ES_ASSERT(!key.empty());

  documentSaveByKey(key);
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onDocumentListCloseRequest(const EsString::Array& keys)
{
  for(const EsString& key : keys)
    if( !documentSaveByKey(key) )
      break;
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onDocumentKeyChanged(const EsString& keyOld, const EsString& keyNew)
{
  ES_DEBUG_TRACE(esT("EsSconsoleMain::onDocumentKeyChanged"));

  wxWindow* view = documentViewByKeyGet(keyOld);

  if(view)
  {
    m_views.erase(keyOld);
    m_views[keyNew] = view;

    EsDocumentIntf::Ptr doc = m_mgrMdi->documentFind(keyNew).asExistingObject();
    ES_ASSERT(doc);

    documentViewUpdate(
      view,
      doc
    );
  }
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onCompilationStart()
{
  m_compiling = true;
  m_compiledOk = false;

  scriptCompiationTextUpdate();
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onCompilationAborted()
{
  m_compiling = false;
  m_compiledOk = false;

  scriptCompiationTextUpdate();

  // Terminate batch execution
  batchReset();
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onCompilationEnd(const EsString& input, const EsVariant& compiledScript)
{
  m_compiling = false;
  m_compiledOk = !compiledScript.isEmpty();

  scriptCompiationTextUpdate();

  if(compiledScript.isEmpty())
  {
    // Terminate batch if no comiled output is set, prevent auto closing in this case
    batchComplete(false);
    return;
  }

  const EsPath& fpathInput = EsPath::createFromFilePath(input);
  const EsString& inputName = fpathInput.fileNameGet();
  const EsString& defExt = m_mgrMdi->documentDefaultExtGet(EsCompiledScriptDocument::classNameGetStatic());
  const EsString& defNewKey = inputName + esT(".") + defExt;

  EsDocumentIntf::Ptr docSingle = m_mgrMdi->documentFindFirstByType(EsCompiledScriptDocument::classNameGetStatic()).asObject();
  if(!docSingle)
    docSingle = m_mgrMdi->documentCreate(
      EsCompiledScriptDocument::classNameGetStatic(),
      defNewKey
    ).asObject();

  ES_ASSERT(docSingle);

  EsCompiledScriptDocument* docPtr = ES_INTFPTR_TO_OBJECTPTR<EsCompiledScriptDocument>(docSingle);
  ES_ASSERT(docPtr);
  docPtr->keySet(
    defNewKey
  );
  docPtr->contentSet(
    compiledScript.asExistingObject()
  );
  docPtr->documentChangedNotify(
    esT("content"),
    this
  );
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onScriptFinished(bool hasErrors)
{
  if(isExecutingBatch())
    batchComplete(
      !hasErrors
    );

  scriptDebugLabelsAndIconsUpdate();
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onScriptAborted()
{
  if(isExecutingBatch())
    batchComplete(false);

  scriptDebugLabelsAndIconsUpdate();
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onScriptDebugPaused(const EsString& file, ulong line, bool ES_UNUSED(isBreakpoint))
{
  documentOpenAndSetPosition(
    file,
    line,
    static_cast<ulong>(0),
    true
  );
}
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

void EsSconsoleMain::documentFileOpenOrActivate(const EsString& documentPath, const EsVariant& params, std::set<EsString>& banNextTime, bool preferActivate /*= false*/)
{
  wxWindow* view = documentViewByKeyGet(documentPath);

  if(preferActivate && view)
  {
    if(m_activeView != view)
      m_nbEditor->SetSelection(
        m_nbEditor->GetPageIndex(view)
      );

    EsScriptEditorView* srcview = dynamic_cast<EsScriptEditorView*>(view);

    if(srcview)
      documentViewParamsHandle(
        documentPath,
        params
      );

    return;
  }

  const EsPath& path = EsPath::createFromFilePath(documentPath);

  // Get document type by selected file extension
  const EsString& type = m_mgrMdi->documentTypeFindByFileExt(
    path.fileExtGet()
  );

  if(type.empty())
    EsException::Throw(
      _("Could not find registered document type for file extension '%s'. File type unknown or not supported."),
      path.fileExtGet()
    );

  documentFileOpen(
    banNextTime,
    type,
    path.pathGet(),
    params
  );
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::documentOpenAndSetPosition(const EsString& documentPath, const EsVariant& line, const EsVariant& col, bool executionMode)
{
  std::set<EsString> banNextTime;

  const EsVariant::Array& params = {
    documentPath, //< For compliance with parameters usage in other cases
    executionMode,
    line,
    col
  };

  documentFileOpenOrActivate(
    documentPath,
    params,
    banNextTime,
    true
  );
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onDocumentActivate(const EsString& documentPath)
{
  documentOpenAndSetPosition(
    documentPath,
    EsVariant::null(),
    EsVariant::null(),
    false
  );
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::onAllDocumentsClosed()
{
  docPtrsReset();
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::uniqueParamsAppend(EsVariant::Array& out, const EsVariant::Array& in, EsVariant::Type ifType /*= EsVariant::VAR_EMPTY*/)
{
  for(const EsVariant& val : in)
  {
    if(
      out.end() == std::find(
        out.begin(),
        out.end(),
        val
      )
    )
      out.push_back(val);
    else if( ifType != EsVariant::VAR_EMPTY && val.typeGet() != ifType)
      out.push_back(val);
  }
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::documentFileOpen(std::set<EsString>& banNextTime, const EsString& type, const EsString& fpath, const EsVariant& params)
{
  if(banNextTime.find(type) != banNextTime.end())
    return;

  if(!EsPath::fileExists(fpath, EsString::null()))
  {
    wxMessageBox(
      wxString::Format(
        _("Could not open document '%s',\nfile does not exist"),
        fpath.c_str()
      ),
      _("Document is not found"),
      wxOK | wxOK_DEFAULT | wxCENTER | wxICON_ERROR,
      this
    );

    int cnt = m_mru.GetCount();
    int idxFound = -1;
    for(int idx = 0; idx < cnt; ++idx)
    {
      const wxString& historyFile = m_mru.GetHistoryFile(idx);
      if(0 == historyFile.CompareTo(fpath.c_str(), wxString::ignoreCase))
      {
        idxFound = idx;
        break;
      }
    }

    if(-1 < idxFound)
      m_mru.RemoveFileFromHistory(
        idxFound
      );

    return;
  }

  if(m_mgrMdi->documentIsSingleton(type).asBool()) //< Open only the first one selected singleton document
    banNextTime.insert(type);

  // Deduce default parameters for compiled script document
  const EsVariant& docParams = documentParamsDeduceByDocTypeAndKey(
    type,
    fpath
  );

  EsVariant openParams;
  if(!docParams.isEmpty())
  {
    openParams.setToNull(EsVariant::VAR_VARIANT_COLLECTION);
    openParams.addToVariantCollection(fpath);
    openParams.addToVariantCollection(docParams);

    if(params.isCollection())
      uniqueParamsAppend(
        openParams.doInterpretAsVariantCollection(),
        params.doInterpretAsVariantCollection(),
        EsVariant::VAR_STRING
      );
  }
  else
  {
    if(params.isCollection())
    {
      openParams.setToNull(EsVariant::VAR_VARIANT_COLLECTION);
      openParams.addToVariantCollection(fpath);
      uniqueParamsAppend(
        openParams.doInterpretAsVariantCollection(),
        params.doInterpretAsVariantCollection(),
        EsVariant::VAR_STRING
      );
    }
    else
      openParams = fpath;
  }

  ES_DEBUG_TRACE(
    esT("EsSconsoleMain::documentFileOpen type=%s, fpath=%s,\ndocParams:\n%s\nparams:\n%s\nopenParams:\n%s"),
    type,
    fpath,
    EsVariant::dump(docParams),
    EsVariant::dump(params),
    EsVariant::dump(openParams)
  );

  m_mgrMdi->documentOpen(
    type,
    openParams
  );
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::documentViewCreate(const EsString& key, const EsDocumentIntf::Ptr& doc)
{
  ES_ASSERT(doc);

  const EsString& type = doc->typeNameGet();
  if(EsScriptDocument::classNameGetStatic() == type)
    scriptViewCreate(
      key,
      doc
    );
  else if(EsCompiledScriptDocument::classNameGetStatic() == type)
    compiledScriptViewCreate(
      key,
      doc
    );
  else if(EsTextDocument::classNameGetStatic() == type)
    textViewCreate(
      key,
      doc
    );
}
//--------------------------------------------------------------------------------

wxWindow* EsSconsoleMain::documentViewByKeyGet(const EsString& key) const ES_NOTHROW
{
  auto cit = m_views.find(key);
  if(cit != m_views.end())
    return (*cit).second;

  return nullptr;
}
//--------------------------------------------------------------------------------

EsString EsSconsoleMain::keyByDocumentViewGet(wxWindow* view) const ES_NOTHROW
{
  for(auto const& item : m_views)
  {
    if(view == item.second)
      return item.first;
  }

  return EsString::null();
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::documentViewAdd(wxWindow* view, const EsString& key, const EsDocumentIntf::Ptr& doc)
{
  ES_ASSERT(view);
  ES_ASSERT(!key.empty());
  ES_ASSERT(doc);

  wxBitmap img;
  bool activate = true;

  const wxSize& tabimgsze = EsUtilities::appSizePropertyGet(ES_APP_OPT_TAB_IMG_WH);

  if( doc->is(EsTextDocument::classNameGetStatic()) )
  {
    img = wxArtProvider::GetBitmap(
      wxART_NORMAL_FILE,
      wxART_OTHER,
      tabimgsze
    );
  }
  else if(doc->is(EsScriptDocument::classNameGetStatic()))
  {
    img = wxArtProvider::GetBitmap(
      esART_SCRIPT_FILE,
      wxART_OTHER,
      tabimgsze
    );
  }
  else if( doc->is(EsCompiledScriptDocument::classNameGetStatic()))
  {
    img = wxArtProvider::GetBitmap(
      wxART_EXECUTABLE_FILE,
      wxART_OTHER,
      tabimgsze
    );
    activate = false;
  }

  m_views[key] = view;
  m_nbEditor->AddPage(
    view,
    wxEmptyString,
    activate,
    img
  );
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::documentViewAddToNotebook(wxWindow* view, const EsString& key, const EsDocumentIntf::Ptr& doc)
{
  ES_ASSERT(view);
  ES_ASSERT(doc);

  wxWindowUpdateLocker lock(m_nbEditor);
  documentViewAdd(view, key, doc);
  documentViewUpdate(view, doc);
  currentDocViewChangeCheck();
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::currentDocViewChangeCheck()
{
  ES_DEBUG_TRACE(esT("EsSconsoleMain::currentDocViewChangeCheck"));

  wxWindow* view = m_nbEditor->GetCurrentPage();
  if(m_activeView != view)
  {
    // Remove custom editor view context menu from main menu
    m_mnuEdit->Destroy(
      usrID_EDIT_CUSTOM_CTX_MENU
    );

    m_activeView = view;

    currentDocPtrUpdate();

    EsTextEditorViewBase* txtView = dynamic_cast<EsTextEditorViewBase*>(m_activeView);
    if(txtView)
    {
      // Create new context menu
      wxMenuPtr customCtx = txtView->customCtxMenuGet();
      if(customCtx)
      {
        std::unique_ptr<wxMenu> ctxMenu(
          EsUtilities::menuCloneCreate(
            customCtx.get()
          )
        );
        ES_ASSERT(ctxMenu);

        wxMenuItem* item = m_mnuEdit->AppendSubMenu(
          ctxMenu.release(),
          _("Advanced"),
          _("Advanced editor commands")
        );
        ES_ASSERT(item);

        item->SetId(
          usrID_EDIT_CUSTOM_CTX_MENU
        );
      }

      // Attach new handlers
      txtView->customCtxMenuEvtHandlersSet(
        this,
        true
      );
    }
  }
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::textViewCreate(const EsString& key, const EsDocumentIntf::Ptr& doc)
{
  EsTextEditorView* view = EsTextEditorView::create(
    m_nbEditor
  );
  ES_ASSERT(view);

  view->documentConnect(doc);

  documentViewAddToNotebook(
    view,
    key,
    doc
  );
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::scriptViewCreate(const EsString& key, const EsDocumentIntf::Ptr& doc)
{
  EsScriptEditorView* view = EsScriptEditorView::create(
    m_nbEditor
  );
  ES_ASSERT(view);

  view->documentConnect(doc);

  documentViewAddToNotebook(
    view,
    key,
    doc
  );
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::compiledScriptViewCreate(const EsString& key, const EsDocumentIntf::Ptr& doc)
{
  EsCompiledScriptView* view = new EsCompiledScriptView(
    m_nbEditor
  );
  ES_ASSERT(view);

  documentViewAddToNotebook(
    view,
    key,
    doc
  );

  // Just in case - update background docptr for compiled script document
  binDocPtrUpdateInternal(
    ES_INTFPTR_TO_OBJECTPTR<EsCompiledScriptDocument>(doc)
  );
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::documentSaveInternal(const EsDocumentIntf::Ptr& doc, const EsString& target)
{
  const EsString& oldKey = doc->keyGet().asString();

  doc->write(
    target,
    documentParamsDeduceByDocTypeAndKey(
      doc->typeNameGet(),
      target
    )
  );
  ES_ASSERT(target == doc->keyGet().asString());

  // Document key may change here, but out view mapping is still using an old one
  // Make consistent changes at once, because we know what we're doing
  //
  if(oldKey != target)
    onDocumentKeyChanged(
      oldKey,
      target
    );
}
//--------------------------------------------------------------------------------

bool EsSconsoleMain::documentSaveByKey(const EsString& key)
{
  const EsDocumentIntf::Ptr& doc = m_mgrMdi->documentFind(key).asExistingObject();
  ES_ASSERT(doc);

  if( documentSave(doc) )
  {
    m_mgrMdi->documentClose(
      doc->keyGet()
    );

    return true;
  }

  return false;
}
//--------------------------------------------------------------------------------

bool EsSconsoleMain::documentSave(const EsDocumentIntf::Ptr& doc, bool promptToSaveModified /*= true*/)
{
  ES_ASSERT(doc);

  if(!doc->isModified())
    return true;

  EsString newPath;
  int result = documentPrepareForSave(
    doc,
    promptToSaveModified ?
    PromptSaveModified :
    0,
    newPath
  );

  if(wxOK == result)
  {
    const EsString& target = doc->isNew() ? newPath : doc->keyGet().asString();

    documentSaveInternal(
      doc,
      target
    );

    return true;
  }

  return wxNO == result;
}
//--------------------------------------------------------------------------------

bool EsSconsoleMain::documentSaveAs(const EsDocumentIntf::Ptr& doc)
{
  ES_ASSERT(doc);

  EsString newPath;
  int result = documentPrepareForSave(
    doc,
    SaveAs,
    newPath
  );

  if(wxOK == result)
  {
    ES_ASSERT(!newPath.empty());

    documentSaveInternal(
      doc,
      newPath
    );

    return true;
  }

  return wxNO == result;
}
//--------------------------------------------------------------------------------

bool EsSconsoleMain::documentsCloseAll(bool promptForSaveModified /*= true*/)
{
  EsUtilities::EsScopedAction currentDocptrGuard(
    [this]{
      m_changingDocptrs = true;
    },
    [this] {
      m_changingDocptrs = false;
    }
  );

  const EsVariant::Array& docs = m_mgrMdi->documentsGet().asVariantCollection();
  for(auto const& vdoc : docs)
  {
    EsDocumentIntf::Ptr doc = vdoc.asExistingObject();
    ES_ASSERT(doc);

    if(!documentSave(doc, promptForSaveModified))
      return false;

    m_mgrMdi->documentClose(doc->keyGet());
  }

  return true;
}
//--------------------------------------------------------------------------------

EsTextEditorViewBase* EsSconsoleMain::currentTextEditorGet()
{
  return dynamic_cast<EsTextEditorViewBase*>(m_nbEditor->GetCurrentPage());
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::documentViewParamsHandle(const EsString& key, const EsVariant& params)
{
  ES_DEBUG_TRACE(
    esT("EsSconsoleMain::documentViewParamsHandle key='%s', params:\n%s"),
    key,
    EsVariant::dump(params)
  );

  if(params.isEmpty() || !params.isVariantCollection())
    return;

  EsScriptEditorView* view = dynamic_cast<EsScriptEditorView*>(
    documentViewByKeyGet(key)
  );
  if(!view)
    return;

  const EsVariant::Array& aparams = params.asVariantCollection();
  if(aparams[1].asBool() && aparams[2].isNumeric() ) //< We're selecting position in execution mode
  {
    long line = aparams[2].asLong();
    if( -1 < line )
      view->currentExecutionLineSet(
        line,
        true
      );
  }
  else //< Editing|compilation position selection mode
  {
    view->SetFocus();

    if(
      aparams[2].isNumeric() &&
      aparams[3].isNumeric()
    )
      view->currentPositionSet(
        aparams[2].asLong(),
        aparams[3].asLong()
      );
  }
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::documentViewUpdate(wxWindow* view, const EsDocumentIntf::Ptr& doc)
{
  ES_ASSERT(view);
  ES_ASSERT(doc);

  int idx = m_nbEditor->GetPageIndex(view);
  ES_ASSERT(-1 < idx);

  const EsString& key = doc->keyGet().doInterpretAsString();

  wxFileName fname(key.c_str());
  wxString tabTxt = fname.GetFullName();
  if(doc->isModified())
    tabTxt += esT("*");

  m_nbEditor->SetPageText(
    idx,
    tabTxt
  );
  m_nbEditor->SetPageToolTip(
    idx,
    key.c_str()
  );

  if(idx == m_nbEditor->GetSelection()) //< Update main frame cation for an active page
    frameCaptionUpdateFromNbPage(idx);

  EsCompiledScriptView* scriptView = dynamic_cast<EsCompiledScriptView*>(view);
  if(scriptView)
  {
    EsCompiledScriptDocument* binDoc = ES_INTFPTR_TO_OBJECTPTR<EsCompiledScriptDocument>(doc);
    ES_ASSERT(binDoc);

    scriptView->progressMonitorAssign(
      binDoc->progressMonitorGet()
    );
  }
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::documentViewClose(wxWindow* view)
{
  ES_DEBUG_TRACE(esT("EsSconsoleMain::documentViewClose"));

  ES_ASSERT(view);

  int idx = m_nbEditor->GetPageIndex(view);
  ES_ASSERT(-1 < idx);

  // Detach old handlers && custom menu items for an active text edit view
  if(m_activeView == view)
  {
    EsTextEditorViewBase* txtView = dynamic_cast<EsTextEditorViewBase*>(view);
    if(txtView)
    {
      txtView->customCtxMenuEvtHandlersSet(
        this,
        false
      );
    }
  }

  m_nbEditor->DeletePage(idx);

  const EsString& key = keyByDocumentViewGet(view);
  m_views.erase(key);

  if(0 == m_nbEditor->GetPageCount())
    frameCaptionUpdateFromNbPage(-1);
  currentDocViewChangeCheck();
}
//--------------------------------------------------------------------------------

int EsSconsoleMain::selectNewFilePath(const EsDocumentIntf::Ptr& doc, EsString& newPath)
{
  ES_ASSERT(doc);
  newPath = EsString::null();

  const EsVariant& regInfo = m_mgrMdi->documentRegistrationPayloadGet(
    doc->typeNameGet()
  );
  const EsString& key = doc->keyGet().asString();

  wxFileDialog dlgSave(
    this,
    wxString::Format(
      _("Save '%s'"),
      key.c_str()
    ),
    wxEmptyString,
    wxEmptyString,
    regInfo[esVT("filterStr")][1].asString().c_str(),
    wxFD_SAVE | wxFD_OVERWRITE_PROMPT | wxFD_CHANGE_DIR | wxFD_NO_FOLLOW,
    wxDefaultPosition,
    wxDefaultSize
  );

  wxFileName fname(key.c_str());

  dlgSave.SetDirectory(fname.GetPath());
  dlgSave.SetFilename(fname.GetFullName());

  if(wxID_OK != dlgSave.ShowModal())
    return wxNO;

  newPath = wxFileName(
    dlgSave.GetDirectory(),
    dlgSave.GetFilename()
  ).GetFullPath().t_str();

  return wxOK;
}
//--------------------------------------------------------------------------------

int EsSconsoleMain::documentPrepareForSave(const EsDocumentIntf::Ptr& doc, int flags, EsString& newPath)
{
  ES_ASSERT(doc);

  newPath = EsString::null();
  if(doc->isModified() || (flags & SaveAs))
  {
    if(doc->isModified() && (flags & PromptSaveModified))
    {
      int response = wxMessageBox(
        wxString::Format(
          _("Document '%s' have unsaved changes.\nDo you want to save it?"),
          doc->keyGet().asString().c_str()
        ),
        _("Save document"),
        wxICON_EXCLAMATION | wxYES | wxNO | wxCANCEL | wxYES_DEFAULT | wxCENTER,
        this
      );

      switch(response)
      {
      case wxNO:
      case wxCANCEL:
        return response;
      case wxYES:
        break;
      default:
        return wxNO;
      }
    }

    if(doc->isNew() || (flags & SaveAs))
    {
_re_query_new_path:

      int response = selectNewFilePath(
        doc,
        newPath
      );

      if(wxOK != response)
        return wxNO;

      if(!m_mgrMdi->documentFind(newPath).isEmpty())
      {
        wxMessageBox(
          wxString::Format(
            _("Document '%s' could not be saved to '%s',\nbecause it is already open in another window."),
            doc->keyGet().asString().c_str(),
            newPath.c_str()
          ),
          _("Document already open"),
          wxICON_WARNING | wxOK | wxOK_DEFAULT | wxCENTER,
          this
        );

        goto _re_query_new_path;
      }
    }
  }

  return wxOK;
}
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

EsDocument* EsSconsoleMain::currentDocPtrGet() ES_NOTHROW
{
  if(m_changingDocptrs) //< Do not touch ptrs while m_mgr in in process of changing them
    return nullptr;

  if(DocPtrType::None == m_docPtrs.m_docPtrType)
    return nullptr;

  switch(m_docPtrs.m_docPtrType)
  {
  case DocPtrType::Text:
    ES_ASSERT(m_docPtrs.m_textDocPtr);
    return m_docPtrs.m_textDocPtr;
  case DocPtrType::Script:
    ES_ASSERT(m_docPtrs.m_scriptDocPtr);
    return m_docPtrs.m_scriptDocPtr;
  case DocPtrType::Binary:
    ES_ASSERT(m_docPtrs.m_compiledDocPtr);
    return m_docPtrs.m_compiledDocPtr;
  }

  ES_FAIL; //< We're never here!
  return nullptr;
}
//--------------------------------------------------------------------------------

EsDocumentIntf::Ptr EsSconsoleMain::currentDocumentGet() const ES_NOTHROW
{
  if(m_activeView)
  {
    const EsString& key = keyByDocumentViewGet(m_activeView);
    const EsVariant& doc = m_mgrMdi->documentFind(key);

    if(!doc.isEmpty())
      return doc.asObject();
  }

  return nullptr;
}
//--------------------------------------------------------------------------------

bool EsSconsoleMain::haveAnyOpenDocuments() const ES_NOTHROW
{
  return 0 < m_mgrMdi->documentsCountGet();
}
//--------------------------------------------------------------------------------

bool EsSconsoleMain::canSaveCurrentDocument() const ES_NOTHROW
{
  const EsDocument* docptr = currentDocPtrGet();
  if(!docptr)
    return false;

  return docptr->isModified();
}
//--------------------------------------------------------------------------------

bool EsSconsoleMain::haveAnyModifiedDocuments() const ES_NOTHROW
{
  const EsVariant::Array& docs = m_mgrMdi->documentsGet().asVariantCollection();
  for(auto const& vdoc : docs)
  {
    EsDocumentIntf::Ptr doc = vdoc.asExistingObject();
    ES_ASSERT(doc);

    if(doc->isModified())
      return true;
  }

  return false;
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::frameCaptionUpdateFromNbPage(int pageIdx)
{
  if(-1 < pageIdx)
  {
    wxString text = m_nbEditor->GetPageToolTip(pageIdx);
    if(text.empty())
      text = m_nbEditor->GetPageText(pageIdx);
    else if(text.Length() > fileFrameCaptionTxtLenMax)
    {
      text = text.Mid(text.Length() - fileFrameCaptionTxtLenMax - 1);
      text = esT("‪…") + text;
    }

    if(text.empty()) //< We have not set-up NB page yet, postpone until direct call from viewUpdate
      return;

    const wxString& title = wxString::Format(
      esT("%s [%s]"),
      wxGetApp().GetAppDisplayName(),
      text
    );

    SetTitle(
      title
    );
  }
  else
    SetTitle(
      wxGetApp().GetAppDisplayName()
    );
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::batchComplete(bool allowClose /*=true*/)
{
  if(!isExecutingBatch())
    return;

  ES_DEBUG_TRACE(
    esT("EsSconsoleMain::batchComplete(allowClose=%s)"),
    allowClose ? esVT("true") : esVT("false")
  );

  if(allowClose && m_batchCmds->m_exitUponCompletion)
    EsEventDispatcher::eventPost(
      ES_EVTC_APPLICATION,
      as_<ulong>(EsSconsoleEvt::ApplicationCloseRequest),
      true //< Close unconditionally
    );

  batchReset();
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::batchReset() ES_NOTHROW
{
  ES_DEBUG_TRACE(esT("EsSconsoleMain::batchReset"));

  m_batchCmds = nullptr;
}
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

void EsSconsoleMain::scriptCompile(const EsDocumentIntf::Ptr& doc)
{
  ES_ASSERT(doc);
  ES_ASSERT(doc->is(EsScriptDocument::classNameGetStatic()));

  if(doc->isNew())
  {
    m_compiler.sourceSet(
      doc->valueGet(esT("content")).doInterpretAsString(),
      true //< Literal text source
    );

    m_compiler.sourceNameSet(
      doc->keyGet().asString()
    );
  }
  else
  {
    const EsString& filePath = doc->keyGet().asString();

    if(doc->isModified())
      doc->write(filePath);

    m_compiler.sourceSet(
      filePath,
      false //< File is not literal text
    );
  }

  m_compiler.start();
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::scriptCompile()
{
  scriptCompile(
    currentDocumentGet()
  );
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::binDocPtrUpdateInternal(EsCompiledScriptDocument* binDocPtr)
{
  if(binDocPtr != m_docPtrs.m_compiledDocPtr)
  {
    ES_DEBUG_TRACE(esT("\tcompiledDocPtr set to binary script"));

    m_docPtrs.m_compiledDocPtr = binDocPtr;

    if(m_docPtrs.m_compiledDocPtr)
    {
      EsScriptIntf::Ptr bin = m_docPtrs.m_compiledDocPtr->contentGet();
      ES_ASSERT(bin);

      // Apply application-wide settings to opened document
      EsSconsoleParams& params = wxGetApp().settingsAccess();

      bin->includePathsSet(
        params.m_includes,
        false
      );

      bin->linkPathsSet(
        params.m_linkPaths,
        false
      );
    }
  }
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::docPtrsReset()
{
  m_docPtrs.m_docPtrType = DocPtrType::None;
  m_docPtrs.m_rawPtr = nullptr;
  m_docPtrs.m_compiledDocPtr = nullptr;

  ES_DEBUG_TRACE(esT("\tpointers reset"));
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::currentDocPtrUpdate()
{
  ES_DEBUG_TRACE(esT("EsSconsoleMain::currentDocPtrUpdate()"));

  EsDocumentIntf::Ptr doc = currentDocumentGet();
  if(!doc)
  {
    docPtrsReset();

    return;
  }

  if(doc->is(EsScriptDocument::classNameGetStatic()))
  {
    m_docPtrs.m_docPtrType = DocPtrType::Script;
    m_docPtrs.m_scriptDocPtr = ES_INTFPTR_TO_OBJECTPTR<EsScriptDocument>(doc);
    ES_ASSERT(m_docPtrs.m_scriptDocPtr);
    ES_DEBUG_TRACE(esT("\tdocptr set to script"));
  }
  else if(doc->is(EsTextDocument::classNameGetStatic()))
  {
    m_docPtrs.m_docPtrType = DocPtrType::Text;
    m_docPtrs.m_textDocPtr = ES_INTFPTR_TO_OBJECTPTR<EsTextDocument>(doc);
    ES_ASSERT(m_docPtrs.m_textDocPtr);

    ES_DEBUG_TRACE(esT("\tdocptr set to text"));
  }
  else if(doc->is(EsCompiledScriptDocument::classNameGetStatic()))
  {
    m_docPtrs.m_docPtrType = DocPtrType::Binary;
    m_docPtrs.m_rawPtr = nullptr;
    binDocPtrUpdateInternal(
      ES_INTFPTR_TO_OBJECTPTR<EsCompiledScriptDocument>(doc)
    );
  }
}
//--------------------------------------------------------------------------------

bool EsSconsoleMain::currentDocumentCanCompile() const
{
  return (DocPtrType::Script == m_docPtrs.m_docPtrType) &&
    (
      !m_docPtrs.m_compiledDocPtr ||
      !m_docPtrs.m_compiledDocPtr->isRunning()
    );
}
//--------------------------------------------------------------------------------

bool EsSconsoleMain::binaryScriptIsDebuggable() const
{
  return m_docPtrs.m_compiledDocPtr &&
    m_docPtrs.m_compiledDocPtr->isDebuggable();
}
//--------------------------------------------------------------------------------

bool EsSconsoleMain::binaryScriptCanRun() const
{
  if(m_compiling)
    return false;

  return m_docPtrs.m_compiledDocPtr &&
    !m_docPtrs.m_compiledDocPtr->isRunning();
}
//--------------------------------------------------------------------------------

bool EsSconsoleMain::binaryScriptCanStep() const
{
  if(m_compiling)
    return false;

  return binaryScriptCanRun() ||
    (
      binaryScriptIsRunning() &&
      m_docPtrs.m_compiledDocPtr->isDebuggerPaused()
      );
}
//--------------------------------------------------------------------------------

bool EsSconsoleMain::binaryScriptCanAbort() const
{
  if(m_compiling)
    return false;

  return binaryScriptIsRunning();
}
//--------------------------------------------------------------------------------

bool EsSconsoleMain::binaryScriptIsRunning() const
{
  return m_docPtrs.m_compiledDocPtr &&
    m_docPtrs.m_compiledDocPtr->isRunning();
}
//--------------------------------------------------------------------------------

bool EsSconsoleMain::binaryScriptIsDebugging() const
{
  return binaryScriptIsRunning() &&
    m_docPtrs.m_compiledDocPtr->isDebugging();
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::binaryScriptRun(const EsDocumentIntf::Ptr& doc, const EsString& entry, const EsVariant& args)
{
  EsCompiledScriptDocument* bindoc = ES_INTFPTR_TO_OBJECTPTR<EsCompiledScriptDocument>(doc);
  ES_ASSERT(bindoc);

  bindoc->run(
    entry,
    args
  );
}
//--------------------------------------------------------------------------------

void EsSconsoleMain::commonAppSettingsApply(bool doSave /*= false*/)
{
  ES_ASSERT(!m_compiling);
  ES_ASSERT(!binaryScriptIsRunning());

  // Assign settings to compiler instance and it (if any) compiled binary document instance
  EsSconsoleParams& params = wxGetApp().settingsAccess();
  EsScriptIntf::Ptr bin = m_compiler.binaryGet();
  bin->includePathsSet(
    params.m_includes,
    false
  );
  bin->linkPathsSet(
    params.m_linkPaths,
    false
  );

  EsCompiledScriptDocument* bindoc = binaryScriptGet();
  if(bindoc)
  {
    bin = bindoc->contentGet();
    ES_ASSERT(bin);

    bin->includePathsSet(
      params.m_includes,
      false
    );
    bin->linkPathsSet(
      params.m_linkPaths,
      false
    );
  }

  if(doSave)
    wxGetApp().settingsSave();
}
//--------------------------------------------------------------------------------

bool EsSconsoleMain::binaryScriptIsContinuouslyDebugging() const
{
  return binaryScriptIsDebugging() &&
    !m_docPtrs.m_compiledDocPtr->isDebuggerPaused();
}
//--------------------------------------------------------------------------------
