#include "ess_console_pch.h"
#pragma hdrstop

#include "EsCompiledScriptDocument.h"
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

EsCompiledScriptDocument::Runner::Runner(EsCompiledScriptDocument& owner) :
  EsThread(),
  m_owner(owner)
{}
//--------------------------------------------------------------------------------

long EsCompiledScriptDocument::Runner::worker()
{
  m_script->exec();

  if( m_entry.empty() )
    return 0;

  m_script->vm().callGlobalMethod(
    m_entry,
    m_params
  );

  return 0;
}
//--------------------------------------------------------------------------------

void EsCompiledScriptDocument::Runner::onEnterWorker()
{
  m_script = m_owner.contentGet();
  ES_ASSERT(m_script);

  const EsVariant::Array& payload = {
    m_owner.keyGet(),
    m_entry,
    m_params
  };

  EsEventDispatcher::eventPost(
    ES_EVTC_SCRIPT_THREAD,
    as_<ulong>(EsScriptRunnerEvt::Started),
    payload
  );
}
//--------------------------------------------------------------------------------

void EsCompiledScriptDocument::Runner::onExitWorker()
{
  const EsVariant::Array& payload = {
    m_owner.keyGet(),
    m_entry,
    m_params,
    errorLogGet()
  };

  EsEventDispatcher::eventPost(
    ES_EVTC_SCRIPT_THREAD,
    as_<ulong>(EsScriptRunnerEvt::Finished),
    payload
  );

  m_script.reset();
  m_entry.clear();
  m_params.setEmpty();
}
//--------------------------------------------------------------------------------

void EsCompiledScriptDocument::Runner::entryPointSetup(const EsString& entry /*= EsString::null()*/, const EsVariant& params /*= EsVariant::null() */)
{
  ES_ASSERT(EsThreadState::None == stateGet());

  m_entry = entry;
  m_params = params;
}
//--------------------------------------------------------------------------------

void EsCompiledScriptDocument::Runner::abortExecution()
{
  EsScriptIntf::Ptr tmp = m_script;
  if(tmp)
  {
    tmp->execAbort();
    stopAndWait();
  }
}
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

EsCompiledScriptDocument::EvtHandler::EvtHandler(EsCompiledScriptDocument& owner) :
  EsEventSubscriber(
    ES_EVTC_SCRIPT_THREAD ES_EVTC_AND
    ES_EVTC_SCRIPT_DEBUG_RSP ES_EVTC_AND
    ES_EVTC_APPLICATION,
    EsEventSubscriber::precedenceHigher
  ),
  m_owner(owner)
{}
//---------------------------------------------------------------------------

void EsCompiledScriptDocument::EvtHandler::notify(const EsEventIntf::Ptr& evt)
{
  const EsString& cat = evt->categoryGet();
  ulong id = evt->idGet();
  const EsVariant& payload = evt->payloadGet();

  if( ES_EVTC_SCRIPT_THREAD == cat )
  {
    switch( as_<EsScriptRunnerEvt>(id) )
    {
    case EsScriptRunnerEvt::Started:
      m_owner.onNonDebugStarted();
      break;
    case EsScriptRunnerEvt::Finished:
      m_owner.onFinished();
      break;
    default:
      // The rest does nothing
      break;
    }
  }
  else if( ES_EVTC_SCRIPT_DEBUG_RSP == cat )
  {
    switch( as_<EsScriptDebugEvt>(id) )
    {
    case EsScriptDebugEvt::Started:
      evt->payloadSet( m_owner.keyGet() ); //< Modify payload to provide uniform 'input' parameter
    case EsScriptDebugEvt::Continued:
      m_owner.onDebugStarted();
      break;
    case EsScriptDebugEvt::Paused:
      m_owner.m_debugPaused = true;
      break;
    case EsScriptDebugEvt::Aborted:
    case EsScriptDebugEvt::Finished:
      evt->payloadSet(m_owner.keyGet()); //< Modify payload to provide uniform 'input' parameter
      m_owner.onFinished();
      break;
    default:
      // The rest does nothing
      break;
    }
  }
  else if( ES_EVTC_APPLICATION == cat )
  {
    switch( as_<EsSconsoleEvt>(id) )
    {
    case EsSconsoleEvt::ScriptBrkChangeRequested:
      m_owner.onBrkChangeRequest(
        payload[0].asString(), //< Script Key
        payload[1].asULLong(), //< Script hash
        payload[2].asInt(),    //< Script line
        payload[3].asBool(),   //< set-reset
        payload[4].asBool()    //< Requested state
      );
      break;
    default:
      // The rest does nothing
      break;
    }
  }
}
//---------------------------------------------------------------------------
//--------------------------------------------------------------------------- 

