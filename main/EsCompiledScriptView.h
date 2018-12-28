#ifndef _es_compiled_script_view_h_
#define _es_compiled_script_view_h_

/// @file EsCompiledScriptView.h
/// Compiled script binary view form ess console MDI workspace
///

class EsCompiledScriptView : public wxPanel
{
public:
  enum {
    markerBrkLine = EsTextEditorViewBase::markerIdMax,
    markerBrk,
    markerBrkInactive,
    markerBrkInvalid,
    markerBrkCurrent, //< Current line, at which execution is stopped
    
    // Special value - must be the last in IDs items list
    markerIdMax,

    // BRK marker masks
    markerBrkLineMask = (1 << markerBrkLine),
    markerBrkMask = (1 << markerBrk),
    markerBrkInactiveMask = (1 << markerBrkInactive),
    markerBrkInvalidMask = (1 << markerBrkInvalid),
    markerBrkCurrentMask = (1 << markerBrkCurrent),
    markerBrkPointMask = (markerBrkMask|markerBrkInvalidMask|markerBrkInactiveMask),
    markerBrkMaskAll =
      markerBrkLineMask |
      markerBrkPointMask|
      markerBrkCurrentMask
  };

private:
  // ES Event subscriber
  class EvtHandler : public EsEventSubscriber
  {
  public:
    EvtHandler(EsCompiledScriptView& owner) ES_NOTHROW;

    ES_DECL_INTF_METHOD(void, notify)(const EsEventIntf::Ptr& evt);

  protected:
    EsCompiledScriptView& m_owner;
  };
  friend class EvtHandler;

public:
  EsCompiledScriptView(wxWindow* parent, wxWindowID id = wxID_ANY);

  void progressMonitorAssign(const EsProgressMonitorIntf::Ptr& pm);

protected:
  void onI18nLocaleChanged(const EsString& loc);
  void onProgressReady(EsProgressMonitorView& sender);
  void onProgressActivity(EsProgressMonitorView& sender);

protected:
  EvtHandler m_handler;
  wxBoxSizer* m_contents;
  wxStaticBoxSizer* m_outBox;
  EsSconsoleScriptOutput* m_out;
  EsProgressMonitorView* m_progress;

private:
  EsCompiledScriptView() ES_REMOVEDECL;
  EsCompiledScriptView(const EsCompiledScriptView&) ES_REMOVEDECL;
  EsCompiledScriptView& operator=(const EsCompiledScriptView&) ES_REMOVEDECL;
};

#endif // _es_compiled_script_view_h_
