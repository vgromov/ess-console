#ifndef _es_sconsole_main_h_
#define _es_sconsole_main_h_
//---------------------------------------------------------------------------

// EsSconsoleSettings class
//
struct EsSconsoleOptions 
{
  EsSconsoleOptions();

  void init();

  wxFont* m_fntTxt;
  wxFont* m_fntLineNum;

private:
  EsSconsoleOptions(const EsSconsoleOptions&) ES_REMOVEDECL;
  EsSconsoleOptions& operator=(const EsSconsoleOptions&) ES_REMOVEDECL;
};

// EsSconsole-specific ART client IDs
#define esART_STC_MARGIN        wxART_MAKE_CLIENT_ID(esART_STC_MARGIN)
#define esART_STC_AUTOCOMPL     wxART_MAKE_CLIENT_ID(esART_STC_AUTOCOMPL)

// EsSconsole-specific ART IDs
//
 
// Script editor art
#define esART_BOOKMARK          wxART_MAKE_ART_ID(esART_BOOKMARK)
#define esART_SCRIPT_FILE       wxART_MAKE_ART_ID(esART_SCRIPT_FILE)
#define esART_BOOKMARK_0        wxART_MAKE_ART_ID(esART_BOOKMARK_0)
#define esART_BOOKMARK_1        wxART_MAKE_ART_ID(esART_BOOKMARK_1)
#define esART_BOOKMARK_2        wxART_MAKE_ART_ID(esART_BOOKMARK_2)
#define esART_BOOKMARK_3        wxART_MAKE_ART_ID(esART_BOOKMARK_3)
#define esART_BOOKMARK_4        wxART_MAKE_ART_ID(esART_BOOKMARK_4)
#define esART_BOOKMARK_5        wxART_MAKE_ART_ID(esART_BOOKMARK_5)
#define esART_BOOKMARK_6        wxART_MAKE_ART_ID(esART_BOOKMARK_6)
#define esART_BOOKMARK_7        wxART_MAKE_ART_ID(esART_BOOKMARK_7)
#define esART_BOOKMARK_8        wxART_MAKE_ART_ID(esART_BOOKMARK_8)
#define esART_BOOKMARK_9        wxART_MAKE_ART_ID(esART_BOOKMARK_9)
#define esART_EXECLINE          wxART_MAKE_ART_ID(esART_EXECLINE)
#define esART_BRK_ACTIVE        wxART_MAKE_ART_ID(esART_BRK_ACTIVE)
#define esART_BRK_INACTIVE      wxART_MAKE_ART_ID(esART_BRK_INACTIVE)
#define esART_BRK_INVALID       wxART_MAKE_ART_ID(esART_BRK_INVALID)

// Script autocompletion art    
#define esART_AC_ATTRS          wxART_MAKE_ART_ID(esART_AC_ATTRS)
#define esART_AC_CONSTS         wxART_MAKE_ART_ID(esART_AC_CONSTS)
#define esART_AC_ENUM_ITEMS     wxART_MAKE_ART_ID(esART_AC_ENUM_ITEMS)
#define esART_AC_ENUMS          wxART_MAKE_ART_ID(esART_AC_ENUMS)
#define esART_AC_GLOBFUNCS      wxART_MAKE_ART_ID(esART_AC_GLOBFUNCS)
#define esART_AC_GLOBVARS       wxART_MAKE_ART_ID(esART_AC_GLOBVARS)
#define esART_AC_KEYWORDS       wxART_MAKE_ART_ID(esART_AC_KEYWORDS)
#define esART_AC_OBJECTS        wxART_MAKE_ART_ID(esART_AC_OBJECTS)
#define esART_AC_OBJFIELDS      wxART_MAKE_ART_ID(esART_AC_OBJFIELDS)
#define esART_AC_OBJFUNCS       wxART_MAKE_ART_ID(esART_AC_OBJFUNCS)
#define esART_AC_OBJPROPS       wxART_MAKE_ART_ID(esART_AC_OBJPROPS)
#define esART_AC_OBJVARS        wxART_MAKE_ART_ID(esART_AC_OBJVARS)
#define esART_AC_SERVICES       wxART_MAKE_ART_ID(esART_AC_SERVICES)
#define esART_AC_VARSVCS        wxART_MAKE_ART_ID(esART_AC_VARSVCS)