// Reflection class info declaration
ES_DECL_CLASS_INFO_DERIVED_BEGIN(EsCompiledScriptDocument, EsDocument, NO_CLASS_DESCR)
  // Reflected interface services
  //
  ES_DECL_REFLECTED_INTF_METHOD_INFO(EsCompiledScriptDocument, EsDocumentIntf, sideloadRead, void_Call, NO_METHOD_DESCR)
  ES_DECL_REFLECTED_INTF_METHOD_INFO(EsCompiledScriptDocument, EsDocumentIntf, sideloadWrite, void_Call, NO_METHOD_DESCR)
  // Reflected services
  //
  ES_DECL_REFLECTED_METHOD_INFO_STD(EsCompiledScriptDocument, contentSet, void_Call_cr_EsBaseIntfPtr, NO_METHOD_DESCR)
  ES_DECL_REFLECTED_METHOD_INFO_STD(EsCompiledScriptDocument, contentGet, EsBaseIntfPtr_CallConst, NO_METHOD_DESCR)
  ES_DECL_REFLECTED_METHOD_INFO_STD(EsCompiledScriptDocument, breakpointsGet, EsVariant_CallConst, NO_METHOD_DESCR)
  // Reflected ctors
  //
  ES_DECL_REFLECTED_CTOR_INFO(EsCompiledScriptDocument, EsVariant_ClassCall_cr_EsVariant, NO_METHOD_DESCR)
ES_DECL_CLASS_INFO_END
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

EsCompiledScriptDocument::EsCompiledScriptDocument(const EsAssocContainerIntf::Ptr& regInfo) :
EsDocument(regInfo),
m_evtHandler(*this),
m_runner(*this),
m_pm(EsProgressMonitor::create(esT("all"))),
m_running(false),
m_debugging(false),
m_debugPaused(false),
m_aborting(false)
{
}
//--------------------------------------------------------------------------------

EsCompiledScriptDocument::~EsCompiledScriptDocument()
{
  abort();
}
//--------------------------------------------------------------------------------

EsVariant EsCompiledScriptDocument::NEW(cr_EsVariant regInfo)
{
  std::unique_ptr<EsCompiledScriptDocument> ptr = ES_MAKE_UNIQUE(
    EsCompiledScriptDocument,
    regInfo.asObject()
  );
  ES_ASSERT(ptr);

  return ptr.release()->asBaseIntfPtr();
}
//--------------------------------------------------------------------------------

void EsCompiledScriptDocument::emptyContentsInit(const EsVariant& ES_UNUSED(params))
{
  EsScriptIntf::Ptr script = EsScript::create();
  script->progressMonitorSet( 
    m_pm
  );
  contentSet(script);

  m_modified = false; //< Make sure new document is not modified
}
//--------------------------------------------------------------------------------

void EsCompiledScriptDocument::valueSet(cr_EsString name, cr_EsVariant val)
{
  EsDocument::valueSet(
    name,
    val
  );

  if( esT("content") == name )
  {
    if( val.isEmpty() )
    {
      emptyContentsInit(EsVariant::null());
      m_debug.scriptSet(nullptr);
    }
    else
    {
      EsScriptIntf::Ptr script = val.asExistingObject();
      ES_ASSERT(script);
      script->vm().hostGet()->propertySet(
        "progressMonitor",
        m_pm
      );

      if( script && script->hasSourceModulesInfo() )
        m_debug.scriptSet(script);
      else
        m_debug.scriptSet(nullptr);
    }

    m_modified = true;
  }
}
//--------------------------------------------------------------------------------

void EsCompiledScriptDocument::contentSet(cr_EsBaseIntfPtr content)
{
  valueSet(
    esT("content"),
    content
  );
}
//--------------------------------------------------------------------------------

EsBaseIntfPtr EsCompiledScriptDocument::contentGet() const
{
  return valueGet(esT("content")).asExistingObject();
}
//--------------------------------------------------------------------------------

bool EsCompiledScriptDocument::isEmpty() const ES_NOTHROW
{
  if( !EsDocument::isEmpty() && valueExists(esT("content")) )
  {
    const EsVariant& content = valueGet("content");
    return content.isEmpty();
  }

  return EsDocument::isEmpty();
}
//--------------------------------------------------------------------------------

