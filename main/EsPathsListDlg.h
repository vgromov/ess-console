#ifndef _es_paths_list_dlg_h_
#define _es_paths_list_dlg_h_

/// Common directory list editor dialog
///
class EsPathsListDlg : public EsDlgBase
{
public:
  EsPathsListDlg(
    wxWindow* parent, 
    const wxString& title, 
    const wxString& dirPickerPrompt, 
    const wxString& dirListLabel
  );
  
  EsString::Array foldersGet() const;
  void foldersSet(const EsString::Array& folders);

  static const wxSize& minSizeGet();

protected:
  virtual void onI18nLocaleChanged(const EsString& loc) ES_OVERRIDE;

  // Folder list helpers
  bool canMoveCurrentUp() const ES_NOTHROW;
  bool canMoveCurrentDown() const ES_NOTHROW;
  void moveCurrentUp() ES_NOTHROW;
  void moveCurrentDown() ES_NOTHROW;

  // WX event handlers
  void onDirItemUp(wxCommandEvent& evt);
  void onDirItemDown(wxCommandEvent& evt);
  void onDirItemAdd(wxCommandEvent& evt);
  void onDirItemReplace(wxCommandEvent& evt);
  void onDirItemDelete(wxCommandEvent& evt);
  void onDirListItemChange(wxCommandEvent& evt);
  void onUpdateUi(wxUpdateUIEvent& evt);

protected:
  wxString m_dirPickerPrompt;
  wxString m_dirListLabel;
  wxSizer* m_folderOps;
  wxBoxSizer* m_folderBtns;
  wxDirPickerCtrl* m_folder;
  wxButton* m_btnUp;
  wxButton* m_btnDown;
  wxButton* m_btnAdd;
  wxButton* m_btnReplace;
  wxButton* m_btnDelete;
  wxStaticText* m_lblList;
  wxListBox* m_lstFolders;
  wxButton* m_btnOk;
  wxButton* m_btnCancel;

  ES_NO_DEFAULT_CTR(EsPathsListDlg);
  ES_NON_COPYABLE(EsPathsListDlg);
};

#endif // _es_paths_list_dlg_h_