// Menu, toolbar art
#define esART_COMPILE           wxART_MAKE_ART_ID(esART_COMPILE)
#define esART_RUN               wxART_MAKE_ART_ID(esART_RUN)
#define esART_DEBUG_RUN         wxART_MAKE_ART_ID(esART_DEBUG_RUN)
#define esART_DEBUG_PAUSE       wxART_MAKE_ART_ID(esART_DEBUG_PAUSE)
#define esART_DEBUG_STEP        wxART_MAKE_ART_ID(esART_DEBUG_STEP)
#define esART_ABORT             wxART_MAKE_ART_ID(esART_ABORT)
#define esART_CLOSE             wxART_MAKE_ART_ID(esART_CLOSE)
#define esART_CLOSE_ALL         wxART_MAKE_ART_ID(esART_CLOSE_ALL)
#define esART_SELECT_ALL        wxART_MAKE_ART_ID(esART_SELECT_ALL)
#define esART_SAVE_ALL          wxART_MAKE_ART_ID(esART_SAVE_ALL)
#define esART_INFO              wxART_MAKE_ART_ID(esART_INFO)
#define esART_HELP_MODULE       wxART_MAKE_ART_ID(esART_HELP_MODULE)

// EsSconsole main frame class
//
class EsSconsoleMain : public wxFrame
{
private:
  // Misc constants
  enum {
    evtPumpTmo = 25,
    fileFrameCaptionTxtLenMax = 64
  };

  // Status bar fields IDs
  enum {
    sbFldHint,
    sbFldLine,
    sbFldColumn,
    sbFldCaps,
    sbFldNumlock,
    sbFldInsOvr,
    // Special value, must go last
    sbFldCnt
  };

  // Modified document save preparation flags
  enum PrepareSaveFlag {
    PromptSaveModified    = 0x0001,
    SaveAs                = 0x0002
  };

  // Document pointer type enum
  enum class DocPtrType {
    None,
    Script,
    Text,
    Binary
  };

  // Document pointer cache
  struct DocPtrs 
  {
    DocPtrType m_docPtrType;
    union {
      void* m_rawPtr;
      EsScriptDocument* m_scriptDocPtr;
      EsTextDocument* m_textDocPtr;
    };
    EsCompiledScriptDocument* m_compiledDocPtr;
  };

  // Script compilation thread worker
  class Compiler : public EsThread
  {
  public:
    Compiler(EsSconsoleMain& owner);
    
    // Access compiled binary instance
    EsScriptIntf::Ptr binaryGet() { return m_scriptBinary; }

    // Set compiler source, either file, or actual text
    void sourceSet(const EsString& src, bool isText);
    void sourceNameSet(const EsString& name) ES_NOTHROW { m_srcTextName = name; }

    // Get assigned source type flag
    bool sourceIsTextGet() const ES_NOTHROW { return m_srcIsText; }

    // Get assigned source
    const EsString& sourceGet() const ES_NOTHROW { return m_src; }

    // Get optional source name
    const EsString& sourceNameGet() const ES_NOTHROW { return m_srcTextName;  }

  protected:
    virtual long worker();
    virtual void onEnterWorker();
    virtual void onExitWorker();

  protected:
    EsSconsoleMain& m_owner;
    EsScriptIntf::Ptr m_scriptBinary;
    EsDateTime m_start;
    EsString m_src;
    EsString m_srcTextName; //< If source is actual text, m_srcTextName is an optional name of that text
    bool m_srcIsText;
    bool m_compiledOk;
  };
  friend class Compiler;

  // ES Event subscriber
  class EvtHandler : public EsEventSubscriber
  {
  public:
    EvtHandler(EsSconsoleMain& owner) ES_NOTHROW;

    ES_DECL_INTF_METHOD(void, notify)(const EsEventIntf::Ptr& evt);

  protected:
    EsSconsoleMain& m_owner;
  };
  friend class EvtHandler;

public:
  EsSconsoleMain();
  virtual ~EsSconsoleMain() ES_OVERRIDE;

  virtual bool Show(bool show = true) ES_OVERRIDE;

  void init();

  /// Command line batch execution mode
  void batchExecute(const EsSconsoleCommandLineParams& cmds);