bool EsCompiledScriptDocument::doRead(cr_EsVariant params)
{
  ES_DEBUG_TRACE(
    esT("EsCompiledScriptDocument::doRead(%s)"),
    EsVariant::dump(params)
  );

  // Interpret src as script file path
  EsPath fpath = EsPath::createFromFilePath(m_key.asString());
  const EsString& fpathStr = fpath.pathGet(); //< Absolutize path str

  if( !fpath.fileExists() )
    EsException::Throw(
      esT("ES Script compiled document file '%s' does not exist"),
      fpathStr
    );

  EsScriptIntf::Ptr script = contentGet();
  ES_ASSERT(script);

  bool retainDebug = true;
  EsString key;

  if( params.isVariantCollection() && params.countGet() > 1 ) //< If params is collection - the second member is assoc container by design convention
  {
    EsAssocContainerIntf::Ptr aparams = params[1].asObject();
    ES_ASSERT(aparams);

    retainDebug = aparams->valueGetDef(
      esVT("retainDebug"),
      true
    ).asBool();

    key = aparams->valueGetDef(
      esVT("key"),
      EsString::null()
    ).asString();
  }

  script->compiledBinaryLoad(
    fpathStr,
    retainDebug,
    key
  );

  m_key = fpathStr;

  return true;
}
//--------------------------------------------------------------------------------

void EsCompiledScriptDocument::doWrite(cr_EsVariant key, cr_EsVariant params, bool asCopy)
{
  // Interpret src as script file path
  const EsPath& fpath = EsPath::createFromFilePath(key.asString());
  const EsString& fpathStr = fpath.pathGet(); //< Absolutize path str

  EsScriptIntf::Ptr script = contentGet();
  ES_ASSERT(script);

  bool retainDebug = true;
  bool i18nSave = false;

  EsString codecKey;
  if( !params.isEmpty() )
  {
    EsAssocContainerIntf::Ptr aparams = params.asObject();
    ES_ASSERT(aparams);

    retainDebug = aparams->valueGetDef(
      esVT("retainDebug"),
      true
    ).asBool();

    i18nSave = aparams->valueGetDef(
      esVT("translatablesSave"),
      true
    ).asBool();

    codecKey = aparams->valueGetDef(
      esVT("key"),
      EsString::null()
    ).asString();
  }

  EsBinBuffer bb = script->compiledBinaryGet(retainDebug);

  if( !codecKey.empty() )
    bb = EsUtilities::bToE(
      bb, 
      codecKey
    );

  // Ensure path to the output file exists
  const EsPath& opath = EsPath::createFromPath(
    fpath.pathGet(
      as_<ulong>(EsPathFlag::Default)|
      as_<ulong>(EsPathFlag::ExcludeFile)
    )
  );

  if( !opath.exists() )
    opath.pathCreate();

  EsFile f(
    fpathStr,
    as_<ulong>(EsFileFlag::Write)
  );

  if( f.open() )
  {
    f.writeAllAsBinBuffer(bb);
    f.close();

    if( i18nSave )
      translatablesSave(fpathStr);
  }
}
//--------------------------------------------------------------------------------

EsVariant EsCompiledScriptDocument::breakpointsGet() const
{
  return m_debug.breakpointsGet();
}
//--------------------------------------------------------------------------------

void EsCompiledScriptDocument::sideloadRead()
{
  // Try to find and read sideload data
  const EsString& sideloadPathStr = m_key.asString() + esT(".sl");

  if( !EsPath::fileExists(sideloadPathStr, EsString::null()) )
    return;

  EsStreamIntf::Ptr stream = EsStreamXml::create(
    as_<ulong>(EsStreamFlag::File) |
    as_<ulong>(EsStreamFlag::Read),
    sideloadPathStr
  );
  ES_ASSERT(stream);

  valueSet(
    esT("breakpoints"),
    stream->valueRead(
      esT("breakpoints"),
      EsVariant::null()
    )
  );
}
//--------------------------------------------------------------------------------

void EsCompiledScriptDocument::sideloadWrite()
{
  sideloadFileDelete();

  if( !valueExists(esT("breakpoints")) )
    return;

  // Try to write sideload data
  const EsString& sideloadPathStr = m_key.asString() + esT(".sl");
  EsStreamIntf::Ptr stream = EsStreamXml::create(
    as_<ulong>(EsStreamFlag::File) |
    as_<ulong>(EsStreamFlag::Write),
    sideloadPathStr
  );
  ES_ASSERT(stream);

  stream->valueWrite(
    esT("breakpoints"),
    valueGet(esT("breakpoints"))
  );
}
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

void EsCompiledScriptDocument::run()
{
  m_runner.entryPointSetup();

  m_runner.start();
}
//--------------------------------------------------------------------------------

