#ifndef _es_compiled_script_document_h_
#define _es_compiled_script_document_h_

class ES_INTF_IMPL_DERIVED(EsCompiledScriptDocument, EsDocument)

private:
  class Runner : public EsThread
  {
  public:
    Runner(EsCompiledScriptDocument& owner);

    void entryPointSetup(const EsString& entry = EsString::null(), const EsVariant& params = EsVariant::null());
    void abortExecution();

  protected:
    virtual long worker();
    virtual void onEnterWorker();
    virtual void onExitWorker();

  protected:
    EsCompiledScriptDocument& m_owner;
    EsScriptIntf::Ptr m_script;
    EsString m_entry;
    EsVariant m_params;
  };
  friend class Runner;

  class EvtHandler : public EsEventSubscriber
  {
  public:
    EvtHandler(EsCompiledScriptDocument& owner);

    virtual void notify(const EsEventIntf::Ptr& evt);

  protected:
    EsCompiledScriptDocument& m_owner;
  };
  friend class Subuscriber;

protected:
  EsCompiledScriptDocument(const EsAssocContainerIntf::Ptr& regInfo);

public:
  ES_DECL_REFLECTED_CLASS(EsCompiledScriptDocument, EsDocument)
  virtual ~EsCompiledScriptDocument();

  // EsBaseIntf implementation
  ES_DECL_INTF_METHOD(EsString, typeNameGet)() const ES_NOTHROW { return classNameGetStatic(); }

  /// Reflected  services
  ///

  /// Document constructor always get registry parameters as an argument,
  /// even if these are not used in specific implementation
  ES_DECL_REFLECTED_CLASS_CTOR1(EsVariant, cr_EsVariant);

  /// Script document-specific reflected services
  ///

  /// Content
  ES_DECL_REFLECTED_METHOD1(void, contentSet, cr_EsBaseIntfPtr);
  ES_DECL_REFLECTED_CONST_METHOD0(EsBaseIntfPtr, contentGet);

  /// Bookmark data
  ES_DECL_REFLECTED_CONST_METHOD0(EsVariant, breakpointsGet);

  /// EsDocumentIntf overrides
  ///
  ES_DECL_INTF_METHOD(bool, isEmpty)() const ES_NOTHROW;
  ES_DECL_INTF_METHOD(void, valueSet)(cr_EsString name, cr_EsVariant val);

  /// The rest of EsDocumentIntf reflected implementation
  ///
  ES_DECL_REFLECTED_INTF_METHOD0(void, sideloadRead);
  ES_DECL_REFLECTED_INTF_METHOD0(void, sideloadWrite);

  /// Document content initialization
  ES_DECL_INTF_METHOD(void, emptyContentsInit)(const EsVariant& params) ES_OVERRIDE;

  /// Non-reflected services
  ///
  virtual bool doRead(cr_EsVariant params) ES_OVERRIDE;
  virtual void doWrite(cr_EsVariant key, cr_EsVariant params, bool asCopy) ES_OVERRIDE;

  /// Access progress monitor instance
  const EsProgressMonitorIntf::Ptr& progressMonitorGet() const ES_NOTHROW { return m_pm; }

  /// Script execution services
  ///

  /// Return true if script execution is active, false otherwise
  bool isRunning() const ES_NOTHROW { return m_running; }

  /// Return true if script is executed under debugger, false otherwise
  bool isDebugging() const ES_NOTHROW { return m_debugging; }

  /// Return true is we're debugging and are in paused state
  bool isDebuggerPaused() const ES_NOTHROW { return m_debugging && m_debugPaused; }

  /// Return true if execution is being aborted
  bool isAborting() const ES_NOTHROW { return m_aborting; }

  /// Return true if script may be debugged (have source module info and debugger is set-up)
  bool isDebuggable() const ES_NOTHROW;

  /// Execute script main entry point
  void run();

  /// Execute specific script entry point, with parameters. 
  /// NB! A main script entry point is executed before calling specified entry, because the former may
  /// contain initialization code for global variables, which may be referenced in specific call.
  /// Beware of possible main entry point execution side-effects.
  /// 
  void run(const EsString& entry, const EsVariant& params);

  /// Execute script in debugger
  void debugRun();

  /// Execute script in debugger, in stepped mode
  void debugStep();

  /// Pause debugger at the current execution point
  void debugPause();

  /// Abort either normal, or debugger execution
  void abort();

  /// Save script translatables
  void translatablesSave(const EsString& dest);

protected:
  virtual bool isSideloadName(const EsString& name) const ES_OVERRIDE;

  // ES events
  void onNonDebugStarted();
  void onFinished();
  void onDebugStarted();
  void onBrkChangeRequest(const EsString& key, EsString::HashT hash, int line, bool set, bool state);

protected:
  EvtHandler m_evtHandler;
  EsScriptDebug m_debug;
  Runner m_runner;
  EsProgressMonitorIntf::Ptr m_pm;
  bool m_running;
  bool m_debugging;
  bool m_debugPaused;
  bool m_aborting;

  ES_NON_COPYABLE(EsCompiledScriptDocument);
};

#endif // _es_compiled_script_document_h_