  /// Return true, if we're executing batch
  inline bool isExecutingBatch() const ES_NOTHROW { return nullptr != m_batchCmds; }
  
  /// Access GUI options data
  const EsSconsoleOptions& optionsGet() const ES_NOTHROW { return m_opts; }

  /// Settings serialization
  void settingsLoad();

  /// App settings (include and bin-link paths) assignment
  /// @param [in, opt] bool - doSave. if true, forces global application settings to be saved immediately.
  ///                         Do not write global settings otherwise (default behaviour)
  ///                         
  void commonAppSettingsApply(bool doSave = false);

  /// Common text document edit menu structure access
  wxMenu* menuEditGet() { return m_mnuEdit; }

  /// Public documents API
  ///

  /// Close all open documents
  bool documentsCloseAll(bool promptForSaveModified = true);
  
  /// Return GUI settings path
  static EsString settingsPathGet();
  
protected:
  // One-time initializers
  //
  void menuInit();
  void mdiInit();
  void toolbarInit();
  void statusbarInit();
  //void treeInit();
  void nbEditorInit();
  void layoutInit();
  void applogPaneInit();
  void compilerOutputPaneInit();
  void documentListPaneInit();

  // Find-replace dialogs
  //
  void dlgFindReplace(bool replace, wxString strSearch = wxEmptyString);

  // Domain-specific initializer helpers
  //
  void nbEditorEvtHandlersInit();
  void mnuFileInit();
  void mnuFileEvtHandlersInit();
  void mnuEditInit();
  void mnuEditEvtHandlersInit();
  void mnuScriptInit();
  void mnuScriptEvtHandlersInit();
  void mnuOptionsInit();
  void mnuOptionsEvtHandlersInit();
  void mnuWindowInit();
  void mnuWindowEvtHandlersInit();
  void mnuHelpInit();
  void mnuHelpEvtHandlersInit();
  
  // Event handling initialization
  //
  void evtHandlersInit();
  void evtHandlersUninit();

  // Dynamic text update helpers
  //
  void scriptCompiationTextUpdate();
  void scriptDebugLabelsAndIconsUpdate();
  void sbTextEditInfoUpdate();
  
  // WX Event handlers
  //
  void onFileUiUpdate(wxUpdateUIEvent& evt);
  void onEditUiUpdate(wxUpdateUIEvent& evt);
  void onScriptUiUpdate(wxUpdateUIEvent& evt);
  void onOptionsUiUpdate(wxUpdateUIEvent& evt);
  void onWindowUiUpdate(wxUpdateUIEvent& evt);
  void onHelpUiUpdate(wxUpdateUIEvent& evt);
  void onIdle(wxIdleEvent& evt);
  void onClose(wxCloseEvent& evt);
  void onEsEvtPump(wxTimerEvent& evt);
  void onMainClose(wxCommandEvent& evt);
  void onScriptNew(wxCommandEvent& evt);
  void onFileOpen(wxCommandEvent& evt);
  void onFileClose(wxCommandEvent& evt);
  void onFileCloseAll(wxCommandEvent& evt);
  void onFileSave(wxCommandEvent& evt);
  void onFileSaveAll(wxCommandEvent& evt);
  void onFileSaveAs(wxCommandEvent& evt);
  void onFileHistoryOpen(wxCommandEvent& evt);
  void onFileHistoryClear(wxCommandEvent& evt);
  void onEditUndo(wxCommandEvent& evt);
  void onEditRedo(wxCommandEvent& evt);
  void onEditSelectAll(wxCommandEvent& evt);
  void onEditCopy(wxCommandEvent& evt);
  void onEditCut(wxCommandEvent& evt);
  void onEditPaste(wxCommandEvent& evt);
  void onEditFind(wxCommandEvent& evt);
  void onEditReplace(wxCommandEvent& evt);
  void onEditBookmarkClearAll(wxCommandEvent& evt);
  void onEditBookmarkToggle(wxCommandEvent& evt);
  void onEditBookmarkNext(wxCommandEvent& evt);
  void onEditBookmarkPrev(wxCommandEvent& evt);
  void onEditBookmarkGoto(wxCommandEvent& evt);
  void onViewClose(wxAuiNotebookEvent& evt);
  void onActiveViewChanged(wxAuiNotebookEvent& evt);
  void onScriptCompileBreak(wxCommandEvent& evt);
  void onScriptRun(wxCommandEvent& evt);
  void onScriptDebug(wxCommandEvent& evt);
  void onScriptDebugStep(wxCommandEvent& evt);
  void onScriptAbort(wxCommandEvent& evt);
  void onWndAppLogToggle(wxCommandEvent& evt);
  void onWndCompLogToggle(wxCommandEvent& evt);
  void onWndDoclistToggle(wxCommandEvent& evt);
  void onOptIncludeDebug(wxCommandEvent& evt);
  void onOptGenTranslatables(wxCommandEvent& evt);
  void onOptIncludePaths(wxCommandEvent& evt);
  void onOptLinkPaths(wxCommandEvent& evt);
  void onOptDbgLogSuppress(wxCommandEvent& evt);
  void onOptDbgLogRules(wxCommandEvent& evt);
  void onOptLangSelected(wxCommandEvent& evt);
  void onHelpAbout(wxCommandEvent& evt);
  void onHelp(wxCommandEvent& evt);
  void onHelpDocument(wxCommandEvent& evt);
#if defined(__WXMSW__)
  void onAutoUpdate(wxCommandEvent& evt);
  void onOnlineUpdate(wxCommandEvent& evt);
#endif
  void onDlgFindReplaceEvent(wxFindDialogEvent& evt);

