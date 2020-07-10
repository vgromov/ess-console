#ifndef _es_dbg_log_rules_dlg_h_
#define _es_dbg_log_rules_dlg_h_

/// DebugLog rules editor dialog
///
class EsDbgLogRulesDlg : public EsDlgBase
{
public:
  EsDbgLogRulesDlg( wxWindow* parent );

  bool inclIsFirstGet() const;
  void inclIsFirstSet(bool inclFirst);

  EsString::Array rulesInclGet() const;
  void rulesInclSet(const EsString::Array& rules);

  EsString::Array rulesExclGet() const;
  void rulesExclSet(const EsString::Array& rules);

  static const wxSize& minSizeGet();

protected:
  virtual void onI18nLocaleChanged(const EsString& loc) ES_OVERRIDE;

  // Rules Evaluation helper
  //
  bool rulesEvaluate(const EsString& fname) const;

  // Lists helpers
  bool hasCurrent(wxListBox* list) const ES_NOTHROW;
  bool canAdd(wxListBox* list, wxTextCtrl* ed) const ES_NOTHROW;
  bool canReplace(wxListBox* list, wxTextCtrl* ed) const ES_NOTHROW;
  bool canMoveCurrentUp(wxListBox* list) const ES_NOTHROW;
  bool canMoveCurrentDown(wxListBox* list) const ES_NOTHROW;
  void moveCurrentUp(wxListBox* list) ES_NOTHROW;
  void moveCurrentDown(wxListBox* list) ES_NOTHROW;
  void itemInsert(wxListBox* list, wxTextCtrl* ed) ES_NOTHROW;
  void itemReplace(wxListBox* list, wxTextCtrl* ed) ES_NOTHROW;
  void itemDelete(wxListBox* list) ES_NOTHROW;

  // WX event handlers
  void onTestSubjChanged(wxCommandEvent& evt);
  void onInclItemUp(wxCommandEvent& evt);
  void onInclItemDown(wxCommandEvent& evt);
  void onInclItemAdd(wxCommandEvent& evt);
  void onInclItemReplace(wxCommandEvent& evt);
  void onInclItemDelete(wxCommandEvent& evt);
  void onInclListItemChange(wxCommandEvent& evt);
  void onExclItemUp(wxCommandEvent& evt);
  void onExclItemDown(wxCommandEvent& evt);
  void onExclItemAdd(wxCommandEvent& evt);
  void onExclItemReplace(wxCommandEvent& evt);
  void onExclItemDelete(wxCommandEvent& evt);
  void onExclListItemChange(wxCommandEvent& evt);
  void onTestEval(wxCommandEvent& evt);
  void onUpdateUi(wxUpdateUIEvent& evt);

protected:
  wxStaticBoxSizer* m_szrTest;
  wxTextCtrl* m_edTest;
  wxButton* m_btnTestEval;
  wxStaticBitmap* m_bmEvalStat;

  wxCheckBox* m_chkInclFirst;

  wxStaticBoxSizer* m_szrIncl;
  wxTextCtrl* m_edIncl;
  wxBoxSizer* m_szrInclBtns;
  wxButton* m_btnInclUp;
  wxButton* m_btnInclDown;
  wxButton* m_btnAddIncl;
  wxButton* m_btnReplaceIncl;
  wxButton* m_btnDeleteIncl;
  wxStaticText* m_lblListIncl;
  wxListBox* m_lstIncl;

  wxStaticBoxSizer* m_szrExcl;
  wxTextCtrl* m_edExcl;
  wxBoxSizer* m_szrExclBtns;
  wxButton* m_btnExclUp;
  wxButton* m_btnExclDown;  
  wxButton* m_btnAddExcl;
  wxButton* m_btnReplaceExcl;
  wxButton* m_btnDeleteExcl;
  wxStaticText* m_lblListExcl;
  wxListBox* m_lstExcl;

  wxButton* m_btnOk;
  wxButton* m_btnCancel;

  ES_NO_DEFAULT_CTR(EsDbgLogRulesDlg);
  ES_NON_COPYABLE(EsDbgLogRulesDlg);
};

#endif //< _es_dbg_log_rules_dlg_h_
