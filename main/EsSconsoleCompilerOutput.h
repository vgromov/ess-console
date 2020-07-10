#ifndef _es_console_compiler_output_h_
#define _es_console_compiler_output_h_

/// @file EsSconsoleCompilerOutput.h 
/// Compiler output messages view pane class
/// 

class EsSconsoleCompilerOutput : public EsSconsoleOutputBase
{
private:
  class EvtHandler : public EsEventSubscriber
  {
  public:
    EvtHandler(EsSconsoleCompilerOutput& owner);

    ES_DECL_INTF_METHOD(void, notify)(const EsEventIntf::Ptr& evt);

  private:
    EsSconsoleCompilerOutput& m_owner;
    bool m_handleScriptEvtc;

    EvtHandler() ES_REMOVEDECL;
    EvtHandler(const EvtHandler&) ES_REMOVEDECL;
    EvtHandler& operator=(const EvtHandler&) ES_REMOVEDECL;
  };
  friend class EvtHandler;

public:
  EsSconsoleCompilerOutput(wxWindow* parent);

protected:
  // ES event handlers
  void onCompilerEvent(const EsString& input);
  void onCompilerError(const EsString& msg, const EsScriptDebugInfoIntf::Ptr& dbg);
  void onCompilationStart(const EsString& input);
  void onCompilationAborted(const EsString& input);
  void onCompilationEnd(const EsString& input, const EsTimeSpan& span, const EsString::Array& elog);

private:
  EvtHandler m_handler;
};

#endif // _es_console_compiler_output_h_