  // ES event handlers
  //
  void onI18nLocaleChanged(const EsString& lang);
  void onDocumentCreated(const EsString& key, const EsVariant& params);
  void onDocumentOpened(const EsString& key, const EsVariant& params);
  void onDocumentClosed(const EsString& key, const EsString& type);
  void onDocumentChanged(const EsString& key, const EsString& subj, void* sender);
  void onDocumentKeyChanged(const EsString& keyOld, const EsString& keyNew);
  void onDocumentStateChanged(const EsString& key);
  void onDocumentViewCloseRequest(wxWindow* view);
  void onDocumentListCloseRequest(const EsString::Array& keys);
  void onCompilationStart();
  void onCompilationAborted();
  void onCompilationEnd(const EsString& input, const EsVariant& compiledScript);
  void onScriptFinished(bool hasErrors);
  void onScriptAborted();
  void onScriptDebugPaused(const EsString& file, ulong line, bool isBreakpoint);
  void documentFileOpenOrActivate(const EsString& documentPath, const EsVariant& params, std::set<EsString>& banNextTime, bool preferActivate = false);
  void documentOpenAndSetPosition(const EsString& documentPath, const EsVariant& line, const EsVariant& col, bool executionMode);
  void onDocumentActivate(const EsString& documentPath);
  void onAllDocumentsClosed();
  
  // Document view services
  //
  void documentFileOpen(std::set<EsString>& banNextTime, const EsString& type, const EsString& fpath, const EsVariant& params);
  int selectNewFilePath(const EsDocumentIntf::Ptr& doc, EsString& newPath);
  int documentPrepareForSave(const EsDocumentIntf::Ptr& doc, int flags, EsString& newPath);

  EsString keyByDocumentViewGet(wxWindow* view) const ES_NOTHROW;
  wxWindow* documentViewByKeyGet(const EsString& key) const ES_NOTHROW;
  void documentViewAdd(wxWindow* view, const EsString& key, const EsDocumentIntf::Ptr& doc);
  void documentViewClose(wxWindow* view);
  void documentViewUpdate(wxWindow* view, const EsDocumentIntf::Ptr& doc);
  void documentViewAddToNotebook(wxWindow* view, const EsString& key, const EsDocumentIntf::Ptr& doc);
  void currentDocViewChangeCheck();

  void scriptViewCreate(const EsString& key, const EsDocumentIntf::Ptr& doc);
  void compiledScriptViewCreate(const EsString& key, const EsDocumentIntf::Ptr& doc);
  void textViewCreate(const EsString& key, const EsDocumentIntf::Ptr& doc);
  void documentViewCreate(const EsString& key, const EsDocumentIntf::Ptr& doc);

  EsDocumentIntf::Ptr currentDocumentGet() const ES_NOTHROW;
  bool haveAnyOpenDocuments() const ES_NOTHROW;
  bool canSaveCurrentDocument() const ES_NOTHROW;
  bool haveAnyModifiedDocuments() const ES_NOTHROW;

