#include "ess_console_pch.h"
#pragma hdrstop

#include <wx/caret.h>
#include "EsSconsoleCompilerOutput.h"
//--------------------------------------------------------------------------------

EsSconsoleCompilerOutput::EvtHandler::EvtHandler(EsSconsoleCompilerOutput& owner) :
EsEventSubscriber(
  ES_EVTC_SCRIPT ES_EVTC_AND
  ES_EVTC_COMPILER_THREAD
),
m_owner(owner),
m_handleScriptEvtc(false)
{
}
//--------------------------------------------------------------------------------

void EsSconsoleCompilerOutput::EvtHandler::notify(const EsEventIntf::Ptr& evt)
{
  const EsString& cat = evt->categoryGet();
  ulong id = evt->idGet();
  const EsVariant& payload = evt->payloadGet();

  if(m_handleScriptEvtc && ES_EVTC_SCRIPT == cat)
  {
    switch(id)
    {
    case EsScript::evtCompilerInfo:
      m_owner.onCompilerEvent(
        payload.isEmpty() ? 
          EsString::null() :
          payload.asString()
      );
      break;
    case EsScript::evtError:
      m_owner.onCompilerError(
        payload[0].asString(),
        payload[1].asObject()
      );
      break;
    }
  }
  else if(ES_EVTC_COMPILER_THREAD == cat)
  {
    switch(as_<EsScriptCompilerEvt>(id))
    {
    case EsScriptCompilerEvt::Started:
      m_handleScriptEvtc = true;
      m_owner.onCompilationStart(
        payload.asString()
      );
      break;
    case EsScriptCompilerEvt::Aborted:
      m_handleScriptEvtc = false;
      m_owner.onCompilationAborted(
        payload.asString()
      );
      break;
    case EsScriptCompilerEvt::Finished:
      m_handleScriptEvtc = false;
      m_owner.onCompilationEnd(
        payload[0].asString(),                      //< Compilation of specific input
        EsTimeSpan::fromVariant( payload[1] ),      //< Compilation time span
        payload[2].isStringCollection() ?
          payload[2].doInterpretAsStringCollection() :   //< Compilation errors
          EsString::nullArray()
      );
      break;
    }
  }
}
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

EsSconsoleCompilerOutput::EsSconsoleCompilerOutput(wxWindow* parent) :
EsSconsoleOutputBase(
  parent
),
m_handler(*this)
{
  styleInit(wxSTC_LEX_ERRORLIST);
}
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

void EsSconsoleCompilerOutput::onCompilerEvent(const EsString& input)
{
  if(input.empty())
    return;

  textLineAppend(
    wxString::Format(
      esT("> %s"),
      input.c_str()
    )
  );
}
//--------------------------------------------------------------------------------

void EsSconsoleCompilerOutput::onCompilerError(const EsString& msg, const EsScriptDebugInfoIntf::Ptr& ES_UNUSED(dbg))
{
  textLineAppend(
    wxString::Format(
      esT("Error %s"),
      msg.c_str()
    )
  );
}
//--------------------------------------------------------------------------------

void EsSconsoleCompilerOutput::onCompilationStart(const EsString& input)
{
  textClearAll();

  textLineAppend(
    wxString::Format(
      _("Compiling '%s'...").as<wxString>(),
      input.as<wxString>()
    )
  );
}
//--------------------------------------------------------------------------------

void EsSconsoleCompilerOutput::onCompilationAborted(const EsString& input)
{
  textLineAppend(
    wxString::Format(
      _("Compilation of '%s' was interrupted by user").as<wxString>(),
      input.as<wxString>()
    )
  );
}
//--------------------------------------------------------------------------------

void EsSconsoleCompilerOutput::onCompilationEnd(const EsString& input, const EsTimeSpan& span, const EsString::Array& elog)
{
  if(elog.empty())
  {
    wxString elapsed;
    if(span.get_allWeeks() > 0)
      elapsed = span.asString(_("%Ew %Dd %H:%M:%S.%l")).as<wxString>();
    else if(span.get_allDays() > 0)
      elapsed = span.asString(_("%Dd %H:%M:%S.%l")).as<wxString>();
    else if(span.get_allHours() > 0)
      elapsed = span.asString(_("%H:%M:%S.%l")).as<wxString>();
    else if(span.get_allMinutes() > 0)
      elapsed = span.asString(_("%M:%S.%l")).as<wxString>();
    else
      elapsed = span.asString(_("%S.%l s")).as<wxString>();

    textLineAppend(
      _("Compilation complete in: ").as<wxString>() + elapsed
    );
  }
  else
  {
    textLineAppend(
      _("Error(s) occurred during compilation:").as<wxString>()
    );

    textLineAppend(
      EsString::fromStringArray(
        elog,
        esT("\n\r")
      ).as<wxString>()
    );
  }
}
//--------------------------------------------------------------------------------