void EsCompiledScriptDocument::run(const EsString& entry, const EsVariant& params)
{
  m_runner.entryPointSetup(
    entry,
    params
  );

  m_runner.start();
}
//--------------------------------------------------------------------------------

void EsCompiledScriptDocument::debugRun()
{
  ES_ASSERT(isDebuggable());
  ES_ASSERT(EsThreadState::None == m_runner.stateGet());

  m_debug.run();
}
//--------------------------------------------------------------------------------

void EsCompiledScriptDocument::debugStep()
{
  ES_ASSERT(isDebuggable());
  ES_ASSERT(EsThreadState::None == m_runner.stateGet());

  m_debug.step();
}
//--------------------------------------------------------------------------------

void EsCompiledScriptDocument::debugPause()
{
  ES_ASSERT(isDebuggable());
  ES_ASSERT(EsThreadState::None == m_runner.stateGet());
  ES_ASSERT(m_running);

  m_debug.pause();
}
//--------------------------------------------------------------------------------

void EsCompiledScriptDocument::abort()
{
  if( m_running && !m_aborting )
  {
    m_aborting = true;
    if( EsThreadState::None == m_runner.stateGet() )
      m_debug.abortExecution();
    else
      m_runner.abortExecution();
  }
}
//--------------------------------------------------------------------------------

void EsCompiledScriptDocument::translatablesSave(const EsString& dest)
{
  EsPath path = EsPath::createFromFilePath(dest);
  path.fileExtSet(esT("pot"));

  EsScriptIntf::Ptr script = contentGet();
  ES_ASSERT(script);

  const EsString::Array& translatables = script->translatablesGet();

  EsFile f(
    path.pathGet(),
    as_<ulong>(EsFileFlag::Write) |
    as_<ulong>(EsFileFlag::Text)
  );

  if( f.open() )
  {
    f.rawWrite("\xEF\xBB\xBF", 3);

    EsString line = EsString::format(
      esT("# Translatable script file generated automatically\n")
      esT("# during compilation of '%s' binary file.\n")
      esT("#\n")
      esT("msgid \"\"\n")
      esT("msgstr \"\"\n")
      esT("\"POT-Creation-Date: %s\\n\"\n")
      esT("\"PO-Revision-Date: YEAR-MO-DA HO:MI+ZONE\\n\"\n")
      esT("\"Last-Translator: FULL NAME <EMAIL@ADDRESS>\\n\"\n")
      esT("\"Language-Team: LANGUAGE <LL@li.org>\\n\"\n")
      esT("\"Language: \\n\"\n")
      esT("\"MIME-Version: 1.0\\n\"\n")
      esT("\"Content-Type: text/plain; charset=CHARSET\\n\"\n")
      esT("\"Content-Transfer-Encoding: 8bit\\n\"\n")
      esT("\n"),
      dest,
      EsDateTime::now().asString()
    );
    f.stringWrite(line);

    for( auto const& msg : translatables )
    {
      line = EsString::format(
        esT("msgid \"%s\"\n")
        esT("msgstr \"\"\n")
        esT("\n"),
        EsString::toString(msg)
      );

      f.stringWrite(line);
    }

    f.close();
  }
}
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

void EsCompiledScriptDocument::onNonDebugStarted()
{
  m_running = true;
  m_debugging = false;
  m_debugPaused = false;
  m_aborting = false;
}
//--------------------------------------------------------------------------------

void EsCompiledScriptDocument::onFinished()
{
  m_running = false;
  m_debugging = false;
  m_debugPaused = false;
  m_aborting = false;
}
//--------------------------------------------------------------------------------

void EsCompiledScriptDocument::onDebugStarted()
{
  m_running = true;
  m_debugging = true;
  m_debugPaused = false;
  m_aborting = false;
}
//--------------------------------------------------------------------------------

void EsCompiledScriptDocument::onBrkChangeRequest(const EsString& key, EsString::HashT hash, int line, bool set, bool state)
{
  if( !isDebuggable() )
    return;

  if( set )
    m_debug.breakpointSet(
      key, 
      line, 
      state
    );
  else
    m_debug.breakpointDelete(
      key, 
      line
    );
}
//--------------------------------------------------------------------------------

bool EsCompiledScriptDocument::isSideloadName(const EsString& name) const
{
  if( esT("breakpoints") == name )
    return true;

  return false;
}
//--------------------------------------------------------------------------------

bool EsCompiledScriptDocument::isDebuggable() const ES_NOTHROW
{
  EsScriptIntf::Ptr script = contentGet();

  return script && script->hasSourceModulesInfo() && m_debug.isScriptAttached();
}
//---------------------------------------------------------------------------