  // Document save internal services
  //
  void documentSaveInternal(const EsDocumentIntf::Ptr& doc, const EsString& target);
  bool documentSaveByKey(const EsString& key);
  bool documentSave(const EsDocumentIntf::Ptr& doc, bool promptToSaveModified = true);
  bool documentSaveAs(const EsDocumentIntf::Ptr& doc);

  EsTextEditorViewBase* currentTextEditorGet();

  static void uniqueParamsAppend(EsVariant::Array& out, const EsVariant::Array& in, EsVariant::Type ifType = EsVariant::VAR_EMPTY);
  void documentViewParamsHandle(const EsString& key, const EsVariant& params);

  // Common internal services
  //
  void binDocPtrUpdateInternal(EsCompiledScriptDocument* binDocPtr);
  void docPtrsReset();
  void currentDocPtrUpdate();
  EsDocument* currentDocPtrGet() ES_NOTHROW;
  inline const EsDocument* currentDocPtrGet() const ES_NOTHROW { return const_cast<EsSconsoleMain*>(this)->currentDocPtrGet(); }
  EsCompiledScriptDocument* binaryScriptGet() ES_NOTHROW { return m_docPtrs.m_compiledDocPtr; }
  void frameCaptionUpdateFromNbPage(int pageIdx);

  // Compiler and Runner services
  //
  void batchReset() ES_NOTHROW;
  void batchComplete(bool allowClose = true);
  void scriptCompile(const EsDocumentIntf::Ptr& doc);
  void scriptCompile();
  bool currentDocumentCanCompile() const;
  bool binaryScriptIsDebuggable() const;
  bool binaryScriptCanRun() const;
  bool binaryScriptCanStep() const;
  bool binaryScriptCanAbort() const;
  bool binaryScriptIsContinuouslyDebugging() const;
  bool binaryScriptIsRunning() const;
  bool binaryScriptIsDebugging() const;
  void binaryScriptRun(const EsDocumentIntf::Ptr& doc, const EsString& entry, const EsVariant& args);

  // Settings serialization
  void settingsSave();

  // Try to deduce document parameters (if any) from document type and key.
  // Parameters must be packed into assoc container by design convention.
  // Both key and type checks are performed, so method may throw on errors.
  // 
  EsVariant documentParamsDeduceByDocTypeAndKey(const EsString& type, const EsString& key) const;

  // Return default compiled script encryption key
  static EsString defaultEncKeyGet();

  // Create binary script document parameters object from app settings
  static EsAssocContainerIntf::Ptr settingsToCompiledScriptDocumentParams(const EsString& key = EsString::null());
 
protected:
#if defined(__WXMSW__)
  EsAutoUpdater m_au;
#endif
  wxAuiManager m_mgrAui;
  Compiler m_compiler;
  EvtHandler m_handler;
  wxTimer m_tmrEvtPump;
  EsStreamIntf::Ptr m_settings;
  EsDocumentManagerIntf::Ptr m_mgrMdi;
  std::map<EsString, wxWindow*> m_views;
  wxFileHistory m_mru;
  EsSconsoleOptions m_opts;
  wxString m_paneAppLogState;
  wxString m_paneCompilerLogState;
  wxMenuBar* m_mnu;
  wxMenu* m_mnuFile;
  wxMenu* m_mnuFileMRU;
  wxMenu* m_mnuEdit;
  wxMenu* m_mnuEditBm;
  wxMenu* m_mnuWindow;
  wxMenu* m_mnuScript;
  wxMenu* m_mnuOptions;
  wxMenu* m_mnuHelp;
  wxStatusBar* m_sb;
  wxToolBar* m_tb;
  wxAuiNotebook* m_nbEditor;
  wxPanel* m_log;
  wxPanel* m_logComp;
  wxPanel* m_docList;
  const EsSconsoleCommandLineParams* m_batchCmds;
  wxWindow* m_activeView;
  DocPtrs m_docPtrs;
  wxFindReplaceDialog* m_dlgFr;
  wxFindReplaceData m_dataFr;
  wxPoint m_posFr;
  bool m_initialized;
  bool m_compiling;
  bool m_compiledOk;
  bool m_changingDocptrs;
};

#endif // _es_sconsole_main_h_
