#include "ess_console_pch.h"
#pragma hdrstop

#include "EsSconsoleScriptOutput.h"
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

EsSconsoleScriptOutput::EvtHandler::EvtHandler(EsSconsoleScriptOutput& owner) :
EsEventSubscriber(
  ES_EVTC_SCRIPT_THREAD EVTC_AND
  ES_EVTC_SCRIPT_DEBUG_RSP
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
}
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

EsSconsoleScriptOutput::EsSconsoleScriptOutput(wxWindow* parent) :
  EsSconsoleOutputBase(parent),
  m_handler(*this)
{
  styleInit(wxSTC_LEX_ERRORLIST);
}
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

void EsSconsoleScriptOutput::onStarted(const EsString& input, const EsString& entry, const EsVariant& params, bool debugMode)
{
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
      _("> Running %s'%s' in '%s' mode..."),
      entry.c_str(),
      input.c_str(),
      debugMode ? esT("DEBUG") : esT("NORMAL")
    )
  );
}
//--------------------------------------------------------------------------------

void EsSconsoleScriptOutput::onAborted(const EsString& input)
{
  textLineAppend(
    wxString::Format(
      _("> Execution of '%s' was aborted by user"),
      input.c_str()
    )
  );
}
//--------------------------------------------------------------------------------

void EsSconsoleScriptOutput::onComplete(const EsString& input, const EsString::Array& errors)
{
  textLineAppend(
    wxString::Format(
      _("> Execution of '%s' is complete"),
      input.c_str()
    )
  );

  if(errors.empty())
    return;

  textLineAppend(
    _("Execution error(s) occurred:")
  );

  for(auto const& err : errors)
    textLineAppend(
      err.c_str()
    );
}
//--------------------------------------------------------------------------------

void EsSconsoleScriptOutput::onLog(const EsString& msg)
{
  textLineAppend( msg.c_str() );
}
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
