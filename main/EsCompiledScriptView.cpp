#include "ess_console_pch.h"
#pragma hdrstop

#include "EsCompiledScriptView.h"
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

EsCompiledScriptView::EvtHandler::EvtHandler(EsCompiledScriptView& owner) ES_NOTHROW :
EsEventSubscriber(
  ES_EVTC_I18N
),
m_owner(owner)
{}
//--------------------------------------------------------------------------------

void EsCompiledScriptView::EvtHandler::notify(const EsEventIntf::Ptr& evt)
{
  ES_ASSERT(evt);

  const EsString& cat = evt->categoryGet();
  ulong id = evt->idGet();

  if(ES_EVTC_I18N == cat && EsEvtI18n::LocaleChanged == as_<EsEvtI18n>(id))
  {
    m_owner.onI18nLocaleChanged(
      evt->payloadGet().asString()
    );
  }
}
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

EsCompiledScriptView::EsCompiledScriptView(wxWindow* parent, wxWindowID id /*= wxID_ANY*/):
wxPanel(
  parent, 
  id
),
m_handler(*this),
m_contents(nullptr),
m_outBox(nullptr),
m_out(nullptr),
m_progress(nullptr)
{
  m_contents = new wxBoxSizer(wxVERTICAL);
  ES_ASSERT(m_contents);

  m_out = new EsSconsoleScriptOutput(this);
  ES_ASSERT(m_out);

  m_progress = new EsProgressMonitorView(this);
  ES_ASSERT(m_progress);

  m_progress->onReadySet(
    [this](EsProgressMonitorView& sender) {
      onProgressReady(sender);
    }
  );

  m_progress->onActivitySet(
    [this](EsProgressMonitorView& sender) {
      onProgressActivity(sender);
    }
  );

  m_outBox = new wxStaticBoxSizer(
    wxVERTICAL,
    this
  );
  ES_ASSERT(m_outBox);

  wxToolBar* tb = m_out->toolBarGet(
    m_outBox->GetStaticBox()
  );
  ES_ASSERT(tb);

  m_outBox->Add(
    tb,
    wxSizerFlags().
    Expand()
  );

  m_outBox->Add(
    m_out,
    wxSizerFlags(1).
    Border().
    Expand()
  );
  m_outBox->Layout();

  m_contents->Add(
    m_outBox,
    wxSizerFlags(1).Border().Expand()
  );

  m_contents->Add(
    m_progress,
    wxSizerFlags().Border().Expand()
  );

  onI18nLocaleChanged(
    EsStringI18n::instanceGet().currentLocaleGet()
  );

  SetSizer(m_contents);
}
//--------------------------------------------------------------------------------

void EsCompiledScriptView::onI18nLocaleChanged(const EsString& ES_UNUSED(loc))
{
  m_outBox->GetStaticBox()->SetLabel(
    _("Script output console:")
  );
}
//--------------------------------------------------------------------------------

void EsCompiledScriptView::progressMonitorAssign(const EsProgressMonitorIntf::Ptr& pm)
{
  ES_ASSERT(m_progress);
  m_progress->progressMonitorSet(pm);
}
//--------------------------------------------------------------------------------

void EsCompiledScriptView::onProgressReady(EsProgressMonitorView& sender)
{
  m_contents->Show(
    m_progress,
    false
  );
  m_contents->Layout();
}
//--------------------------------------------------------------------------------

void EsCompiledScriptView::onProgressActivity(EsProgressMonitorView& sender)
{
  if( !m_contents->IsShown(m_progress) )
    m_contents->Show(
      m_progress
    );
  m_contents->Layout();
}
//--------------------------------------------------------------------------------
