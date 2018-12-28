#ifndef _es_console_script_output_view_h_
#define _es_console_script_output_view_h_

/// @file EsSconsoleScriptOutput.h 
/// Script execution messages view pane class
/// 

class EsSconsoleScriptOutput : public EsSconsoleOutputBase
{
private:
  class EvtHandler : public EsEventSubscriber
  {
  public:
    EvtHandler(EsSconsoleScriptOutput& owner);

    ES_DECL_INTF_METHOD(void, notify)(const EsEventIntf::Ptr& evt);

  private:
    EsSconsoleScriptOutput& m_owner;

    EvtHandler() ES_REMOVEDECL;
    EvtHandler(const EvtHandler&) ES_REMOVEDECL;
    EvtHandler& operator=(const EvtHandler&) ES_REMOVEDECL;
  };
  friend class EvtHandler;

public:
  EsSconsoleScriptOutput(wxWindow* parent);

protected:
  // ES event handlers
  void onStarted(const EsString& input, const EsString& entry, const EsVariant& params, bool debugMode);
  void onAborted(const EsString& input);
  void onComplete(const EsString& input, const EsString::Array& errors);
  void onLog(const EsString& msg);

private:
  EvtHandler m_handler;
};

#endif // _es_console_script_output_view_h_
