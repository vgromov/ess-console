#ifndef _es_script_editor_view_h_
#define _es_script_editor_view_h_

class EsScriptEditorView : public EsTextEditorViewBase
{
public:
  enum {
    reparseDelay                = 2000,  //< Reparse changed script document after specified period of ms
    autoCompletionShowAfterCnt  = 2,     //< Show autocompletion after that number of word characters typed
    autoCompTmo                 = 500,
    // Autocompletion category IDs
    //
    acIdKeyword                 = 0,
    acIdConst,
    acIdAttr,
    acIdVarGlobal,
    acIdEnum,
    acIdEnumItem,
    acIdFunc,
    acIdVarsvc,
    acIdClass,
    acIdClassVar,
    acIdClassFld,
    acIdClassProp,
    acIdClassMemberFunc,
    acIdClassFunc,
    // Special value, must be the last
    acIdsCnt
  };

private:
  // ES Event subscriber
  class EvtHandler : public EsEventSubscriber
  {
  public:
    EvtHandler(EsScriptEditorView& owner) ES_NOTHROW;

    ES_DECL_INTF_METHOD(void, notify)(const EsEventIntf::Ptr& evt);

  protected:
    EsScriptEditorView& m_owner;
  };
  friend class EvtHandler;

protected:
  EsScriptEditorView(wxWindow *parent, wxWindowID id, long style);

public:
  static EsScriptEditorView* create(wxWindow *parent, wxWindowID id = wxID_ANY, long style = 0);

  virtual void textSet(const EsString& text) ES_OVERRIDE;

  /// Position selection API
  void currentExecutionLineSet(int line, bool set);

protected:
  // Base class overrides
  //
  virtual void doCustomCtxMenuInit() ES_OVERRIDE;
  virtual void doCtxMenuStringsUpdate(wxMenu* pmnu) ES_OVERRIDE;
  virtual void doCustomCtxMenuEvtHandlersSet(wxEvtHandler* subj, bool set) ES_OVERRIDE;
  virtual void stylesSetCommon() ES_OVERRIDE;
  virtual void autocompletionInit() ES_OVERRIDE;
  virtual void onEditorLinesChanged() ES_OVERRIDE;
  virtual void onI18nLocaleChanged(const EsString& loc) ES_OVERRIDE;

  // Append autocompletion items to the aggregator list
  //
  static void autocompletionItemsAppend(
    EsString::Array& dest,
    const EsString::Array& src,
    int id
  );
  void autocompletionItemsAppend(
    EsString::Array& dest,
    const EsScriptParser::Node::PtrArrayT& parserNodes,
    const EsString& filter,
    int id
  );

  // Prepare autocompletion list
  wxString autocompletionListPrepare(int curPos, const EsString& filter, wxString subj, wxString op);

  // Show autocompletion list either forcibly, or after N chars entered
  void autocompletionShow(bool force = false);

  // Internal brk. manipulation helpers. Do not call them directly in response to 
  // margin clicks, these are being called internally from EsScriptDebug response handlers
  // 
  void breakpointDelete(int line);
  void breakpointSet(int line, bool state, bool valid);

  // Local context characterization helpers
  //
  void operatorAndSubjGetLeftOfPos(int curPos, wxString& subj, wxString& op, bool searchSubj = true);
  
  // WX handlers
  virtual void onEditorContentChange(wxStyledTextEvent& evt) ES_OVERRIDE;
  virtual void onStcUiUpdate(wxStyledTextEvent& evt) ES_OVERRIDE;
  virtual void onCmdUiUpdate(wxUpdateUIEvent& evt) ES_OVERRIDE;
  virtual void onMarginClick(wxStyledTextEvent& evt) ES_OVERRIDE;
  virtual void onAutoCompleting(wxStyledTextEvent& evt) ES_OVERRIDE;
  void onTimer(wxTimerEvent & evt);
  void onFileOpenAtCursor(wxCommandEvent& evt);
  void onFileLocationOpenAtCursor(wxCommandEvent& evt);
  void onLineCommentToggle(wxCommandEvent& evt);
  void onBlockCommentToggle(wxCommandEvent& evt);
  void onCodeInsight(wxCommandEvent& evt);

  // ES handlers
  void onCompiledScriptChanged(const EsVariant& compiledScript);
  void onCompiledScriptClosed();
  void onBreakpointChanged(const EsScriptIntf::Ptr& script, const EsVariant& oldState, const EsVariant& newState);
  void onDebuggerPaused(ulong line, bool isBreakpoint);
  void onExecContinued();
  void onExecFinished();

  // Internal helpers
  void breakpointMarkersClean();
  void breakableLineMarkersClear();
  void allBrkMarkersClean();
  void breakpointsInvalidSet();
  int scriptCtxAtPosGet(int pos);

private:
  EvtHandler m_handler;
  wxTimer m_tmrParser;
  wxTimer m_tmrAutoComplete;
  EsScriptParser m_ctxParser;
  wxString m_acList;
  const EsScriptParser::Node* m_topCtx;
  int m_curlinePrev;
  int m_ctxAtPos;
  int m_parserStop;
  bool m_ctxParsed;
  
private:
  EsScriptEditorView() ES_REMOVEDECL;
  EsScriptEditorView(const EsScriptEditorView&) ES_REMOVEDECL;
  EsScriptEditorView& operator=(const EsScriptEditorView&) ES_REMOVEDECL;
};

//---------------------------------------------------------------------------
#endif // _es_script_editor_view_h_
