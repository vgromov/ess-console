#include "ess_console_pch.h"
#pragma hdrstop

#include "EsSconsoleScriptOutput.h"
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

EsSconsoleScriptOutput::EvtHandler::EvtHandler(EsSconsoleScriptOutput& owner) :
EsEventSubscriber(
  ES_EVTC_SCRIPT_THREAD ES_EVTC_AND
  ES_EVTC_SCRIPT_DEBUG_RSP ES_EVTC_AND
  ES_EVTC_SCRIPT
),
m_owner(owner)
{
}
//--------------------------------------------------------------------------------

void EsSconsoleScriptOutput::EvtHandler::notify(const EsEventIntf::Ptr& evt)
{
  const EsString& cat = evt->categoryGet();
  ulong id = evt->idGet();
  const EsVariant& payload = evt->payloadGet();

  if( ES_EVTC_SCRIPT_THREAD == cat )
  {
    switch( as_<EsScriptRunnerEvt>(id) )
    {
    case EsScriptRunnerEvt::Started:
      m_owner.onStarted(
        payload[0].asString(),
        payload[1].asString(),
        payload[2],
        false
      );
      break;
    case EsScriptRunnerEvt::Finished:
      m_owner.onComplete(
        payload[0].asString(),
        payload[3].asStringCollection()
      );
      break;
    }
  }
  else if( ES_EVTC_SCRIPT_DEBUG_RSP == cat )
  {
    switch( as_<EsScriptDebugEvt>(id) )
    {
    case EsScriptDebugEvt::Started:
      m_owner.onStarted(
        payload.asString(),
        EsString::null(),
        EsVariant::null(),
        true
      );
      break;
    case EsScriptDebugEvt::Aborted:
      m_owner.onAborted( 
        payload.asString() 
      );
      break;
    case EsScriptDebugEvt::Finished:
      m_owner.onComplete( 
        payload.asString(),
        EsString::nullArray()
      );
      break;
    case EsScriptDebugEvt::Log:
      m_owner.onLog( 
        payload.asString() 
      );
      break;
    }
  }
  else if( 
    m_owner.m_executing && //< Do not log out-of-execution errors (code insight, for instance)
    ES_EVTC_SCRIPT == cat && 
    EsScript::evtError == id
  )
  {
    m_owner.onLog( 
      EsString::format(
        esT("Error %s"),
        payload[0].asString()
      )
    );
  }
}
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

EsSconsoleScriptOutput::EsSconsoleScriptOutput(wxWindow* parent) :
EsSconsoleOutputBase(parent),
m_handler(*this),
m_executing(false)
{
  styleInit(wxSTC_LEX_ERRORLIST);
}
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

void EsSconsoleScriptOutput::onStarted(const EsString& input, const EsString& entry, const EsVariant& params, bool debugMode)
{
  m_executing = true;

  textClearAll();

  wxString entryStr;
  if( !entry.empty() )
  {
    entryStr = entry.c_str();
    if( params.isEmpty() )
      entryStr += esT("()");
    else
    {
      entryStr += esT("( ");
      entryStr += params.asString().c_str();
      entryStr += esT(" )");
    }
  }

  textLineAppend(
    wxString::Format(
      _("> Running %s'%s' in '%s' mode...").as<wxString>(),
      entry.as<wxString>(),
      input.as<wxString>(),
      debugMode ? esT("DEBUG") : esT("NORMAL")
    )
  );
}
//--------------------------------------------------------------------------------

void EsSconsoleScriptOutput::onAborted(const EsString& input)
{
  m_executing = false;

  textLineAppend(
    wxString::Format(
      _("> Execution of '%s' was aborted by user").as<wxString>(),
      input.as<wxString>()
    )
  );
}
//--------------------------------------------------------------------------------

void EsSconsoleScriptOutput::onComplete(const EsString& input, const EsString::Array& errors)
{
  m_executing = false;

  textLineAppend(
    wxString::Format(
      _("> Execution of '%s' is complete").as<wxString>(),
      input.as<wxString>()
    )
  );

  if(errors.empty())
    return;

  textLineAppend(
    _("Execution error(s) occurred:").as<wxString>()
  );

  for(auto const& err : errors)
    textLineAppend(
      err.as<wxString>()
    );
}
//--------------------------------------------------------------------------------

void EsSconsoleScriptOutput::onLog(const EsString& msg)
{
  textLineAppend( msg.as<wxString>());
}
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
