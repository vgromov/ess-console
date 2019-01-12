#ifndef _es_text_editor_view_base_h_
#define _es_text_editor_view_base_h_

class EsTextEditorViewBase : public wxStyledTextCtrl
{
private:
  // ES Event subscriber
  class EvtHandler : public EsEventSubscriber
  {
  public:
    EvtHandler(EsTextEditorViewBase& owner) ES_NOTHROW;

    ES_DECL_INTF_METHOD(void, notify)(const EsEventIntf::Ptr& evt);

  protected:
    EsTextEditorViewBase& m_owner;
  };
  friend class EvtHandler;

public:
  enum {
    /// Marker IDs. Derived classes should define markers starting from markerIdMax
    markerBmGeneric,
    markerBm0,
    markerBm1,
    markerBm2,
    markerBm3,
    markerBm4,
    markerBm5,
    markerBm6,
    markerBm7,
    markerBm8,
    markerBm9,
    /// Special value must be the last one in list of enum values
    markerIdMax,

    /// BM marker masks
    markerBmGenericMask =
      (1 << markerBmGeneric),
    markerBmNumberedMask =
      (1 << markerBm0) |
      (1 << markerBm1) |
      (1 << markerBm2) |
      (1 << markerBm3) |
      (1 << markerBm4) |
      (1 << markerBm5) |
      (1 << markerBm6) |
      (1 << markerBm7) |
      (1 << markerBm8) |
      (1 << markerBm9),
    markerBmMask =
      markerBmGenericMask |
      markerBmNumberedMask,

    /// Indicator ids
    highlighter = 0
  };

protected:
  EsTextEditorViewBase(wxWindow *parent, wxWindowID id, long style, const wxString& className);

public:
  virtual ~EsTextEditorViewBase();

  bool isStyled() const ES_NOTHROW { return nullptr != m_lexNode; }

  bool isStyle(int hlStyleId, EsSyntaxHighlighterId hlId) const ES_NOTHROW;
  bool isStyleInRange(int hlStyleId, EsSyntaxHighlighterId hlIdStart, EsSyntaxHighlighterId hlIdEnd) const ES_NOTHROW;

  void stylesInit();

  void currentPositionSet(int line, int col);

  virtual void deduceLexerFromFilePath(const EsString& fpath);

  /// Text access API
  ///
  virtual void textSet(const EsString& text);
  virtual EsString textGet() const;

  /// Text search-replace API
  ///
  void textSearchReplaceReset();
  void textSearchReplaceDirectionSet(bool down);
  inline bool textSearchReplaceDirectionGet() const ES_NOTHROW { return m_searchReplaceDirection; }
  void textSearchReplaceCurrentRangeGet(int& fromPos, int& toPos);

  inline int textSearchReplacePosGet() const ES_NOTHROW { return m_searchReplacePos; }
  void textSearchReplacePositionSetCurrent();

  bool textSearch(const wxString& txt, int flags);
  bool textReplace(const wxString& txtOld, const wxString& txtNew, int flags, bool all);

  bool textSearchIsFinished() const;

  /// Text highlighter API
  ///
  /// Highlights text range using either active, or inactive highlighter style
  /// @param [in] fromPos - Text position to start highlighting
  /// @param [in] toPos   - Text position to end highlighting
  ///
  void highlight(int fromPos, int toPos);

  /// Remove all highlighting between specified positions
  /// @param [in] fromPos - Start position to remove highlighting
  /// @param [in] toPos   - End position to remove highlighting
  ///                       if both fromPos and toPos = -1, remove all highlighting in document
  ///
  void highlightRemove(int fromPos, int toPos);

  /// Highlight text pattern(s) in document, between fromPos and toPos
  /// @param [in] fromPos - Text position to start pattern lookup for highlighting
  /// @param [in] toPos   - Text position to end pattern lookup for highlighting
  ///                       if both fromPos and toPos = -1 - perform lookup in whole document
  /// @param [in] all     - Highlight all found pattern occurrences, otherwise, only the first one is highlighted
  ///
  /// Postcondition:        All existing highlighting in document is removed
  ///
  void highlight(const wxString& txt, int fromPos, int toPos, bool all);

  /// Attached document key R/O access
  EsString keyGet() const;

  void lexerSet(const EsLexDbNode& lexNode);

  void documentConnect(const EsDocumentIntf::Ptr& doc) ES_NOTHROW;

  /// Bookmark modification and traverse API
  ///

  bool hasBookmarks() const;

  void bookmarksClearAll();

  void bookmarkToggle(int tag = -1); ///< Toggle (optionally numbered) bookmark at current line

  bool hasBookmark(int tag) const;

  void bookmarkGotoPrev();
  void bookmarkGotoNext();
  void bookmarkGoto(int tag);

  /// Editor context menu getter
  wxMenuPtr ctxMenuGet();
  wxMenuPtr customCtxMenuGet();
  void customCtxMenuStringsUpdate(wxMenu* pmnu);
  void customCtxMenuEvtHandlersSet(wxEvtHandler* subj, bool set);

protected:
  virtual void stylesSetCommon();
  
  // Tune-up editor commands support
  virtual void cmdsInit();
  
  // Apply highlighting styles from lexer node
  virtual void lexerStylesApply(const EsLexDbNode& lexNode);

  // Initialize autocompletion data. 
  //
  virtual void autocompletionInit();

  // Bookmarks maintenance
  //
  virtual void doBookmarkToggle(int line, int tag);

  void markersEnumerate(int mask, std::function<void (int line, int mask, int maskFound)> onMarkerEnumerate);
  virtual void onEditorLinesChanged();

  bool bookmarkFromMaskGet(int mask, int& tag);
  void taggedBookmarkRemoveAllExcl(int tag, int excl);
  bool bookmarkFromLineGet(int line, int& tag); //< Return true if line has BM set, return its tag value in ref param
  void bookmarkSet(int line, int tag);
  void bookmarksSynchronize();

  void textFromDocAssign();

  // Search replace helpers
  //
  void textSearchReplacePosFixup();
  void textReplaceInternal(const wxString& txtOld, const wxString& txtNew);

  void fromToFixup(int& from, int& to) const;

  // Local selection highlighter
  //
  void highlightClear();
  virtual bool canHighlightSelection(int fromPos, int toPos) const;

  void ctxMenuInit();
  virtual void doCustomCtxMenuInit();
  virtual void doCtxMenuStringsUpdate(wxMenu* pmnu);
  virtual void doCustomCtxMenuEvtHandlersSet(wxEvtHandler* subj, bool set);

  // Local text context helpers
  //
  bool isBrace(const wxString::char_type& ch) const;

  void braceHighlightUpdate(int pos);

  /// Enclose current selection into left-right strings pair
  void selectionEncloseIn(const wxString& left, const wxString& right);

  // WX events
  void onEditorContentChange(wxStyledTextEvent& evt);
  void onDblClick(wxStyledTextEvent& evt);
  virtual void onStcUiUpdate(wxStyledTextEvent& evt);
  virtual void onMarginClick(wxStyledTextEvent& evt);
  virtual void onAutoCompleting(wxStyledTextEvent& evt);
  void onContextMenu(wxContextMenuEvent& evt);
  void onGotoClosingBrace(wxCommandEvent& evt);
  void onGotoOpeningBrace(wxCommandEvent& evt);
  virtual void onCmdUiUpdate(wxUpdateUIEvent& evt);

  // ES events
  void onDocumentOpened();
  void onDocumentChanged(const EsString& subj);
  void onDocumentSideloadChanged(const EsString& subj);
  void onDocumentStateChanged();
  virtual void onI18nLocaleChanged(const EsString& loc);

protected:
  EvtHandler m_handler;
  wxMenuPtr m_pmnu;     //< Editor pop-up menu
  wxMenuPtr m_pmnuCtx;  //< Editor custom context menu part
  wxMenu* m_mnuEditBm;
  const EsLexDbNode* m_lexNode;
  EsDocumentIntf::Ptr m_doc; ///< Optional attached document
  wxString m_txtLookup;
  std::set<int> m_tags;
  std::map<int, std::set<wxString> > m_categorizedTokens;
  int m_searchReplacePos;
  int m_braceBeg;
  int m_braceEnd;
  bool m_searchReplaceDirection;

private:
  EsTextEditorViewBase() ES_REMOVEDECL;
  EsTextEditorViewBase(const EsTextEditorViewBase&) ES_REMOVEDECL;
  EsTextEditorViewBase& operator=(const EsTextEditorViewBase&) ES_REMOVEDECL;
};

#endif // _es_text_editor_view_base_h_
